#include "tutorialdialog.h"
#include "ui_tutorialdialog.h"

TutorialDialog::TutorialDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TutorialDialog){
    ui->setupUi(this);

    lblText = findChild<QLabel*>("lblText");
    tutorials = new QString[5];
    tutorials[0] = tr("Hello! Is it your first time here? \nWelcome to Series! Track your favourite TV series, you'll never forget which\nwas the last episode you watched!\n" \
    "Thank you for downloading the app, I hope you like it!");
    tutorials[1] = tr("In order to add a new series, just click Add new TV series button, it allows\nyou to choose name, espisode and season for a new series!\nA dialog will be showed to do this operation, " \
    "just insert name, season and\nepisode (optional) and press Ok. The new series will be displayed immediatly.");
    tutorials[2] = tr("You can update season and episode of every series: just wrtite it into the\ncorrect field and press the Save button.");
    tutorials[3] = tr("In order to make some changes, press the Modify button.\nYou will be able to change name and positions (the display order)\nof every series. You can also delete them.");
    tutorials[4] = tr("I hope you like this app! Thank you for downloading it.");

    index = 0;

    lblText->setText(tutorials[0]);

    btnNext = findChild<QPushButton*>("btnNext");
    btnBack = findChild<QPushButton*>("btnBack");
    btnClose = findChild<QPushButton*>("btnClose");

    connect(btnNext, SIGNAL(released()), this, SLOT(moveNext()));
    connect(btnBack, SIGNAL(released()), this, SLOT(moveBack()));
    connect(btnClose, SIGNAL(released()), this, SLOT(closeDialog()));

    btnBack->setEnabled(false);
}

TutorialDialog::~TutorialDialog(){
    delete ui;
}

void TutorialDialog::moveNext(){
    index++;
    lblText->setText(tutorials[index]);

    btnNext->setEnabled(index < 4);
    btnBack->setEnabled(true);
}

void TutorialDialog::moveBack(){
    index--;
    lblText->setText(tutorials[index]);

    btnBack->setEnabled(index > 0);
    btnNext->setEnabled(true);
}

void TutorialDialog::closeDialog(){
    close();
}
