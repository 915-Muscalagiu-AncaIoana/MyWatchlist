//
// Created by mia on 5/25/2021.
//

#include "UndoRedo.h"

UndoRedo::UndoRedo(Repository *repository, Tutorial tutorial) {
this->repository = repository;
this->tutorial = tutorial;
}

void UndoRedoAdd::executeUndo() {
    repository->remove_from_repo(tutorial.getTitle());
}

void UndoRedoAdd::executeRedo() {
    Tutorial* t = new Tutorial(&tutorial);
    repository->add_to_repo(t);
}

void UndoRedoRemove::executeUndo() {
    Tutorial* t = new Tutorial(&tutorial);
repository->add_to_repo(t);
}

void UndoRedoRemove::executeRedo() {
repository->remove_from_repo(tutorial.getTitle());
}

void UndoRedoUpdate::executeUndo() {
    Tutorial* t = new Tutorial((char*)title.c_str(),(char*)presenter.c_str(),minutes,seconds,likes,(char*)link.c_str());
repository->update_in_repo(t);
}

void UndoRedoUpdate::executeRedo() {
    Tutorial* t = new Tutorial(&tutorial);
repository->update_in_repo(t);
}

UndoRedoAdd::UndoRedoAdd(Repository *repository, Tutorial tutorial) : UndoRedo(repository, tutorial) {

}

UndoRedoRemove::UndoRedoRemove(Repository *repository, Tutorial tutorial) : UndoRedo(repository, tutorial) {

}

UndoRedoUpdate::UndoRedoUpdate(Repository *repository, Tutorial tutorial,Tutorial* old) : UndoRedo(repository, tutorial) {
title = old->getTitle();
presenter = old->getPresenter();
minutes = old->getMinutes();
seconds = old->getSeconds();
likes = old->getLikes();
link = old->getLink();
}


UndoRedoWatchlist::UndoRedoWatchlist(Repository *repository, Repository *watchlist_repository, Tutorial tutorial) {
this->repository=repository;
this->watchlist_repository=watchlist_repository;
this->tutorial = tutorial;
}

UndoRedoAddWatchlist::UndoRedoAddWatchlist(Repository *repository, Repository *watchlist_repository, Tutorial tutorial)
        : UndoRedoWatchlist(repository, watchlist_repository, tutorial) {

}

void UndoRedoAddWatchlist::executeUndo() {
    watchlist_repository->remove_from_repo(tutorial.getTitle());
}

void UndoRedoAddWatchlist::executeRedo() {
    Tutorial* t = new Tutorial(&tutorial);
    watchlist_repository->add_to_repo(t);
}

UndoRedoRemoveWatchlist::UndoRedoRemoveWatchlist(Repository *repository, Repository *watchlist_repository,
                                                 Tutorial tutorial,Tutorial updated) : UndoRedoWatchlist(repository,
                                                                                        watchlist_repository,
                                                                                        tutorial) {
    this->updated = updated;
}

void UndoRedoRemoveWatchlist::executeUndo() {
    Tutorial* t = new Tutorial(&tutorial);
watchlist_repository->add_to_repo(t);
repository->update_in_repo(t);
}

void UndoRedoRemoveWatchlist::executeRedo() {
    watchlist_repository->remove_from_repo(tutorial.getTitle());
    Tutorial* t = new Tutorial(&updated);
    repository->update_in_repo(t);
}
