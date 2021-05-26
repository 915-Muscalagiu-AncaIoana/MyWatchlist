//
// Created by mia on 4/3/2021.
//

#ifndef A67_915_MUSCALAGIU_ANCAIOANA_TUTORIAL_H
#define A67_915_MUSCALAGIU_ANCAIOANA_TUTORIAL_H
#pragma once
#endif //A67_915_MUSCALAGIU_ANCAIOANA_TUTORIAL_H
#include <ostream>
#include <string>
using namespace std;
typedef struct timp
{
    int minutes;
    int seconds;
}timp;

class Tutorial {
private:
    char title[201];
    char presenter[201];
    timp duration;
    int likes;
    char link[201];
public:
    //This function creates a tutorial with a given title, presenter, duration(in minutes and seconds),number of likes and link
    Tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]);
    Tutorial(Tutorial* tutorial);
    Tutorial();
    //This function returns the title of the tutorial
    char *getTitle() ;
    //This function returns the presenter of the tutorial
    char *getPresenter() ;
    //This function returns the number of minutes of the tutorial
    int getMinutes();
    //This function returns the number of seconds of the tutorial
    int getSeconds();
    //This function returns the number of likes of the tutorial
    int getLikes();
    //This function returns the link of the tutorial
    char *getLink();
    friend std::ostream &operator<<(std::ostream &os, const Tutorial &tutorial);
    friend std::istream &operator>>(std::istream &is, Tutorial* tutorial);
    void setTitle(char* title);
    void setPresenter(char* presenter);
    void setMinutes(int minutes);
    void setSecond(int seconds);
    void setLikes(int likes);
    void setLink(char* link);
    string toString();
};