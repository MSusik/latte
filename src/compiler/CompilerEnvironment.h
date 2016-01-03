//
// Created by msusik on 02.01.16.
//

#ifndef LATTE_COMPILERENVIRONMENT_H
#define LATTE_COMPILERENVIRONMENT_H

#include<algorithm>
#include<map>
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
    vector<string> arguments = {"di", "si", "dx", "cx", "r8", "r9"};
    int args = 0;
    int args2 = 0;
    int stackMin = -8;
public:
    map<string, int> variables_on_stack;
    map<string, string> variables;
    Registers();
    Registers(bool sameStack, const Registers& reg);
    string getTemp(bool pointer);
    string freeFree(string name);
    string getFree(bool pointer);
    string getArg(bool pointer);
    void freeArgs();
    string freeTemp();
    string short_to_long(string s, bool pointer);
    string long_to_short(string l);
    string addArgumentToVariables(string name, bool pointer);
    void freeArguments();
    vector<string> temps;
    string etor(string e);
    string rtoe(string r);
    void clearArgs(stringstream *ss);
    void restoreArgs(stringstream *ss);
    bool isUsed(string name);
    bool calling();

    void addUsed(string used_);

    string secureRegister(string value, stringstream *program, bool pointer);

    char tempOnStack = 0;

    char getOperator(const string &name);
};


class CompilerEnvironment {
public:
    CompilerEnvironment();

    CompilerEnvironment(bool d, const CompilerEnvironment& ce);

    Registers registers;
    map<string, int> stackShifts; // 0 if in register
    void putArg(stringstream *ss);
    string freeTemp();
    string getTemp(bool pointer);
    void addVariable(string name, bool pointer);
    void addArgumentToVariables(string name, bool pointer);
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
