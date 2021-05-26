//
// Created by mia on 5/5/2021.
//
#include "QShortcut"
#include <sstream>
#include "GUI.h"
#include <QDesktopWidget>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include "stdlib.h"
#include "QCoreApplication"
#include "QChart"
#include <QTreeWidget>
#include "QPushButtonDelegate.h"
#include "QTableView"
using namespace QtCharts;
void GUI::show_user() {

//    QDesktopWidget desktopWidget;
//    QRect screenSize = desktopWidget.availableGeometry(adminW);
//    userW->setFixedSize(screenSize.width() * 0.4, screenSize.height() * 0.4);
    this->userW->show();
    userW->setWindowTitle("User Mode");
    hide();
    this->initialize_user(userW);
}

void GUI::show_admin() {

//    QDesktopWidget desktopWidget;
//    QRect screenSize = desktopWidget.availableGeometry(adminW);
//    adminW->setFixedSize(screenSize.width() * 0.85, screenSize.height() * 0.4);
    adminW->setWindowTitle("Administrator Mode");
    adminW->show();

    hide();


    this->initialize_admin(adminW);
}

void GUI::initialize_user(QWidget *parent) {
    if(parent->layout() != nullptr)
    {
       QLayoutItem * item ;
        while ( ( item = parent->layout()->takeAt( 0 ) ) != nullptr )
        {
            delete item->widget();
            delete item;
        }
        delete parent->layout();
    }


    QVBoxLayout *layout = new QVBoxLayout{parent};
    //playlist widget

  //  this->watchlistWidget = new QListWidget{};

    tableModel = new TutorialTableModel{service};
    tableview = new QTableView{};
    tableview->setModel(tableModel);

    QPushButtonDelegate* qPushButtonDelegate = new QPushButtonDelegate();
    tableview->setItemDelegateForColumn(6,qPushButtonDelegate);
    layout->addWidget(tableview);

    this->filterW = new QWidget;
    this->deleteW = new QWidget;
    //buttons for the playlist
    QWidget *playlistButtonsWidget = new QWidget{};
    QHBoxLayout *watchlistButtonsLayout = new QHBoxLayout{playlistButtonsWidget};
    this->filterButton = new QPushButton{"Filter"};
    this->deleteButton = new QPushButton{"Delete"};
    this->openInAppButton = new QPushButton{"Open in App"};
    this->exitUser = new QPushButton{"Exit"};
   exitUser->setStyleSheet("background-color: rgb(236,190,190)");
    watchlistButtonsLayout->addWidget(filterButton);
    watchlistButtonsLayout->addWidget(deleteButton);
    watchlistButtonsLayout->addWidget(openInAppButton);
    watchlistButtonsLayout->addWidget(exitUser);

    QWidget *presenterWidget = new QWidget{};
    QFormLayout *formLayout = new QFormLayout{presenterWidget};


    QLabel *label2 = new QLabel("Presenter : ");
    QLabel *label2Value = new QLabel("");

    this->presenterInput = new QLineEdit{};
    formLayout->addRow(label2, this->presenterInput);

    //add everything to the right side
    QLabel* label_watch = new QLabel{"Watchlist"};
    label_watch->setStyleSheet("font: 16pt");
    label_watch->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label_watch);
    //layout->addWidget(watchlistWidget);


    //this->watchlistWidget->setDisabled(true);
    layout->addWidget(playlistButtonsWidget);
    layout->addWidget(presenterWidget);
   // populate_watchlist();
    QObject::connect(this->exitUser, SIGNAL(clicked()), this, SLOT(back_user()));
    QObject::connect(this->openInAppButton, SIGNAL(clicked()), this, SLOT(open_in_app()));
    QObject::connect(this->filterButton, SIGNAL(clicked()), this, SLOT(filter_watchlist()));
    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(delete_from_watchlist()));
}

