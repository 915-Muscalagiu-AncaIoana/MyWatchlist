#include <QApplication>
#include <QPushButton>
#include "GUI.h"
#include "iostream"
#include "Service.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    string path = "";
    TextFileRepository *repository = new TextFileRepository("C:\\Users\\LAPTOP_MIA\\CLionProjects\\a89-915-Muscalagiu-AncaIoana\\tutorials.txt");
    Repository *repository_watchlist = new Repository();
    Validator *validator = new Validator();
    ServiceUndo* serviceUndo = new ServiceUndo(repository);
    ServiceUndoWatchlist* serviceUndoWatchlist = new ServiceUndoWatchlist(repository,repository_watchlist);
    Services_Tutorial *servicesTutorial = new Services_Tutorial(repository, repository_watchlist, serviceUndo,serviceUndoWatchlist, validator);

    GUI* gui = new GUI(nullptr,servicesTutorial);
gui->show();
    return app.exec();
}
