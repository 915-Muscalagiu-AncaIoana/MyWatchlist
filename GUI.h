//
// Created by mia on 5/5/2021.
//

#ifndef GUI3_GUI_H
#define GUI3_GUI_H

#endif //GUI3_GUI_H
#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include "Service.h"
#include <QTableWidget>
#include <QBarSet>
#include <QBarSeries>
#include "TutorialTableModel.h"
#include "UndoRedo.h"
#pragma once
class GUI : public QWidget {
Q_OBJECT
public:
    GUI( QWidget *parent, Services_Tutorial* servicesTutorial ) : QWidget(parent), service{servicesTutorial}{
this->initialize();
    }

private:
    QWidget* userW;
    QWidget* adminW;
    QWidget* filterW;
    QWidget *deleteW;
    QMainWindow *displayW;
    QMainWindow *displayTableW;
    QMainWindow *displayTreeW;


    QPushButton* buttons[50];
    Services_Tutorial* service;

    QListWidget* tutorialsListWidget;
    QListWidget* watchlistWidget;

    QLineEdit * titleInput ;
    QLineEdit * presenterInput ;
    QLineEdit * minutesInput ;
    QLineEdit * secondsInput ;
    QLineEdit * likesInput ;
    QLineEdit * linkInput;
    QLineEdit *deleteInput;

    QPushButton* modeAButton;
    QPushButton* modeBButton;
    QPushButton* chooseButton;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* filterButton;
    QPushButton* openInAppButton;
    QPushButton* openButton;
    QPushButton* nextButton;
    QPushButton* exitWatchlistButton;
    QPushButton* addWatchlistButton;

    QPushButton* displayAsTableButton;
    QPushButton* displayAsTreeButton;
    QPushButton* displayButton;
    QPushButton* exitButton;
    QPushButton* exitUser;
    QPushButton* exitAdmin;

    QRadioButton* radio1 ;
    QRadioButton* radio2 ;
    QRadioButton* repo1 ;
    QRadioButton* repo2 ;

    QLabel* label1Value ;
    QLabel* label2Value ;
    QLabel* label3Value ;
    QLabel* label4Value ;
    QLabel* label5Value ;
    QLabel* label6Value ;

    TutorialTableModel* tableModel;
    QTableView* tableview;
   // QFormLayout* formTLayout;

    QTableWidget* tableWidget;

    int indexWatchlist;
    vector <Tutorial*> filtered;
    void initialize() ;

    void initialize_user(QWidget* parent);
    void initialize_admin(QWidget* parent);
    void populate_tutorials();
    void populate_watchlist();




private slots:
    void show_user();

    void show_admin();

    void exit_app(){
        std::exit(0);
    }

    void add_tutorial();
    void delete_tutorial();
    void update_tutorial();
    void back_admin();
    void delete_from_watchlist();
    void back_user();
    void open_in_app();
    void next_tutorial();
    void open_link();
    void add_to_watchlist();
    void exit_filtering();
    void exit_deleting();
    void filter_watchlist();
    void delete_by_title_from_watchlist();
    void display_as_table();
    void choose_repo();
    void display_table();
    void display_tree();
    void undoAct();
    void redoAct();


};