//
// Created by mia on 4/3/2021.
//

#include "Service.h"

#include <exception>
#include <cstring>
#include <algorithm>

Services_Tutorial::Services_Tutorial(Repository *repository, Repository *repository_watchlist, ServiceUndo* serviceUndo, ServiceUndoWatchlist* serviceUndoWatchlist, Validator *validator) {
    this->repository = repository;
    this->repository_watchlist = repository_watchlist;
    this->validator = validator;
    this->serviceUndoWatchlist = serviceUndoWatchlist;
this->serviceUndo = serviceUndo;
}

Validator *Services_Tutorial::get_validator() const {
    return validator;
}

void Services_Tutorial::add_tutorial(char title[], char presenter[], int minutes, int seconds, int likes, char link[]) {

    this->validator->validate_tutorial(title, presenter, minutes, seconds, likes, link);

    Tutorial *tutorial = new Tutorial(title, presenter, minutes, seconds, likes, link);
    Tutorial *tutorial_rec = new Tutorial(title, presenter, minutes, seconds, likes, link);
    UndoRedoAdd* op = new UndoRedoAdd(repository,*tutorial_rec);

    this->repository->add_to_repo(tutorial);
    serviceUndo->record(op);
}

void Services_Tutorial::generate_initial() {
    add_tutorial("Java Tutorial for Beginners (2020)", "Programming with Mosh", 150, 47, 104000,
                 "https://www.youtube.com/watch?v=eIrMbAQSU34");
    add_tutorial("Learn Python - Full Course for Beginners [Tutorial]", "freeCodeCamp.org", 266, 51, 560000,
                 "https://www.youtube.com/watch?v=rfscVS0vtbw&t=14265s");
    add_tutorial("Intro to Data Science - Crash Course for Beginners", "freeCodeCamp.org", 89, 48, 3100,
                 "https://www.youtube.com/watch?v=N6BghzuFLIg");
    add_tutorial("Microsoft .NET Tutorial - Intro to .NET (Part 01)", "ICT Tutorial Channel", 36, 29, 2100,
                 "https://www.youtube.com/watch?v=iRSAmekqRBo");
    add_tutorial("Learn JavaScript - Full Course for Beginners", "freeCodeCamp.org", 206, 42, 110000,
                 "https://www.youtube.com/watch?v=PkZNo7MFNFg");
    add_tutorial("Node.js Ultimate Beginner's Guide in 7 Easy Steps", "Fireship", 16, 19, 14000,
                 "https://www.youtube.com/watch?v=ENrzD9HAZK4");
    add_tutorial("C++ FULL COURSE For Beginners (Learn C++ in 10 hours)", "CodeBeauty", 16, 19, 14000,
                 "https://www.youtube.com/watch?v=GQp1zzTwrIg");
    add_tutorial("Intermediate Python Programming Course", "freeCodeCamp.org", 355, 46, 18000,
                 "https://www.youtube.com/watch?v=HGOBQPFzWKo");
    add_tutorial("C Programming | In One Video", "Mike Dane", 25, 40, 2700,
                 "https://www.youtube.com/watch?v=3lQEunpmtRA&t=3s");
    add_tutorial("Rust Crash Course | Rustling", "Traversity Media", 110, 43, 8500,
                 "https://www.youtube.com/watch?v=zF34dRivLOw");
}

void Services_Tutorial::remove_tutorial(char title[]) {
    int index = this->repository->search_in_repo(title);
    if (index == -1)
        throw RepositoryException("There is no tutorial wit this title!");
    Tutorial *tutorial= this->repository->get_entities()[index];
    Tutorial *tutorial_rec = new Tutorial(tutorial->getTitle(),tutorial->getPresenter(),tutorial->getMinutes(),tutorial->getSeconds(),tutorial->getLikes(),tutorial->getLink());
    this->repository->remove_from_repo(title);
    UndoRedoRemove* op = new UndoRedoRemove(repository,*tutorial_rec);
    serviceUndo->record(op);
}

void Services_Tutorial::update_tutorial(char title[], char presenter[], int new_minutes, int new_seconds, int new_likes,
                                        char new_link[]) {


    Tutorial *new_tutorial = new Tutorial(title, presenter, new_minutes, new_seconds, new_likes, new_link);
    int index = this->repository->search_in_repo(title);
    if (index == -1)
        throw RepositoryException("There is no tutorial wit this title!");
    Tutorial *tutorial= this->repository->get_entities()[index];
    Tutorial * tutorial_old = new Tutorial(tutorial->getTitle(),tutorial->getPresenter(),tutorial->getMinutes(),tutorial->getSeconds(),tutorial->getLikes(),tutorial->getLink());
    Tutorial* tutorial_rec = new Tutorial(title, presenter, new_minutes, new_seconds, new_likes, new_link);
    UndoRedoUpdate* op = new UndoRedoUpdate(repository,*tutorial_rec,tutorial_old);

    this->validator->validate_tutorial(title, presenter, new_minutes, new_seconds, new_likes, new_link);
    this->repository->update_in_repo(new_tutorial);
    serviceUndo->record(op);
}

vector<Tutorial *> Services_Tutorial::get_tutorials() {
    return this->repository->get_entities();
}

