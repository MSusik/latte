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
    used.insert(make_pair("r15", false));
}


Registers::Registers(bool sameStack, const Registers& reg) : Registers() {
    if(sameStack)
    {
        cout << "SAME STACK" << endl;
        variables_on_stack = reg.variables_on_stack;
    }
    cout << variables_on_stack.size() << " REG" << endl;
}

vector<int> Registers::call_function(vector<pair<string, bool>> pointers) {
    //unused
    vector<int> leftovers;
    int index = 0;
    for(auto it= pointers.begin(); it != pointers.end(); ++it)
    {

        used[arguments[index++]] = true;
        if(index > 6)
            break; // TODO
    }
    return leftovers;
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
    if(sameStack) {
        newEnv.stackShifts = this->top().stackShifts;
    }

    cout << "Adding new env" << endl;
    this->envs.push(newEnv);
}

void Envs::removeEnv() {
    envs.pop();
}

CompilerEnvironment &Envs::top() {
    return envs.top();
}

void CompilerEnvironment::saveRegisters(stringstream *ss) {
    (*ss) << "\tpushq rdi\n";
    (*ss) << "\tpushq rsi\n";
    (*ss) << "\tpushq rdx\n";
    (*ss) << "\tpushq rcx\n";
    (*ss) << "\tpushq r8\n";
    (*ss) << "\tpushq r9\n";
}

void CompilerEnvironment::freeRegisters(stringstream *ss) {
    (*ss) << "\tpopq r9\n";
    (*ss) << "\tpopq r8\n";
    (*ss) << "\tpopq rcx\n";
    (*ss) << "\tpopq rdx\n";
    (*ss) << "\tpopq rsi\n";
    (*ss) << "\tpopq rdi\n";
}

string CompilerEnvironment::freeTemp() {
    return this->registers.freeTemp();
}

void CompilerEnvironment::putArg(stringstream *ss) {
    /// to co jest na topie
    string reg = this->registers.getArg(false);
    string value = this->registers.freeTemp();
    (*ss) << "\tmovl " << value << ", " << reg <<"\n";
}


string Registers::getFree(bool pointer) {
    string th = "";
    for(auto it = this->used.begin(); it != this->used.end(); ++it)
    {
        if(!it->second){
            th = it->first;
        }

    }
    this->used[th] = true;
    string reg_name = this->short_to_long(th, pointer);
    //cout << "Getting " << reg_name << endl;
    return "%" + reg_name;
}


string Registers::getTemp(bool pointer) {
    string reg_name = this->getFree(pointer);
    this->temps.push_back(reg_name);
    return reg_name;
}


string Registers::freeFree(string reg_name) {
    string short_name = this->long_to_short(reg_name);
    this->used[short_name] = false;
    //cout << "Freeing " << reg_name << endl;
    return reg_name;
}

string Registers::freeTemp() {
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
    this->temps.pop_back();
    return reg_name;
}

string Registers::short_to_long(string s, bool pointer) {
    if(pointer)
    {
        if(s[0] == 'r')
            return s;
        else
            return "r" + s;
    } else
    {
        if(s[0] == 'r')
            return s + "d";
        else
            return "e" + s;

    }
}

string Registers::long_to_short(string l) {
    string l2 = l.substr(2);
    if(isdigit(l2[0])){
        if(!isdigit(*(l2.end()-1))){
            return "r" + l2.substr(0, l2.size() - 1);
        }
        return "r" + l2;
    }
    return l2;
}

string Registers::getArg(bool pointer) {
    string q;
    if(pointer){
        q = argumentsStrings[args];
    } else {
        q = argumentsNumbers[args];
    }
    args++;
    return "%" + q;
}

void Registers::freeArgs() {
    args = 0;
}

string CompilerEnvironment::getTemp(bool pointer) {
    return this->registers.getTemp(pointer);
}

void CompilerEnvironment::addVariable(string name, bool pointer) {
    this->registers.variables.insert(make_pair(name, this->registers.getFree(pointer)));
}

string CompilerEnvironment::getVariable(string name) {
    if(registers.calling()){
        return to_string(this->registers.variables_on_stack[name]) + "(%rbp)";
    } else {
        return this->registers.variables[name];
    }
}

void CompilerEnvironment::removeVariable(string name) {
    this->registers.freeFree(name);
}

void CompilerEnvironment::addArgumentToVariables(string name, bool pointer) {
    string r = this->registers.addArgumentToVariables(name, pointer);
    this->registers.variables.insert(make_pair(name, r));

}

string Registers::addArgumentToVariables(string name, bool pointer) {
    string reg_name;
    if(pointer)
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
    args=0;
}

void Registers::clearArgs(stringstream *ss) {
    for(int i = 0; i < args; ++i)
    {
        (*ss) << "\tpushl %" << argumentsNumbers[i] << endl;
        for(auto it = this->variables.begin(); it!= this->variables.end(); ++it){
            if(it->second == "%" + argumentsNumbers[i]) {
                variables_on_stack.insert(make_pair(it->first, stackMin));
                stackMin -= 8;
                break;
            }
        }

    }
    args2 = args;
    args = 0;
}

void Registers::restoreArgs(stringstream *ss) {
    int index = 0;
    for(auto i = this->variables_on_stack.begin(); i != this->variables_on_stack.end() ; ++i)
    {
        (*ss) << "\tpopl %" << argumentsNumbers[index] << endl;
        stackMin += 8;
    }
    variables_on_stack.clear();
    args = args2;
    args2 = 0;
}

bool Registers::calling() {
    return args2 > 0;
}

CompilerEnvironment::CompilerEnvironment() : registers(false, this->registers) {

}

CompilerEnvironment::CompilerEnvironment(bool sameStack, const CompilerEnvironment& ce) : registers(sameStack, ce.registers) {

}
