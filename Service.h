//
// Created by mia on 4/3/2021.
//

#ifndef A67_915_MUSCALAGIU_ANCAIOANA_SERVICES_H
#define A67_915_MUSCALAGIU_ANCAIOANA_SERVICES_H

#endif //A67_915_MUSCALAGIU_ANCAIOANA_SERVICES_H

#pragma once
#include "Repository.h"

#include <vector>
#include <map>
#include "ServiceUndo.h"

class Services_Tutorial {
private:
    Validator *validator;
    ServiceUndo* serviceUndo;
    ServiceUndoWatchlist* serviceUndoWatchlist;
    Repository *repository;
    Repository *repository_watchlist;
public:
    //This function creates a service with a repository of tutorials and a validator
    Services_Tutorial(Repository *repository, Repository *repository_watchlist,ServiceUndo* serviceUndo, ServiceUndoWatchlist* serviceUndoWatchlist, Validator *validator);

    //This function creates a tutorial with the given input, validates and adds it to the repository of tutorials
    void add_tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]);

    //This function generates 10 tutorials at the start of program
    void generate_initial();

    //This function removes a tutorial with a given title from the repository of the tutorials
    void remove_tutorial(char title[]);

    //This function validates the new info about the tutorial and updates the tutorial in the repository of tutorials
    void update_tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]);

    //This function returns all the tutorials available in the program
    vector<Tutorial*> get_tutorials();

    //This function frees the memory occupied by the service
    virtual ~Services_Tutorial();

    //This function filters the tutorials by a given presenter; if the presenter name is empty then it returns all the tutorials
    vector<Tutorial*> filter_by_presenter(char presenter[]);

    //This function adds a tutorial to the user's watchlist
    void add_tutorial_to_watchlist(char title[]);

    //This function rates a tutorial by increasing its number of likes with 1
    void rate_a_tutorial(char title[]);


    //This function returns the watchlist of the user
    vector<Tutorial*> get_watchlist();

    //This function deletes a tutorial from the watchlist of the user
    void delete_tutorial_from_watchlist(char title[]);

    //This function returns the validator of the service
    Validator *get_validator() const;

    void set_repo(Repository* repository);

    string get_system_command();

    vector<string> get_presenters();

    map <string,float> average_minutes();

    map <string,float> average_likes();

    void undoOp();
    void redoOp();

    void undoWatchlistOp();
    void redoWatchlistOp();
};