vector<Tutorial *> Services_Tutorial::filter_by_presenter(char presenter[]) {
    if (strlen(presenter) == 0)
        return this->get_tutorials();

    vector<Tutorial *> tutorials = this->repository->get_entities();

    auto it_f = tutorials.begin();
    auto it_l=tutorials.end();

    tutorials.erase(remove_if(it_f,it_l,[&presenter](Tutorial* tutorial) {return strcmp(tutorial->getPresenter(),presenter) !=0; }),it_l);
    return tutorials;
}

void Services_Tutorial::add_tutorial_to_watchlist(char title[]) {
    int position = this->repository->search_in_repo(title);
    char presenter[201];
    char link[201];
    strcpy(presenter, this->repository->get_entities()[position]->getPresenter());
    strcpy(link, this->repository->get_entities()[position]->getLink());
    int minutes, seconds, likes;
    minutes = this->repository->get_entities()[position]->getMinutes();
    seconds = this->repository->get_entities()[position]->getSeconds();
    likes = this->repository->get_entities()[position]->getLikes();
    Tutorial *tutorial = new Tutorial(title, presenter, minutes, seconds, likes, link);
    Tutorial *tutorial_rec = new Tutorial(title, presenter, minutes, seconds, likes, link);
    UndoRedoAddWatchlist* op = new UndoRedoAddWatchlist(repository,repository_watchlist,*tutorial_rec);

    this->repository_watchlist->add_to_repo(tutorial);
    serviceUndoWatchlist->record(op);
}

void Services_Tutorial::delete_tutorial_from_watchlist(char title[]) {
    int index = this->repository->search_in_repo(title);
    if (index == -1)
        throw RepositoryException("There is no tutorial wit this title!");
    Tutorial *tutorial= this->repository->get_entities()[index];
    Tutorial *tutorial_rec = new Tutorial(tutorial->getTitle(),tutorial->getPresenter(),tutorial->getMinutes(),tutorial->getSeconds(),tutorial->getLikes(),tutorial->getLink());
    Tutorial *tutorial_new = new Tutorial(tutorial_rec);
    tutorial_new->setLikes(tutorial_new->getLikes()+1);
    UndoRedoRemoveWatchlist* op = new UndoRedoRemoveWatchlist(repository,repository_watchlist,*tutorial_rec,*tutorial_new);

    this->repository_watchlist->remove_from_repo(title);
    serviceUndoWatchlist->record(op);

}

void Services_Tutorial::rate_a_tutorial(char title[]) {
    int position = this->repository->search_in_repo(title);
    char presenter[201];
    char link[201];
    strcpy(presenter, this->repository->get_entities()[position]->getPresenter());
    strcpy(link, this->repository->get_entities()[position]->getLink());
    int minutes, seconds, likes;
    minutes = this->repository->get_entities()[position]->getMinutes();
    seconds = this->repository->get_entities()[position]->getSeconds();
    likes = this->repository->get_entities()[position]->getLikes();
    this->update_tutorial(title, presenter, minutes, seconds, likes + 1, link);
}

vector<Tutorial *> Services_Tutorial::get_watchlist() {
    return this->repository_watchlist->get_entities();
}

Services_Tutorial::~Services_Tutorial() {
    delete this->repository;
    delete this->repository_watchlist;
    delete this->validator;
}

void Services_Tutorial::set_repo(Repository *repository) {
    this->repository_watchlist=repository;

}

string Services_Tutorial::get_system_command() {
    return this->repository_watchlist->get_system_command();
}

vector<string> Services_Tutorial::get_presenters() {
    vector <string> presenters;
    for(auto it: this->get_tutorials())
    { bool exists = false;
        string current_presenter = it->getPresenter();
        for( auto presenter : presenters)
            if (presenter == current_presenter)
            {exists= true;
                break;}
        if (!exists)
            presenters.push_back(current_presenter);
    }
    return presenters;
}

map <string,float> Services_Tutorial::average_minutes() {
    vector <string> presenters = get_presenters();
    map <string,float> minutes ;
    map <string,int> times;

    for (auto tutorial : get_tutorials())
    {
        minutes[tutorial->getPresenter()]+= tutorial->getMinutes();
        times[tutorial->getPresenter()] ++;
    }

    for ( int index=0;index< presenters.size();index++)
        minutes[presenters[index]]/=times[presenters[index]];

    return minutes;
}

map <string,float> Services_Tutorial::average_likes() {
    vector <string> presenters = get_presenters();
    map <string,float> likes ;
    map <string,int> times;
    for (auto tutorial : get_tutorials())
    {
        likes[tutorial->getPresenter()]+= tutorial->getLikes();
        times[tutorial->getPresenter()] ++;
    }

    for ( int index=0;index< presenters.size();index++)
        likes[presenters[index]]/=times[presenters[index]];

    return likes;
}

void Services_Tutorial::undoOp() {
this->serviceUndo->undo();
}

void Services_Tutorial::redoOp() {
this->serviceUndo->redo();
}

void Services_Tutorial::undoWatchlistOp() {
this->serviceUndoWatchlist->undo();
}

void Services_Tutorial::redoWatchlistOp() {
this->serviceUndoWatchlist->redo();
}


