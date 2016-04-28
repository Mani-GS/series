#ifndef SERIES_H
#define SERIES_H
#include "mainwindow.h"
#include <QtWidgets>
#include <QApplication>
#include <string>

class Series : public QObject{
    Q_OBJECT

public:
    Series(MainWindow *window, int ID, QString name, QString season, QString episode, bool finish, int position);
    ~Series();
    void init();
    void createSeries();
    void removeFromGUI();
    void reDraw();

    void setWindow(MainWindow* window);
    void setID(int ID);
    void setPosition(int position);
    void setName(QString name);
    void setSeason(QString season);
    void setEpisode(QString episode);
    void setFinish(bool finish);
    void setChanges(bool changes);

    int getID();
    QString getName();
    QString getSeason();
    QString getEpisode();
    bool getFinish();
    int getPosition();
    bool getChanges();

public slots:

    void episodeChanged(QString text);
    void seasonChanged(QString text);
    void finishChanged(int state);
    void saveSeries();

signals:

    void save(int position);
    void somethingChanged ();

private:
    QString name, season, episode;
    int position, ID;
    bool finish, sChanges, eChanges, fChanges;

    MainWindow *window;
    QGridLayout *scaLayout;
    QHBoxLayout *hLay;
    QGroupBox *grpSeries;
    QLabel *lblSeason, *lblEpisode;
    QLineEdit *txtSeason, *txtEpisode;
    QCheckBox *chkFinish;
    QPushButton *btnSave;
};

#endif // SERIES_H
