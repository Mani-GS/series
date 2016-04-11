#ifndef TUTORIALDIALOG_H
#define TUTORIALDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class TutorialDialog;
}

class TutorialDialog : public QDialog{
    Q_OBJECT

public:
    explicit TutorialDialog(QWidget *parent = 0);
    ~TutorialDialog();

public slots:

    void moveNext();
    void moveBack();
    void closeDialog();

private:
    Ui::TutorialDialog *ui;
    QString* tutorials;
    int index;
    QLabel* lblText;
    QPushButton* btnNext, *btnBack, *btnClose;
};

#endif // TUTORIALDIALOG_H
