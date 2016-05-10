#include "series.h"
#include "mainwindow.h"
#include "manager.h"
#include <QApplication>
#include <QtWidgets>

#include <QTranslator>

#include "fervor/fvupdater.h"

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QApplication::setApplicationName("Series");
    QApplication::setApplicationVersion("1.1");
    QApplication::setOrganizationName("Mani");
    QApplication::setOrganizationDomain("Mani.it");

    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/Mani-GS/series/feature_updateChecker/Appcast.xml");
    FvUpdater::sharedUpdater()->CheckForUpdates();

    QTranslator translator;
    QString language = QLocale::system().name();

    if(language == "it_IT"){
        translator.load(":/translations/series_it");
        a.installTranslator(&translator);
    }

    Manager* manag = new Manager();
    manag->main();

	return a.exec();
}
