#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "series.h"
#include "insertdialog.h"
#include "modifydialog.h"
#include "tutorialdialog.h"
#include <QWidget>
#include <sqlite3.h>
#include <string>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <pwd.h>

using namespace std;

class Manager : public QObject {
    Q_OBJECT

public:
    Manager(QObject *parent = 0);
    ~Manager();
    bool checkMainFolder();
    bool checkDb();
    void firstAccess();
    void openDb(bool create);
    void loadSeries();
    void main();

public slots:

    void addSeries(QString name, QString season, QString episode);
    void saveSeries(int position);
    void saveAll();
    void insertNewSeries();
    void modifySeries();
    void deleteSeries(int pos);
    void changeSeriesName(int pos, QString name);
    void changeSeriesPosition(int ID, int oldPos, int newPos);
    void orderSeries();
    void changes();

private:

    void bubbleSort();
    void checkIssues();
    QString cleanStr(QString str);
    QString cleanStrGUI(QString str);

    MainWindow* w;
    InsertDialog* insSeries;
    ModifyDialog* modSeries;
    QPushButton* btnAddSeries, *btnSaveAll, *btnModify;
    sqlite3* db;
    string mainFolder;
    vector<Series*> series_array;
};

#endif // MANAGER_H
