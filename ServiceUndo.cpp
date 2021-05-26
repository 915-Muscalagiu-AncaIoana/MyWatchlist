//
// Created by mia on 5/25/2021.
//

#include "ServiceUndo.h"
#pragma once
ServiceUndo::ServiceUndo(Repository* repository)
{
    this->repository = repository;
    index = -1;
}

void ServiceUndo::undo() {
    if (index == -1)
        throw UndoException("No more redos\n");
    history[index]->executeUndo();
    index--;
}

void ServiceUndo::redo() {
    if (index == history.size()-1)
        throw UndoException("No more undos\n");
    history[index+1]->executeRedo();
    index++;
}

void ServiceUndo::record(UndoRedo* op) {

   if (index != history.size()-1 )
    history.erase(history.begin()+index+1,history.end());
    history.push_back(op);
    index++;
}