void GUI::filter_watchlist() {
    QWidget* parent = filterW;
    if(parent->layout() != nullptr)
    {
        QLayoutItem * item ;
        while ( ( item = parent->layout()->takeAt( 0 ) ) != nullptr )
        {
            delete item->widget();
            delete item;
        }
        delete parent->layout();
    }
    this->filterW->show();
    delete filterW->layout();
    filterW->setWindowTitle("User Mode");
    QVBoxLayout *layout = new QVBoxLayout{filterW};
    QWidget *tutorialButtonsWidget = new QWidget{};
    QHBoxLayout *watchlistButtonsLayout = new QHBoxLayout{tutorialButtonsWidget};
    this->openButton = new QPushButton{"Open link"};
    this->addWatchlistButton = new QPushButton{"Add"};
    this->nextButton = new QPushButton{"Skip"};
    this->exitWatchlistButton = new QPushButton{"Exit"};
    exitWatchlistButton->setStyleSheet("background-color: rgb(236,190,190)");
    watchlistButtonsLayout->addWidget(openButton);
    watchlistButtonsLayout->addWidget(addWatchlistButton);
    watchlistButtonsLayout->addWidget(nextButton);
    watchlistButtonsLayout->addWidget(exitWatchlistButton);

    QObject::connect(this->openButton, SIGNAL(clicked()), this, SLOT(open_link()));
    QObject::connect(this->addWatchlistButton, SIGNAL(clicked()), this, SLOT(add_to_watchlist()));
    QObject::connect(this->nextButton, SIGNAL(clicked()), this, SLOT(next_tutorial()));
    QObject::connect(this->exitWatchlistButton, SIGNAL(clicked()), this, SLOT(exit_filtering()));

    std::string presenter = presenterInput->text().toStdString();
    filtered = service->filter_by_presenter((char *) presenter.c_str());
    if (filtered.size() == 0) {
        filterW->hide();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("No tutorials with this presenter!"));

        return;
    }

    indexWatchlist = 0;

    QWidget *tutorialsLabelsWidget = new QWidget{};

    QFormLayout* formTLayout = new QFormLayout{tutorialsLabelsWidget};


    QLabel *label1 = new QLabel("Title : ");
    label1->setStyleSheet("font: 10pt");
    label1Value = new QLabel(filtered[indexWatchlist]->getTitle());
    label1Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label1, label1Value);


    QLabel *label2 = new QLabel("Presenter : ");
    label2->setStyleSheet("font: 10pt");
    label2Value = new QLabel(filtered[indexWatchlist]->getPresenter());
    label2Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label2, label2Value);

    string min = to_string(filtered[indexWatchlist]->getMinutes());
    QLabel *label3 = new QLabel("Minutes : ");
    label3->setStyleSheet("font: 10pt");
    label3Value = new QLabel(QString::fromStdString(min));
    label3Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label3, label3Value);

    string sec = to_string(filtered[indexWatchlist]->getMinutes());
    QLabel *label4 = new QLabel("Seconds : ");
    label4->setStyleSheet("font: 10pt");
    label4Value = new QLabel(QString::fromStdString(sec));
    label4Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label4, label4Value);

    string likes = to_string(filtered[indexWatchlist]->getMinutes());
    QLabel *label5 = new QLabel("Likes : ");
    label5->setStyleSheet("font: 10pt");
    label5Value = new QLabel(QString::fromStdString(likes));
    label5Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label5, label5Value);


    QLabel *label6 = new QLabel("Link : ");
    label6->setStyleSheet("font: 10pt");
    label6Value = new QLabel(filtered[indexWatchlist]->getLink());
    label6Value->setStyleSheet("font: 10pt");
    formTLayout->addRow(label6, label6Value);


    layout->addWidget(tutorialsLabelsWidget);
    layout->addWidget(tutorialButtonsWidget);

}

void GUI::exit_filtering() {


    filterW->hide();
    show_user();


    QCoreApplication::processEvents();
}

void GUI::next_tutorial() {
    indexWatchlist++;

    if (indexWatchlist == filtered.size() || filtered[indexWatchlist] == nullptr)
        indexWatchlist = 0;

    label1Value->setText(filtered[indexWatchlist]->getTitle());

    label2Value->setText(filtered[indexWatchlist]->getPresenter());

    string min = to_string(filtered[indexWatchlist]->getMinutes());

    label3Value->setText(QString::fromStdString(min));


    string sec = to_string(filtered[indexWatchlist]->getMinutes());

    label4Value->setText(QString::fromStdString(sec));


    string likes = to_string(filtered[indexWatchlist]->getMinutes());

    label5Value->setText(QString::fromStdString(likes));

    label6Value->setText(filtered[indexWatchlist]->getLink());

}

