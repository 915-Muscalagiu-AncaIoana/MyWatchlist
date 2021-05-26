//
// Created by mia on 5/5/2021.
//

#include "Validator.h"
#include "Validator.h"
#include <cstring>
int Validator::validate_tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]) {
    if (minutes < 0)
        throw ValidatorException("The number of minutes must be a positive integer");
    if (seconds < 0)
        throw ValidatorException("The number of seconds must be a positive integer");
    if(likes<0)
        throw ValidatorException("The number of likes must be a positive integer");
    if (strlen(link) == 0)
        throw ValidatorException("The link cannot be empty");
    if(strlen(title) == 0)
        throw ValidatorException("The title cannot be empty");
    if(strlen(presenter) == 0)
        throw ValidatorException("The presenter cannot be empty");

    return 1;
}

int Validator::validate_option(char op[]) {
    if (strlen(op) != 1)
        return 0;
    if (!((op[0] >= '0') && (op[0] <= '9')))
        return 0;
    return 1;
}

int Validator::is_integer(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] < '0' || string[i] > '9')
            return 0;
    }
    return 1;
}