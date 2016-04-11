#include "series.h"
#include "mainwindow.h"
#include "manager.h"
#include <QApplication>
#include <QtWidgets>

#include <QTranslator>

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

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
