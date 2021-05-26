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