void GUI::populate_watchlist() {
    watchlistWidget->clear();
    for (auto tutorial : this->service->get_watchlist()) {
        QString listItem = QString::fromStdString(tutorial->toString());
        QListWidgetItem *listItemWidget = new QListWidgetItem(listItem);
        this->watchlistWidget->addItem(listItemWidget);

    }

}

void GUI::open_link() {
    string link = "start ";
    link = link + filtered[indexWatchlist]->getLink();
    link = link + " 2> nul";
    system(link.c_str());
}

void GUI::add_to_watchlist() {
    try {
        this->service->add_tutorial_to_watchlist(filtered[indexWatchlist]->getTitle());
      //  populate_watchlist();

        tableModel = new TutorialTableModel{service};
        tableview = new QTableView{};
        tableview->setModel(tableModel);

        next_tutorial();
    }
    catch (RepositoryException &repositoryException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Tutorial already exists!"));
    }
}

void GUI::open_in_app() {
    system(this->service->get_system_command().c_str());
}

void GUI::delete_from_watchlist() {
    QWidget* parent = deleteW;
    if(parent->layout() != nullptr)
    {
        QLayoutItem * item ;
        while ( ( item = parent->layout()->takeAt( 0 ) ) != nullptr )
        {
            delete item->widget();
            delete item;
        }
        delete parent->layout();
    }

    deleteW->setWindowTitle("User Mode");
    QGridLayout *layout = new QGridLayout{};

    QLabel *label1 = new QLabel("Title : ");
    deleteInput = new QLineEdit{deleteW};
    deleteInput->setEnabled(true);
    QPushButton *deleteWatch = new QPushButton("Delete");
    QPushButton *exitWatch = new QPushButton("Exit");
    exitWatch->setStyleSheet("background-color: rgb(236,190,190)");
    layout->addWidget(label1, 0, 0);
    layout->addWidget(deleteInput, 0, 1);
    layout->addWidget(deleteWatch, 0, 2);
    layout->addWidget(exitWatch, 0, 3);

    QLabel *label2 = new QLabel("Do you want to rate it? : ");
    radio1 = new QRadioButton("Yes");
    radio2 = new QRadioButton("No");
    layout->addWidget(label2, 1, 0);
    layout->addWidget(radio1, 1, 1);
    layout->addWidget(radio2, 1, 2);

    deleteW->setLayout(layout);
    QObject::connect(deleteWatch, SIGNAL(clicked()), this, SLOT(delete_by_title_from_watchlist()));
    QObject::connect(exitWatch, SIGNAL(clicked()), this, SLOT(exit_deleting()));

    deleteW->show();

}

void GUI::exit_deleting() {
deleteW->hide();

}


void GUI::delete_by_title_from_watchlist() {
    std::string title = deleteInput->text().toStdString();

    if (title.size() != 0 && (radio1->isChecked() || radio2->isChecked() ))
        try {
            this->service->delete_tutorial_from_watchlist((char *) title.c_str());
            if (radio1->isChecked())
                this->service->rate_a_tutorial((char *) title.c_str());
            //this->populate_watchlist();

        }
        catch (RepositoryException &repositoryException) {
            QMessageBox messageBox;
            messageBox.critical(0, "Error", QString::fromStdString("There is no tutorial with this title in watchlist!"));
        }
    else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Please enter a non empty title and check if you want to rate it or not!"));
    }
}

