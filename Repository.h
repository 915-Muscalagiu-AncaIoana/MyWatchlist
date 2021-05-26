//
// Created by mia on 4/3/2021.
//

#ifndef A67_915_MUSCALAGIU_ANCAIOANA_REPOSITORY_H
#define A67_915_MUSCALAGIU_ANCAIOANA_REPOSITORY_H

#endif //A67_915_MUSCALAGIU_ANCAIOANA_REPOSITORY_H
#include "Tutorial.h"
#include "Validator.h"
#include <vector>
#pragma once

using namespace std;
class Repository{
private:
    vector <Tutorial*> entities;
public:
    Repository();
    //This function adds an entity to the repository(if it is not already in the repository)
    virtual void add_to_repo(Tutorial* elem);
    //This function removes an entity in the repository by its unique identification field (if the entity exists)
    virtual void remove_from_repo(char* entity_title);
    //This function searches in the repository an elem by its unique identification field
    virtual int search_in_repo(char* entity_title);
    //This function updates an entity in the repo(if there is already an entity with the respective identification field)
    virtual void update_in_repo(Tutorial* elem);
    //This function returns all the entities in the repo
    virtual vector <Tutorial*> get_entities();
    //This function frees the memory allocated for the repository
    virtual string get_system_command();

    virtual ~Repository();
};


class TextFileRepository : public Repository{
private:
    vector <Tutorial*> entities;
    string path;
public:
    explicit TextFileRepository(string path);
    void add_to_repo(Tutorial* elem) override;
    void remove_from_repo(char* entity_title) override;
    void update_in_repo(Tutorial* elem) override;
    void load_from_file();
    void save_to_file();

};

class CSVRepository : public Repository{
private:
    vector <Tutorial*> entities;
    string path;
public:
    explicit CSVRepository(string path);
    void save_to_file();
    void add_to_repo(Tutorial* elem) override;
    void remove_from_repo(char* entity_title) override;
    void update_in_repo(Tutorial* elem) override;
    string get_system_command() override;
};

class HTMLRepository : public Repository{
private:
    vector <Tutorial*> entities;
    string path;
public:
    explicit HTMLRepository(string path);
    void save_to_file();
    void add_to_repo(Tutorial* tutorial) override;
    void remove_from_repo(char* entity_title) override;
    void update_in_repo(Tutorial* elem) override;
    string get_system_command() override;

};

