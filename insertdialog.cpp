#include "insertdialog.h"
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(QWidget *parent) : QDialog(parent), ui(new Ui::InsertDialog){
    ui->setupUi(this);

    btbButtons = findChild<QDialogButtonBox*>("btbButtons");

    connect(btbButtons, SIGNAL(accepted()), this, SLOT(okPressed()));
    connect(btbButtons, SIGNAL(rejected()), this, SLOT(cancelPressed()));

    txtName = findChild<QLineEdit*>("txtName");
    txtSeason = findChild<QLineEdit*>("txtSeason");
    txtEpisode = findChild<QLineEdit*>("txtEpisode");

    btbButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    btbButtons->button(QDialogButtonBox::Cancel)->setText(tr("&Cancel"));

    connect(txtName, SIGNAL(textChanged(QString)), this, SLOT(txtNameChanged(QString)));
    connect(txtSeason, SIGNAL(textChanged(QString)), this, SLOT(txtSeasonChanged(QString)));
    connect(txtEpisode, SIGNAL(textChanged(QString)), this, SLOT(txtEpisodeChanged(QString)));

    name = false;
    season = true;
    episode = true;

    QPixmap tickPNG(":/icons/imgs/tick.png");
    QPixmap delPNG(":/icons/imgs/delete.png");
    QIcon tickICO(tickPNG);
    QIcon delICO(delPNG);

    btbButtons->button(QDialogButtonBox::Ok)->setIcon(tickICO);
    btbButtons->button(QDialogButtonBox::Cancel)->setIcon(delICO);
}

InsertDialog::~InsertDialog(){
    delete ui;
    delete btbButtons;
    delete txtName;
    delete txtSeason;
    delete txtEpisode;
}

void InsertDialog::okPressed(){
    emit newSeries(txtName->text(), txtSeason->text(), txtEpisode->text());
    reset();
}

void InsertDialog::cancelPressed(){
    reset();
}

void InsertDialog::reset(){
    txtName->setText("");
    txtSeason->setText("1");
    txtEpisode->setText("0");
    name = false;
    season = true;
    episode = true;
}

void InsertDialog::enableOk(){
    btbButtons->button(QDialogButtonBox::Ok)->setEnabled(name && season && episode);
}

void InsertDialog::txtNameChanged(QString text){
    name = text != "";
    enableOk();
}

void InsertDialog::txtSeasonChanged(QString text){
    season = text != "";
    enableOk();
}

void InsertDialog::txtEpisodeChanged(QString text){
    episode = text != "";
    enableOk();
}
