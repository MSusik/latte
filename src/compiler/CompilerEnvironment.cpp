//
// Created by msusik on 02.01.16.
//

#include <iostream>
#include "CompilerEnvironment.h"

Registers::Registers() {
    used.insert(make_pair("ax", false));
    used.insert(make_pair("bx", false));
    used.insert(make_pair("r10", false));
    used.insert(make_pair("r11", false));
    used.insert(make_pair("r12", false));
    used.insert(make_pair("r13", false));
    used.insert(make_pair("r14", false));
}


Registers::Registers(bool sameStack, const Registers& reg) : Registers() { ;
    if(sameStack)
    {
        variables_on_stack = reg.variables_on_stack;
        variables = reg.variables;
        used = reg.used;
        stackPointers = reg.stackPointers;
        stackMin = reg.stackMin;
        args = reg.args;
    }
    defined_here = set<string>();
    cout << variables_on_stack.size() << " REG" << endl;
    cout << variables.size() << " Variables" << endl;
    cout << used.size() << " Used" << endl;
    flush(cout);
}

void Envs::addEnv(bool sameStack) {
    if(!envs.size())
    {
        CompilerEnvironment newEnv;
        this->envs.push(newEnv);
        cout << "Adding empty env" << endl;
        return;

    }
    CompilerEnvironment newEnv(sameStack, envs.top());

    cout << "Adding new env" << endl;
    this->envs.push(newEnv);
}

void Envs::removeEnv() {
    envs.pop();
}

CompilerEnvironment &Envs::top() {
    return envs.top();
}

string CompilerEnvironment::freeTemp() {
    return this->registers.freeTemp();
}

void CompilerEnvironment::putArg(stringstream& ss) {
    /// to co jest na topie
    string value = this->registers.freeTemp();
    char op = this->registers.getOperator(value);
    cout << op << " TYPE" << endl;
    string reg = this->registers.getArg(op == 'q', op == 'b');
    ss << "\tmov" << op << " " << value << ", " << reg <<"\n";
}


string Registers::getFree(short pointer) {
    string th = "";
    for(auto it = this->used.begin(); it != this->used.end(); ++it)
    {
        if(!it->second){
            th = it->first;
        }

    }
    this->used[th] = true;
    //cout << "Getting " << th << endl;
    return this->short_to_long(th, pointer);
}


string Registers::getTemp(bool pointer) {
    string reg_name = this->getFree(pointer ? 1 : 0);
    //cout <<"Getting temp " << reg_name << endl;
    this->temps.push_back(reg_name);
    return reg_name;
}


string Registers::freeFree(string reg_name) {
    string short_name = this->long_to_short(reg_name);
    this->used[short_name] = false;
    //cout << "Freeing " << reg_name << endl;
    return reg_name;
}

string Registers::freeTemp(bool pop) {
    //cout << "free" << endl;

    string reg_name = this->temps.back();
    if(reg_name[0] == 'V' || reg_name[0] == '$')
    {
        // Variable
        this->temps.pop_back();
        if(reg_name[0] == 'V' )
        {
            return reg_name.substr(1);
        }
        return reg_name;
    }
    reg_name = this->freeFree(reg_name);
    if(pop)
        this->temps.pop_back();
    return reg_name;
}

string Registers::short_to_long(string s, short pointer) {
    if(pointer == 1)
    {
        if(s[0] == 'r')
            return '%' + s;
        else
            return "%r" + s;
    } else if(pointer == -1)
    {
        if(s[0] == 'r')
            return '%' + s + "b";
        else if(s[s.size() - 1] == 'x')
            return "%" + s[0] + 'l';
        else
            return "%" + s + 'l';

    } else
    {
        if(s[0] == 'r')
            return '%' + s + "d";
        else
            return "%e" + s;

    }
}

string Registers::long_to_short(string l) {
    string l2 = l.substr(2);

    // konczy sie na b
    if(l[l.size()-1] == 'b')
        return "r" + l2.substr(0, l2.size()-1);

    // konczy sie na l
    if(l[l.size()-1] == 'l')
    {
        if(l[1] == 's')
            return "si";
        if(l[1] == 'd' && l[2] == 'i')
            return "di";
        return l[1] + "x";
    }

    // reszta
    if(isdigit(l2[0])){
        if(!isdigit(*(l2.end()-1))){
            return "r" + l2.substr(0, l2.size() - 1);
        }
        return "r" + l2;
    }
    return l2;
}

string Registers::getArg(bool pointer, bool bool_) {
    string q;
    if(bool_)
        q = argumentsBool[args_called];

    else if(pointer){
        q = argumentsStrings[args_called];
    } else {
        q = argumentsNumbers[args_called];
    }
    args_called++;
    return "%" + q;
}

string CompilerEnvironment::getTemp(bool pointer) {
    return this->registers.getTemp(pointer);
}

void CompilerEnvironment::addVariable(string name, bool pointer) {
    this->registers.variables[name] =  this->registers.getFree(pointer ? 1 : 0);
    this->registers.defined_here.insert(name);
}

