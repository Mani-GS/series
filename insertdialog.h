#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog{
    Q_OBJECT

public:
    explicit InsertDialog(QWidget *parent = 0);
    ~InsertDialog();
    void reset();
    void enableOk();

public slots:

    void okPressed();
    void cancelPressed();
    void txtNameChanged(QString text);
    void txtSeasonChanged(QString text);
    void txtEpisodeChanged(QString text);

signals:

    void newSeries(QString name, QString season, QString episode);

private:
    Ui::InsertDialog *ui;
    QDialogButtonBox* btbButtons;
    QLineEdit *txtName, *txtSeason, *txtEpisode;
    bool name, season, episode;
};

#endif // INSERTDIALOG_H
