//
// Created by msusik on 02.01.16.
//

#ifndef LATTE_COMPILERENVIRONMENT_H
#define LATTE_COMPILERENVIRONMENT_H

#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<stack>
#include<sstream>
#include<utility>
#include<vector>

using namespace std;

class Registers {
private:
    map<string, bool> used; //is register used
    vector<string> argumentsNumbers = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};
    vector<string> argumentsStrings = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    vector<string> argumentsBool = {"dil", "sil", "dl", "cl", "r8b", "r9b"};
    vector<string> arguments = {"di", "si", "dx", "cx", "r8", "r9"};
    int args = 0;
    int args_called = 0;
    int stackMin = -8;
    map<int, char> stackPointers; // true if pointer
public:
    set<string> defined_here;
    map<string, int> variables_on_stack;
    map<string, string> variables;
    Registers();
    Registers(bool sameStack, const Registers& reg);
    string getTemp(bool pointer);
    string freeFree(string name);
    string getFree(short pointer);
    string getArg(bool pointer, bool bool_=false);
    string freeTemp(bool pop=true);
    string short_to_long(string s, short pointer);
    string long_to_short(string l);
    string addArgumentToVariables(string name, bool pointer, bool bool_);
    void freeArguments();
    vector<string> temps;
    string etor(string e);
    string rtoe(string r);
    void clearArgs(stringstream& ss);
    void restoreArgs(stringstream& ss);
    bool isUsed(string name);
    bool calling();

    string secureRegister(string value, stringstream& program, bool pointer);

    char tempOnStack = 0;

    char getOperator(const string &name);
    char getTypeFromStack(const string &name);

    bool cal = false;

    bool undefined(string var_name);

    string freeBool();

    string getBool();

    bool notARegister(string name);

    string toOp(string name, short pointer);

    string btor(string e);
};


class CompilerEnvironment {
public:
    CompilerEnvironment();

    CompilerEnvironment(bool d, const CompilerEnvironment& ce);

    Registers registers;
    void putArg(stringstream& ss);
    string freeTemp();
    string getTemp(bool pointer);
    void addVariable(string name, bool pointer);
    void addArgumentToVariables(string name, bool pointer, bool bool_);
    string getVariable(string name);
    void removeVariable(string name);
};

class Envs {
private:
    stack<CompilerEnvironment> envs;
    int next_label = 0;
public:
    void addEnv(bool sameStack);
    void removeEnv();
    CompilerEnvironment& top();
    string getNextLabel();

};


#endif //LATTE_COMPILERENVIRONMENT_H
