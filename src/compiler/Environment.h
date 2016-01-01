//
// Created by msusik on 01.01.16.
//

#ifndef LATTE_ENVIRONMENT_H
#define LATTE_ENVIRONMENT_H

#include <map>
#include <string>
#include "../Absyn.H"

using namespace std;

class Environment {
public:
    bool is_variable_declared(string variable);
    void add_variable(string name, Type *type);
    Type *get_type(string name);
private:
    map<string, Type*> declared_variables; //name->type
};


#endif //LATTE_ENVIRONMENT_H
