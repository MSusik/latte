//
// Created by msusik on 26.12.15.
//

#ifndef LATTE_UTILS_H
#define LATTE_UTILS_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class ErrorState {
public:
    bool error = false;
    vector<pair<int, string>> messages;
    void printMessage(pair<int, string> pair)
    {
        cerr << "Line " << pair.first << ": " << pair.second << endl;
    };
    void addError(int line_number, string message)
    {
        this->error = true;
        this->messages.push_back(make_pair(line_number, message));
    };
};

#endif //LATTE_UTILS_H
