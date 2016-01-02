//
// Created by msusik on 01.01.16.
//

#include "Environment.h"

#include<iostream>

bool Environment::is_variable_declared(string variable)
{
    //cerr << "Checking for " << variable << " av " << declared_variables.size() <<endl;
    auto it = this->declared_variables.find(variable);
    return it != this->declared_variables.end();
}

bool Environment::is_variable_declared_here(string variable)
{
    //cerr << "Checking for dec " << variable << " av " << declared_variables.size() <<endl;
    auto it = this->declared_variables.find(variable);
    if(it != this->declared_variables.end()){
        return it->second.second;
    }
    return false;
}

void Environment::add_variable(string name, Type *type) {
    //cerr << "Adding " << name << endl;
    auto it = this->declared_variables.find(name);
    if(it != this->declared_variables.end())
    {
        this->declared_variables[name] = make_pair(type, true);
    } else
    {
        this->declared_variables.insert(make_pair(name, make_pair(type, true)));
    }
}

Type *Environment::get_type(string name) {

    try {
        return this->declared_variables.at(name).first;
    } catch (const std::out_of_range& oor) {
        // variable undeclared
        return nullptr;
    }
}

map<string, pair<Type *, bool>> Environment::get_previous() {
    // switches all trues to false
    map<string, pair<Type*, bool>> result;
    for( auto it =this->declared_variables.begin(); it != this->declared_variables.end(); ++it )
    {
        result.insert(make_pair(it->first, make_pair(it->second.first, false)));
    }
    return result;
}

Environment::Environment(map<string, pair<Type *, bool>> p) : declared_variables(p){}

Environment::Environment() {

}
