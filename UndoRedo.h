//
// Created by mia on 5/25/2021.
//

#ifndef A10_915_MUSCALAGIU_ANCAIOANA_1_UNDOREDO_H
#define A10_915_MUSCALAGIU_ANCAIOANA_1_UNDOREDO_H

#endif //A10_915_MUSCALAGIU_ANCAIOANA_1_UNDOREDO_H
#include "Repository.h"
#pragma once
class UndoRedo{
protected:
    Repository* repository;
    Tutorial tutorial;
public:
    UndoRedo(Repository* repository, Tutorial tutorial);
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class UndoRedoAdd : public UndoRedo{
public:
    UndoRedoAdd(Repository* repository, Tutorial tutorial);
    void executeUndo() override;
    void executeRedo() override;
};

class UndoRedoRemove : public UndoRedo{
public:
    UndoRedoRemove(Repository* repository, Tutorial tutorial);
    void executeUndo() override;
    void executeRedo() override;
};
class UndoRedoUpdate : public UndoRedo{

private:
    string title;
    string presenter;
    int minutes;
    int seconds;
    int likes;
    string link;
public:
    UndoRedoUpdate(Repository* repository, Tutorial tutorial, Tutorial* old);
    void executeUndo() override;
    void executeRedo() override;
};
class UndoException : public std::exception{
    string message;
public:
    UndoException(std::string message) :message(message) {};
    string getMessage() { return this->message; };
};

class UndoRedoWatchlist{
protected:
    Repository* repository;
    Repository* watchlist_repository;
    Tutorial tutorial;
public:
    UndoRedoWatchlist(Repository* repository, Repository* watchlist_repository, Tutorial tutorial);
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class UndoRedoAddWatchlist : public UndoRedoWatchlist{
public:
    UndoRedoAddWatchlist(Repository* repository, Repository* watchlist_repository, Tutorial tutorial);
    void executeUndo() override;
    void executeRedo() override;
};

class UndoRedoRemoveWatchlist : public UndoRedoWatchlist{
private:
    Tutorial updated;
public:
    UndoRedoRemoveWatchlist(Repository* repository,Repository* watchlist_repository, Tutorial tutorial, Tutorial updated);
    void executeUndo() override;
    void executeRedo() override;
};