void GUI::initialize_admin(QWidget *parent) {
    if(parent->layout() != nullptr)
    {
        QLayoutItem * item ;
        while ( ( item = parent->layout()->takeAt( 0 ) ) != nullptr )
        {
            delete item->widget();
            delete item;
        }
        delete parent->layout();
    }
    delete parent->layout();
    QHBoxLayout *layout = new QHBoxLayout{parent};
    this->tutorialsListWidget = new QListWidget{};
    this->tutorialsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QWidget* tutorialsWidget = new QWidget{};
    QVBoxLayout* vertical = new QVBoxLayout{tutorialsWidget};

    QLabel* data_label = new QLabel{"Tutorials database"};
    data_label->setStyleSheet("font: 16pt");
    data_label->setAlignment(Qt::AlignHCenter);
    vertical->addWidget(data_label);
    vertical->addWidget(tutorialsListWidget);
    QWidget *TutorialDataWidget = new QWidget{};
    QFormLayout *formLayout = new QFormLayout{TutorialDataWidget};


    this->titleInput = new QLineEdit{};
    this->presenterInput = new QLineEdit{};
    this->minutesInput = new QLineEdit{};
    this->secondsInput = new QLineEdit{};
    this->likesInput = new QLineEdit{};
    this->linkInput = new QLineEdit{};


    formLayout->addRow("Title:", titleInput);
    formLayout->addRow("Presenter:", presenterInput);
    formLayout->addRow("Minutes:", minutesInput);
    formLayout->addRow("Seconds:", secondsInput);
    formLayout->addRow("Likes:", likesInput);
    formLayout->addRow("Link:", linkInput);

    //left side buttons
    QWidget *buttonsWidget = new QWidget{};
    QGridLayout *gridLayout = new QGridLayout{buttonsWidget};
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->updateButton = new QPushButton{"Update"};
    this->displayButton = new QPushButton{"Display Chart"};
    this->displayAsTableButton = new QPushButton{"Display Table"};
    this->displayAsTreeButton = new QPushButton{"Display Tree"};
    this->exitAdmin = new QPushButton{"Exit"};
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};

    undoButton->setShortcut(QKeySequence("Ctrl+Z"));
    redoButton->setShortcut(QKeySequence("Ctrl+Y"));
    exitAdmin->setStyleSheet("background-color: rgb(236,190,190)");
    gridLayout->addWidget(addButton, 0, 0);
    gridLayout->addWidget(deleteButton, 0, 1);
    gridLayout->addWidget(updateButton, 0, 2);

    gridLayout->addWidget(displayButton, 1, 0);
    gridLayout->addWidget(displayAsTableButton, 1, 1);
    gridLayout->addWidget(displayAsTreeButton, 2, 1);
    gridLayout->addWidget(exitAdmin, 1, 2);
    gridLayout->addWidget(undoButton, 2, 0);
    gridLayout->addWidget(redoButton, 2, 2);
    layout->addWidget(tutorialsWidget);
    //layout->addWidget(tutorialsListWidget);

    QWidget* tutorialsButtonsWidget = new QWidget{};
    QVBoxLayout* vertical_buttons = new QVBoxLayout{tutorialsButtonsWidget};


    vertical_buttons->addWidget(TutorialDataWidget);
    vertical_buttons->addWidget(buttonsWidget);

    layout->addWidget(tutorialsButtonsWidget);
    populate_tutorials();
    QObject::connect(this->undoButton, SIGNAL(clicked()), this, SLOT(undoAct()));
    QObject::connect(this->redoButton, SIGNAL(clicked()), this, SLOT(redoAct()));
    QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(add_tutorial()));
    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(delete_tutorial()));
    QObject::connect(this->updateButton, SIGNAL(clicked()), this, SLOT(update_tutorial()));
    QObject::connect(this->exitAdmin, SIGNAL(clicked()), this, SLOT(back_admin()));
    QObject::connect(this->displayButton, SIGNAL(clicked()), this, SLOT(display_as_table()));
    QObject::connect(this->displayAsTableButton, SIGNAL(clicked()), this, SLOT(display_table()));
    QObject::connect(this->displayAsTreeButton, SIGNAL(clicked()), this, SLOT(display_tree()));
//
}

void GUI::populate_tutorials() {
    tutorialsListWidget->clear();
    for (auto tutorial : this->service->get_tutorials()) {
        QString listItem = QString::fromStdString(tutorial->toString());
        QListWidgetItem *listItemWidget = new QListWidgetItem(listItem);
        this->tutorialsListWidget->addItem(listItemWidget);
    }
}

