#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    modify = false;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event){
    if(modify){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Warning"));
        msgBox.setText(tr("Some changes were not saved."));
        msgBox.setInformativeText(tr("Are you sure you want to quit?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.button(QMessageBox::Save)->setText(tr("&Save"));
        msgBox.button(QMessageBox::Discard)->setText(tr("&Don't save"));
        msgBox.button(QMessageBox::Cancel)->setText(tr("&Cancel"));
        msgBox.setIconPixmap(QPixmap (":/icons/imgs/stop.png"));

        int ret = msgBox.exec();

        if(ret == QMessageBox::Discard){
            event->accept();
        }else if(ret == QMessageBox::Save){
            emit saveChanges();
            event->accept();
        }else{
            event->ignore();
        }
    }
}

void MainWindow::setModify(bool modify){
    this->modify = modify;
}

bool MainWindow::getModify(){
    return modify;
}
