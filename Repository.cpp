//
// Created by mia on 5/5/2021.
//

#include "Repository.h"
//
// Created by mia on 3/18/2021.
//

#include "Repository.h"
#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>

#pragma secure_delete=ON

void Repository::add_to_repo(Tutorial *elem) {
    char *entity_title = elem->getTitle();
    int index = this->search_in_repo(entity_title);
    if (index == -1)
        this->entities.push_back(elem);
    else
        throw RepositoryException("There is already a tutorial with this title");
}

void Repository::remove_from_repo(char *entity_title) {
    int index_removed = this->search_in_repo(entity_title);
    if (index_removed == -1)
        throw RepositoryException("There is no tutorial with this title");
    this->entities.erase(this->entities.begin() + index_removed);
}

int Repository::search_in_repo(char *entity_title) {
    int index;

    for (auto it = this->entities.begin(); it != this->entities.end(); ++it)
        if (strcmp((*it)->getTitle(), entity_title) == 0)
            return it - this->entities.begin();
    return -1;

}

void Repository::update_in_repo(Tutorial *elem) {
    char *entity_title = elem->getTitle();
    int index_updated = this->search_in_repo(entity_title);
    if (index_updated == -1)
        throw RepositoryException("There is no tutorial with this title");
    delete this->entities[index_updated];
    this->entities[index_updated] = elem;

}

vector<Tutorial *> Repository::get_entities() {
    return this->entities;
}

Repository::~Repository() {
    for (auto it = this->entities.begin(); it != this->entities.end(); ++it)
        delete *it;
}

Repository::Repository() {

}

string Repository::get_system_command() {
    return "";
}



TextFileRepository::TextFileRepository(string path) {
    this->path = path;
    this->load_from_file();
}

void TextFileRepository::load_from_file() {
    ifstream file(this->path);
    Tutorial *tutorial = new Tutorial;
    while (file >> tutorial) {
        Repository::add_to_repo(tutorial);
        tutorial = new Tutorial;
    }
    file.close();
}

void TextFileRepository::add_to_repo(Tutorial *elem) {
    Repository::add_to_repo(elem);
    save_to_file();
}

void TextFileRepository::remove_from_repo(char *entity_title) {
    Repository::remove_from_repo(entity_title);
    save_to_file();
}

void TextFileRepository::update_in_repo(Tutorial *elem) {
    Repository::update_in_repo(elem);
    save_to_file();
}

void TextFileRepository::save_to_file() {
    ofstream file(this->path);
    if (!file.is_open())
        return;
    for (auto tutorial : this->get_entities()) {
        file << *tutorial << '\n';
    }
    file.close();
}


CSVRepository::CSVRepository(string path) {
    this->path = path;
}


string CSVRepository::get_system_command() {
    string command = "notepad ";
    string result = command + this->path;
    return result;
}

void CSVRepository::save_to_file() {
    ofstream file(this->path);
    if (!file.is_open())
        return;
    for (auto tutorial : this->get_entities()) {
        file << *tutorial << '\n';
    }
    file.close();
}

void CSVRepository::add_to_repo(Tutorial *elem) {
    Repository::add_to_repo(elem);
    this->save_to_file();
}

void CSVRepository::remove_from_repo(char *entity_title) {
    Repository::remove_from_repo(entity_title);
    this->save_to_file();
}

void CSVRepository::update_in_repo(Tutorial *elem) {
    Repository::update_in_repo(elem);
    this->save_to_file();
}


HTMLRepository::HTMLRepository(string path) {
    this->path = path;
}

void HTMLRepository::save_to_file() {
    ofstream file(this->path);
    if (!file.is_open())
        return;

    file << "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <title>Tutorial</title>\n"
            "</head>\n"
            "<body>\n"
            "<table border=\"1\">\n"
            "    <tr> \n"
            "    <td>Title</td>\n"
            "    <td>Presenter</td>\n"
            "    <td>Duration</td>\n"
            "    <td>Likes</td>\n"
            "    <td>Link</td>\n"
            "    </tr>\n";


    for (auto tutorial : this->get_entities()) {
        string duration = to_string(tutorial->getMinutes());
        duration = duration + ":";
        duration = duration + to_string(tutorial->getSeconds());
        string likes = to_string(tutorial->getLikes());
        file << "<tr>\n";
        file << "<td>" << tutorial->getTitle() << "</td>\n";
        file << "<td>" << tutorial->getPresenter() << "</td>\n";
        file << "<td>" << duration << "</td>\n";
        file << "<td>" << likes << "</td>\n";
        file << "<td><a href=\"" << tutorial->getLink() << "\">Link</a></td>\n";
        file << "</tr>\n";
    }

    file << "</tr>\n";
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";
    file.close();
}


void HTMLRepository::add_to_repo(Tutorial *tutorial) {
    Repository::add_to_repo(tutorial);
    this->save_to_file();
}

void HTMLRepository::remove_from_repo(char *entity_title) {
    Repository::remove_from_repo(entity_title);
    this->save_to_file();
}

void HTMLRepository::update_in_repo(Tutorial *elem) {
    Repository::update_in_repo(elem);
    this->save_to_file();
}

string HTMLRepository::get_system_command() {
    string command = "start ";
    string result = command + this->path;
    return result;
}


