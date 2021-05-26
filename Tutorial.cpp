//
// Created by mia on 4/3/2021.
//

#include "Tutorial.h"

#include <string.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Tutorial::Tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]) {
    strcpy(this->title, title);
    strcpy(this->presenter, presenter);
    this->duration.minutes = minutes;
    this->duration.seconds = seconds;
    this->likes = likes;
    strcpy(this->link, link);
}

Tutorial::Tutorial(Tutorial* tutorial)
{
    strcpy(this->title, tutorial->title);
    strcpy(this->presenter, tutorial->presenter);
    this->duration.minutes = tutorial->duration.minutes;
    this->duration.seconds = tutorial->duration.seconds;
    this->likes = tutorial->likes;
    strcpy(this->link, tutorial->link);
}

char *Tutorial::getTitle() { return this->title; };

int Tutorial::getMinutes() { return this->duration.minutes;}

int Tutorial::getSeconds(){return this->duration.seconds;}

int Tutorial::getLikes(){return this->likes;}

char *Tutorial::getLink(){return this->link;}

char *Tutorial::getPresenter() { return this->presenter; }

//std::ostream &operator<<(std::ostream &os, const Tutorial &tutorial) {
//    os << "Title: " << tutorial.title << "\nPresenter: " << tutorial.presenter << "\nMinutes: "
//       << tutorial.duration.minutes << "\nSeconds: " << tutorial.duration.seconds << "\nLikes: " << tutorial.likes
//       << "\nLink: " << tutorial.link;
//    return os;
//}

std::ostream &operator<<(std::ostream &os, const Tutorial &tutorial) {
    os << tutorial.title << "," << tutorial.presenter << ","
       << tutorial.duration.minutes << "," << tutorial.duration.seconds << "," << tutorial.likes
       << "," << tutorial.link;
    return os;
}

Tutorial::Tutorial() {

}

void Tutorial::setLikes(int likes) {
    Tutorial::likes = likes;
}

void Tutorial::setTitle(char *title) {
    strcpy(this->title,title);
}

void Tutorial::setPresenter(char *presenter) {
    strcpy(this->presenter,presenter);
}

void Tutorial::setMinutes(int minutes) {
    this->duration.minutes=minutes;
}

void Tutorial::setSecond(int seconds) {
    this->duration.seconds=seconds;
}

void Tutorial::setLink(char *link) {
    strcpy(this->link,link);
}


std::istream &operator>>(std::istream &is, Tutorial* tutorial){
    string line;
    getline(is,line);

    vector<string> tokens;
    string delimiter=",";
    size_t pos;
    string token;
    while ((pos = line.find(delimiter))!= std::string::npos) {
        token = line.substr(0,pos);
        tokens.push_back(token);
        line.erase(0,pos+delimiter.length());
    }
    tokens.push_back(line);
    if (tokens.size() != 6)
        return is;
    tutorial->setTitle((char*)tokens[0].c_str());
    tutorial->setPresenter((char*)tokens[1].c_str());
    tutorial->setMinutes(stoi(tokens[2]));
    tutorial->setSecond(stoi(tokens[3]));
    tutorial->setLikes(stoi(tokens[4]));
    tutorial->setLink((char*)tokens[5].c_str());
    return is;
}

string Tutorial::toString() {
    std::string titlu(this->title);
    std::string prez(this->presenter);
    std::string lik(this->link);
    string str = titlu + "," +prez + ","
       +to_string(this->duration.minutes) + "," + to_string(this->duration.seconds) + "," + to_string(this->likes)
       + "," + lik;
    return str;
}
