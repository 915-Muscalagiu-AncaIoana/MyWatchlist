//
// Created by mia on 4/3/2021.
//

#ifndef A67_915_MUSCALAGIU_ANCAIOANA_VALIDATOR_H
#define A67_915_MUSCALAGIU_ANCAIOANA_VALIDATOR_H

#endif //A67_915_MUSCALAGIU_ANCAIOANA_VALIDATOR_H
#pragma once
#include <string>
#include <exception>
using namespace std;
class Validator{
public:
    //This function validates the info about a tutorial: the title, presenter and link must not be empty and the minutes
    //seconds and likes must be positive integers.
    int validate_tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]);
    //This function validates an option inputted by the user
    int validate_option(char op[]);
    //This function checks if an input read as a string can be converted to an integer
    int is_integer(char * string);
};

class RepositoryException : public std::exception{
    string message;
public:
    RepositoryException(std::string message) :message(message) {};
    string getMessage() { return this->message; };
};

class ValidatorException : public std::exception {
    string message;
public:
    ValidatorException(std::string message) :message(message) {};
    string getMessage() { return this->message; };
};

class InputException : public std::exception {
    std::string message;
public:
    InputException(std::string message) :message(message) {};
    string getMessage() { return this->message; };
};