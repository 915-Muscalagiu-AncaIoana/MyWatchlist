//
// Created by mia on 5/25/2021.
//

#ifndef A10_915_MUSCALAGIU_ANCAIOANA_1_SERVICEUNDO_H
#define A10_915_MUSCALAGIU_ANCAIOANA_1_SERVICEUNDO_H

#endif //A10_915_MUSCALAGIU_ANCAIOANA_1_SERVICEUNDO_H
#include "UndoRedo.h"
class ServiceUndo{
private:
    vector <UndoRedo*> history;
    Repository* repository;
    int index;
public:
    ServiceUndo(Repository* repository);
    void record(UndoRedo* op);
    void undo();
    void redo();
};
class ServiceUndoWatchlist{
private:
    vector <UndoRedoWatchlist*> history;
    Repository* repository;
    Repository* watchlist_repository;
    int index;
public:
    ServiceUndoWatchlist(Repository* repository,Repository* watchlist);
    void record(UndoRedoWatchlist* op);
    void undo();
    void redo();
};