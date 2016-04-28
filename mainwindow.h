#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
//#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent* event);
    void setModify(bool modify);

    bool getModify();

signals:

    void saveChanges();

private:

    bool modify;
};

#endif // MAINWINDOW_H
