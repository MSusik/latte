//
// Created by msusik on 01.01.16.
//

#include "Environment.h"

#include<iostream>

bool Environment::is_variable_declared(string variable) {
    return this->declared_variables.find(variable) != this->declared_variables.end();
}

void Environment::add_variable(string name, Type *type) {
    this->declared_variables.insert(make_pair(name, type));
    // cerr << name << " inserted" << endl;
}

Type *Environment::get_type(string name) {
    // cerr << "getting " << name << " avail " << this->declared_variables.size() << endl;
    try {
        return this->declared_variables.at(name);
    } catch (const std::out_of_range& oor) {
        // variable undeclared
        return nullptr;
    }
}
