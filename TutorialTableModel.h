//
// Created by mia on 5/22/2021.
//

#ifndef A10_915_MUSCALAGIU_ANCAIOANA_1_TUTORIALTABLEMODEL_H
#define A10_915_MUSCALAGIU_ANCAIOANA_1_TUTORIALTABLEMODEL_H

#endif //A10_915_MUSCALAGIU_ANCAIOANA_1_TUTORIALTABLEMODEL_H
#include "QWidget"
#include "QAbstractTableModel"
#pragma once
#include "Service.h"
#include "QHeaderView"
#include <iostream>
#include "QPushButton"
class TutorialTableModel : public QAbstractTableModel{
Q_OBJECT
private:
    Services_Tutorial* servicesTutorial;

public:
    TutorialTableModel(Services_Tutorial* servicesTutorial) {
this->servicesTutorial = servicesTutorial;


    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return servicesTutorial->get_watchlist().size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex())const{
        return 7;
    };



    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
        std::vector<Tutorial*> data = servicesTutorial->get_watchlist();

        int row = index.row(), column = index.column();
        if (role == Qt::DisplayRole){
            if (data.empty())
                return  QVariant();
            if (column == 0) {
                return QString::fromStdString(data[row]->getTitle());
            }
            if (column == 1){
                return QString::fromStdString(data[row]->getPresenter());
            }
            if (column == 2){
                return QString::number(data[row]->getMinutes());
            }
            if (column == 3){
                return QString::number(data[row]->getSeconds());
            }
            if (column == 4){
                return QString::number(data[row]->getLikes());
            }
            if (column == 5){
                return QString::fromStdString(data[row]->getLink());
            }
            if (column == 6)
            {
                return QString::fromStdString(data[row]->getLink());
            }

        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Title");
                case 1:
                    return QString("Presenter");
                case 2:
                    return QString("Minutes");
                case 3:
                    return QString("Seconds");
                case 4:
                    return QString("Likes");
                case 5:
                    return QString("Link");
                case 6:
                    return  QString("Play");

            }
        }
        return QVariant();
    }
};