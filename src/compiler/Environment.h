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
    Environment();
    Environment(map<string, pair<Type*, bool>> p);
    bool is_variable_declared(string variable);
    bool is_variable_declared_here(string variable);
    void add_variable(string name, Type *type);
    Type *get_type(string name);
    map<string, pair<Type*, bool>> get_previous();
private:
    map<string, pair<Type*, bool>> declared_variables; //name->type
};


#endif //LATTE_ENVIRONMENT_H