void GUI::add_tutorial() {
    std::string title = titleInput->text().toStdString();
    std::string presenter = presenterInput->text().toStdString();

    int minutes;
    try {
        minutes = std::stoi(minutesInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    int seconds;
    try {
        seconds = std::stoi(secondsInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    int likes;
    try {
        likes = std::stoi(likesInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    std::string link = linkInput->text().toStdString();
    std::string tutorialString = title + "," + presenter + "," + to_string(minutes) + "," + to_string(seconds) + "," +
                                 to_string(likes) + "," + link;

    std::stringstream stream{tutorialString};
    try {
        Tutorial *tutorial = new Tutorial();
        stream >> tutorial;
        cout << tutorial->getTitle() << '\n';
        service->add_tutorial(tutorial->getTitle(), tutorial->getPresenter(), tutorial->getMinutes(),
                              tutorial->getSeconds(), tutorial->getLikes(), tutorial->getLink());

        this->populate_tutorials();
    }
    catch (ValidatorException &validatorException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }
    catch (RepositoryException &repositoryException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Tutorial already exists!"));
    }
}

void GUI::delete_tutorial() {
    std::string title = titleInput->text().toStdString();
    try {
        service->remove_tutorial((char *) title.c_str());

        this->populate_tutorials();
    }
    catch (ValidatorException &validatorException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid title!"));
    }
    catch (RepositoryException &repositoryException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Tutorial doesn't exist!"));
    }
}

void GUI::update_tutorial() {
    std::string title = titleInput->text().toStdString();
    std::string presenter = presenterInput->text().toStdString();

    int minutes;
    try {
        minutes = std::stoi(minutesInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    int seconds;
    try {
        seconds = std::stoi(secondsInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    int likes;
    try {
        likes = std::stoi(likesInput->text().toStdString());
    }
    catch (std::invalid_argument &invalidArgument) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
        return;
    }

    std::string link = linkInput->text().toStdString();
    std::string tutorialString = title + "," + presenter + "," + to_string(minutes) + "," + to_string(seconds) + "," +
                                 to_string(likes) + "," + link;

    std::stringstream stream{tutorialString};
    try {
        Tutorial *tutorial = new Tutorial();
        stream >> tutorial;
        cout << tutorial->getTitle() << '\n';
        service->update_tutorial(tutorial->getTitle(), tutorial->getPresenter(), tutorial->getMinutes(),
                                 tutorial->getSeconds(), tutorial->getLikes(), tutorial->getLink());

        this->populate_tutorials();
    }
    catch (ValidatorException &validatorException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }
    catch (RepositoryException &repositoryException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Tutorial doesn't exist!"));
    }

}
void GUI::display_as_table() {
    displayW = new QMainWindow();
    displayW->resize(800,500);

    QBarSet *set0 = new QBarSet("Minutes");
    QBarSet *set1 = new QBarSet("Likes");

    map <string,float> minutes = this->service->average_minutes();
    map <string,float> likes = this->service->average_likes();
    for( auto presenter : minutes)
        *set0 << presenter.second;
    for( auto presenter : likes)
        *set1 << presenter.second;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);


    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Tutorials Barchart");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;

    for ( auto category : minutes)
        categories << QString::fromStdString(category.first);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,250);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    displayW->setCentralWidget(chartView);




    displayW->show();


}

void GUI::back_admin() {
    this->adminW->hide();
    this->show();
//    delete titleInput;
//    delete presenterInput;
//    delete minutesInput;
//    delete secondsInput;
//    delete likesInput;
//    delete linkInput;
//    delete addButton;
//    delete deleteButton;
//    delete updateButton;
//    delete displayButton;
//    delete exitAdmin;
//    delete tutorialsListWidget;


}

void GUI::back_user() {
    this->userW->hide();
    this->show();

}

void GUI::initialize() {
    QGridLayout* layout = new QGridLayout{ this };
    this->modeAButton = new QPushButton{ "Administrator" };
    this->modeBButton = new QPushButton{ "User" };
    this->exitButton = new QPushButton{ "Exit" };
    exitButton->setStyleSheet("background-color: rgb(236,190,190)");
    this->chooseButton = new QPushButton{ "Choose" };


    QLabel *label2 = new QLabel("Repository type : ");
    repo1 = new QRadioButton("CSV");
    repo2 = new QRadioButton("HTML");
    layout->addWidget(label2, 1, 0);
    layout->addWidget(repo1, 1, 1);
    layout->addWidget(repo2, 1, 2);
    layout->addWidget(chooseButton,1,3);

    layout->addWidget(modeAButton,0,0);
    layout->addWidget(modeBButton,0,1);
    layout->addWidget(exitButton,0,2);

    modeAButton->setDisabled(true);
    modeBButton->setDisabled(true);


    QObject::connect(this->modeAButton, SIGNAL(clicked()), this, SLOT(show_admin()));
    QObject::connect(this->modeBButton, SIGNAL(clicked()), this, SLOT(show_user()));
    QObject::connect(this->exitButton, SIGNAL(clicked()), this, SLOT(exit_app()));
    QObject::connect(this->chooseButton, SIGNAL(clicked()), this, SLOT(choose_repo()));
    this-> adminW = new QWidget;
    this-> userW = new QWidget;

}

void GUI::choose_repo() {
if (repo1->isChecked() || repo2->isChecked())
{

    if (repo1->isChecked())
    {string path = "C:\\Users\\LAPTOP_MIA\\CLionProjects\\a89-915-Muscalagiu-AncaIoana\\watchlist.csv";
        CSVRepository *csvRepository = new CSVRepository(path);
        this->service->set_repo(csvRepository);
    }
    else {
        string path = "C:\\Users\\LAPTOP_MIA\\CLionProjects\\a89-915-Muscalagiu-AncaIoana\\watchlist.html";
        HTMLRepository *htmlRepository = new HTMLRepository(path);
        this->service->set_repo(htmlRepository);
    }

    modeAButton->setDisabled(false);
    modeBButton->setDisabled(false);
    chooseButton->setDisabled(true);
    repo1->setEnabled(false);
    repo2->setEnabled(false);
}
else {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", QString::fromStdString("Please choose a type of repo!"));
}
}

void GUI::display_table() {
displayTableW = new QMainWindow;
    auto tableWidget = new QTableWidget(12, 3, this);
    tableWidget->setColumnCount(6);
    tableWidget->setRowCount(this->service->get_tutorials().size());
    int row=0;
    int column = 0;
    displayTableW->setCentralWidget(tableWidget);

    tableWidget->setHorizontalHeaderLabels(QStringList{ "Title", "Presenter","Minutes","Seconds","Likes","Link" });
    for (auto it : service->get_tutorials())
    {column=0;
        QTableWidgetItem *newItem = new QTableWidgetItem(it->getTitle());
        tableWidget->setItem(row, column, newItem);

        column++;
        newItem = new QTableWidgetItem(it->getPresenter());
        tableWidget->setItem(row, column, newItem);

        column++;
        string min = to_string(it->getMinutes());
        newItem = new QTableWidgetItem(QString::fromStdString(min));
        tableWidget->setItem(row, column, newItem);

        column++;
        string sec = to_string(it->getSeconds());
        newItem = new QTableWidgetItem(QString::fromStdString(sec));
        tableWidget->setItem(row, column, newItem);

        column++;
        string lik = to_string(it->getLikes());
        newItem = new QTableWidgetItem(QString::fromStdString(lik));
        tableWidget->setItem(row, column, newItem);

        column++;
        newItem = new QTableWidgetItem(it->getLink());
        tableWidget->setItem(row, column, newItem);

        row++;
    }
    displayTableW->show();
}

void GUI::display_tree() {
displayTreeW = new QMainWindow;

QTreeWidget* treeWidget = new QTreeWidget;
displayTreeW->setCentralWidget(treeWidget);
treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
for ( auto it : service->get_tutorials())
{
    QTreeWidgetItem *newItem = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString(it->getTitle())));
    items.append(reinterpret_cast<QTreeWidgetItem *const>(newItem));
}
treeWidget->insertTopLevelItems(0,items);

displayTreeW->show();
}

void GUI::undoAct() {
    try {
        this->service->undoOp();
        this->populate_tutorials();
    }
    catch (UndoException &undoException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("No more undos!"));
    }
}

void GUI::redoAct() {
    try {
        this->service->redoOp();
        this->populate_tutorials();
    }
    catch (UndoException &undoException) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("No more redos!"));
    }
}