string CompilerEnvironment::getVariable(string name) {
    if(registers.calling() && registers.variables_on_stack.find(name) != registers.variables_on_stack.end()){
        return to_string(this->registers.variables_on_stack[name]) + "(%rbp)";
    } else {
        return this->registers.variables[name];
    }
}

void CompilerEnvironment::removeVariable(string name) {
    this->registers.freeFree(name);
}

void CompilerEnvironment::addArgumentToVariables(string name, bool pointer, bool bool_) {
    string r = this->registers.addArgumentToVariables(name, pointer, bool_);
    this->registers.variables.insert(make_pair(name, r));

}

string Registers::addArgumentToVariables(string name, bool pointer, bool bool_) {
    string reg_name;
    if(bool_)
        reg_name = this->argumentsBool[args];
    else if(pointer)
        reg_name = this->argumentsStrings[args];
    else
        reg_name = this->argumentsNumbers[args];
    args++;
    return '%' + reg_name;
}

string Envs::getNextLabel() {
    return ".L" + to_string(this->next_label++);
}

void Registers::freeArguments() {
}

void Registers::clearArgs(stringstream& ss) {
    //also remembers the temp

    for(auto it = this->variables.begin(); it!= this->variables.end(); ++it){
        ss << "\tpushq " << etor(it->second) << endl;
        variables_on_stack.insert(make_pair(it->first, stackMin));
        stackPointers.insert(make_pair(stackMin, getOperator(it->second)));
        stackMin -= 8;
    }

    if(temps.size()){

        string ft = freeTemp();
        if(ft[0] == '$')
            ss << "\tpushq " << ft << endl;
        else {
            ss << "\tpushq " << etor(ft) << endl;
        }
        stackMin -= 8;
        this->tempOnStack = this->getOperator(ft);
    }
    cal = true;
}

void Registers::restoreArgs(stringstream& ss) {
    //also restores the temp
    if(tempOnStack) {
        stackMin += 8;
        if(tempOnStack == 'b')
        {
            string temp = getBool();
            ss << "\tpopq " << btor(temp) << endl;
        }
        else {
            string temp = getTemp(tempOnStack == 'q');
            ss << "\tpopq " << etor(temp) << endl;
        }
        tempOnStack = 0;
    }

    for(auto it = this->variables.rbegin(); it != this->variables.rend() ; ++it)
    {
        ss << "\tpopq " << etor(it->second) << endl;
        stackMin += 8;
    }
    variables_on_stack.clear();
    stackPointers.clear();
    cal = false;
    args_called = 0;
}

bool Registers::calling() {
    return cal;
}

CompilerEnvironment::CompilerEnvironment() : registers(false, this->registers) {

}

CompilerEnvironment::CompilerEnvironment(bool sameStack, const CompilerEnvironment& ce) : registers(sameStack, ce.registers) {

}

bool Registers::isUsed(string name) {
    auto it = find(arguments.begin(), arguments.end(), name);
    if(it != arguments.end()){
        int pos = it - arguments.begin();
        return pos <= args;
    }
    return used.at(name);
}

string Registers::btor(string e) {
    return short_to_long(long_to_short(e), -1);
}

string Registers::etor(string e) {
    return short_to_long(long_to_short(e), 1);
}

string Registers::rtoe(string r) {
    return short_to_long(long_to_short(r), 0);
}

string Registers::secureRegister(string value, stringstream& program, bool pointer) {
    string res = pointer ? "%r15" : "%r15d";
    if(value[0] == '$') {
        if(pointer)
            program << "\tmovq " << value << ", %r15\n";
        else
            program << "\tmovl " << value << ", %r15d\n";
        return res;
    }
    return value;
}

char Registers::getOperator(const string &name) {
    if(name[1] == 'e' || name[name.size() - 1] == 'd' || name[0] == '$')
        return 'l';
    if(name[name.length()-1] == 'b' || name[name.length()-1] == 'l')
        return 'b';
    char st = getTypeFromStack(name);
    if(st != '0')
    {
        return st;
    }
    return 'q';
}

char Registers::getTypeFromStack(const string &name) {
    auto it = name.find('(');
    if(it == string::npos)
        return '0'; // not on stack
    auto val = stoi(name.substr(0, it));
    return stackPointers[val];
}

bool Registers::undefined(string var_name) {
    return defined_here.find(var_name) == defined_here.end();
}

string Registers::freeBool() {
    return this->freeTemp();
}

string Registers::getBool() {
    string reg_name = this->getFree(-1);
    // cout <<"Getting bool " << reg_name << endl;
    this->temps.push_back(reg_name);
    return reg_name;
}

bool Registers::notARegister(string name) {
    return name[0] == '$' || name[name.size()-1] == ')';
}

string Registers::toOp(string name, short pointer) {
    if(pointer == 1){
        //string
        return etor(name);
    } else if(pointer == 0){
        //int
        return rtoe(name);
    } else {
        //bool
        return short_to_long(long_to_short(name), -1);
    }
}
