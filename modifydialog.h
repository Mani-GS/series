#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include "series.h"
#include <QDialog>
#include <vector>
#include <string>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QDialog{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = 0);
    ~ModifyDialog();

    void setSeries(std::vector<Series*> series_array);
    void createList();
    void reset();
    void checkPosition();

public slots:

    void refresh(QModelIndex i);
    void applyChanges();
    void deleteSeries();
    void newName(QString text);
    void moveUp();
    void moveDown();
    void selUp();
    void selDown();

signals:

    void del(int pos);
    void changeName(int pos, QString name);
    void changePosition(int ID, int oldPos, int newPos);
    void endRepositioning();

private:
    typedef struct _values{
        QString name;
        int position;
    }Values;

    QString dirtyStr(QString str);

    Ui::ModifyDialog *ui;
    QListWidget* lstSeries;
    QModelIndex i;
    QLineEdit* txtNewName;
    QDialogButtonBox* btbButtons;
    QPushButton* btnDelete, *btnUp, *btnDown;
    QLabel* lblActiveItem;
    std::vector<Series*> series_array;
    std::vector<Values> seriesValues;
};

#endif // MODIFYDIALOG_H
