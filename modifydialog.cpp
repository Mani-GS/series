#include "modifydialog.h"
#include "ui_modifydialog.h"

using namespace std;

ModifyDialog::ModifyDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ModifyDialog){
    ui->setupUi(this);
    QPixmap tickPNG(":/icons/imgs/tick.png");
    QPixmap delPNG(":/icons/imgs/delete.png");
    QPixmap applyPNG(":/icons/imgs/apply.png");

    QIcon tickICO(tickPNG);
    QIcon delICO(delPNG);
    QIcon applyICO(applyPNG);

    lstSeries = findChild<QListWidget*>("lstSeries");
    txtNewName = findChild<QLineEdit*>("txtNewName");
    btbButtons = findChild<QDialogButtonBox*>("btbButtons");
    btnDelete = findChild<QPushButton*>("btnDelete");
    btnUp = findChild<QPushButton*>("btnUp");
    btnDown = findChild<QPushButton*>("btnDown");
    lblActiveItem = findChild<QLabel*>("lblActiveItem");

    btbButtons->button(QDialogButtonBox::Apply)->setText(tr("Apply"));
    btbButtons->button(QDialogButtonBox::Apply)->setIcon(applyICO);
    btbButtons->button(QDialogButtonBox::Ok)->setIcon(tickICO);
    btbButtons->button(QDialogButtonBox::Cancel)->setText(tr("&Cancel"));
    btbButtons->button(QDialogButtonBox::Cancel)->setIcon(delICO);

    connect(lstSeries, SIGNAL(clicked(QModelIndex)), this, SLOT(refresh(QModelIndex)));
    connect(btbButtons, SIGNAL(accepted()), this, SLOT(applyChanges()));
    connect(btbButtons->button(QDialogButtonBox::Apply), SIGNAL(released()), this, SLOT(applyChanges()));
    connect(btnDelete, SIGNAL(released()), this, SLOT(deleteSeries()));
    connect(btnUp, SIGNAL(released()), this, SLOT(moveUp()));
    connect(btnDown, SIGNAL(released()), this, SLOT(moveDown()));
    connect(txtNewName, SIGNAL(textEdited(QString)), this, SLOT(newName(QString)));

    QShortcut* shortcutKeyUp = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_Up), this);
    QShortcut* shortcutKeyDown = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_Down), this);

    QShortcut* shKeyUp = new QShortcut(QKeySequence(Qt::Key_Up), this);
    QShortcut* shKeyDown = new QShortcut(QKeySequence(Qt::Key_Down), this);

    connect(shortcutKeyUp, SIGNAL(activated()), this, SLOT(moveUp()));
    connect(shortcutKeyDown, SIGNAL(activated()), this, SLOT(moveDown()));
    connect(shKeyUp, SIGNAL(activated()), this, SLOT(selUp()));
    connect(shKeyDown, SIGNAL(activated()), this, SLOT(selDown()));
}

ModifyDialog::~ModifyDialog(){
    delete ui;
    delete lstSeries;
    delete txtNewName;
    delete btbButtons;
    delete btnUp;
    delete btnDown;
    delete btnDelete;
    delete lblActiveItem;
}

void ModifyDialog::setSeries(vector<Series*> series_array){
    this->series_array = series_array;
}

void ModifyDialog::createList(){
    reset();

    QListWidgetItem* it;
    Values val;

    for(unsigned int i=0; i<series_array.size(); i++){
        QString name = dirtyStr(series_array[i]->getName());
        it = new QListWidgetItem(name);
        lstSeries->addItem(it);

        val.name = "";
        val.position = i;
        seriesValues.push_back(val);
    }

    checkPosition();
}

void ModifyDialog::reset(){
    lstSeries->clear();
    txtNewName->setText("");
    lblActiveItem->setText(tr("You haven't selected an item yet."));
    i = QModelIndex();

    while(seriesValues.size() > 0){
        seriesValues.pop_back();
    }
}

void ModifyDialog::checkPosition(){
    if(i.row() == 0){
        btnUp->setEnabled(false);
        if(i.row() < (series_array.size() - 1)){
            btnDown->setEnabled(true);
        }
    }
    if(i.row() > 0 && i.row() < (series_array.size() - 1)){
        btnUp->setEnabled(true);
        btnDown->setEnabled(true);
    }
    if(i.row() == (series_array.size() - 1)){
        btnDown->setEnabled(false);
        if(i.row() > 0){
            btnUp->setEnabled(true);
        }
    }
    if(i.row() == -1){
        btnUp->setEnabled(false);
        btnDown->setEnabled(false);
    }
}


//public slots

void ModifyDialog::refresh(QModelIndex i){
    this->i = i;

    QString newItem = tr("You've currently selected: \n");
    newItem.append(dirtyStr(series_array[i.row()]->getName()));
    lblActiveItem->setText(newItem);

    txtNewName->setText(seriesValues[i.row()].name);

    checkPosition();
}

void ModifyDialog::applyChanges(){
    bool repositioning = false;

    for(unsigned int i=0; i<series_array.size(); i++){
        if(seriesValues[i].name != ""){
            emit changeName(series_array[i]->getPosition(), seriesValues[i].name);
            lstSeries->takeItem(i);
            lstSeries->insertItem(i, seriesValues[i].name);

            lstSeries->setCurrentRow(i);
            const QAbstractItemModel* lstModel = this->i.model();
            this->i = lstModel->index(i, 0);

            refresh(this->i);

            seriesValues[i].name = "";
            txtNewName->setText("");
        }
    }

    for(unsigned int i=0; i<series_array.size(); i++){
        if(seriesValues[i].position != series_array[i]->getPosition()){
            emit changePosition(series_array[i]->getID(), series_array[i]->getPosition(), seriesValues[i].position);
            repositioning = true;
        }
    }

    if(repositioning){
        emit endRepositioning();
    }
}

void ModifyDialog::newName(QString text){
    if(i.row() == -1){
        QMessageBox::warning(NULL, tr("Warning"), tr("Please select a series."));
        txtNewName->setText("");
        return;
    }

    seriesValues[i.row()].name = text;
}

void ModifyDialog::moveUp(){
    if(i.row() == -1){
        lstSeries->setCurrentRow(0);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
    else if(i.row() > 0){
        QListWidgetItem *it;

        int pos = i.row();

        seriesValues[pos].position--;
        seriesValues[pos - 1].position++;

        Series* s = series_array[pos - 1];
        series_array[pos - 1] = series_array[pos];
        series_array[pos] = s;

        Values v = seriesValues[pos -1];
        seriesValues[pos - 1] = seriesValues[pos];
        seriesValues[pos] = v;

        lstSeries->clear();

        for(unsigned int i=0; i<series_array.size(); i++){
            QString name = series_array[i]->getName();
            it = new QListWidgetItem(name);
            lstSeries->addItem(it);
        }

        lstSeries->setCurrentRow(pos - 1);
        const QAbstractItemModel* lstModel = i.model();
        i = lstModel->index(pos - 1, 0);

        checkPosition();
    }
}

void ModifyDialog::moveDown(){
    if(i.row() == -1){
        int n = series_array.size() - 1;

        lstSeries->setCurrentRow(n);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
    else if(i.row() < (series_array.size() - 1)){
        QListWidgetItem *it;

        int pos = i.row();

        seriesValues[pos].position++;
        seriesValues[pos + 1].position--;

        Series* s = series_array[pos];
        series_array[pos] = series_array[pos + 1];
        series_array[pos + 1] = s;

        Values v = seriesValues[pos];
        seriesValues[pos] = seriesValues[pos + 1];
        seriesValues[pos + 1] = v;

        lstSeries->clear();

        for(unsigned int i=0; i<series_array.size(); i++){
            QString name = series_array[i]->getName();
            it = new QListWidgetItem(name);
            lstSeries->addItem(it);
        }

        lstSeries->setCurrentRow(pos + 1);
        const QAbstractItemModel* lstModel = i.model();
        i = lstModel->index(pos + 1, 0);

        checkPosition();
    }
}

void ModifyDialog::selUp(){
    if(i.row() == -1){
        lstSeries->setCurrentRow(0);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
    else if(i.row() > 0){
        int n = i.row() - 1;

        lstSeries->setCurrentRow(n);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
}

void ModifyDialog::selDown(){
    if(i.row() == -1){
        int n = series_array.size() - 1;

        lstSeries->setCurrentRow(n);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
    else if(i.row() < series_array.size() - 1){
        int n = i.row() + 1;

        lstSeries->setCurrentRow(n);
        const QAbstractItemModel* lstModel = i.model();
        i = lstSeries->currentIndex();

        checkPosition();
        refresh(i);
    }
}

void ModifyDialog::deleteSeries(){
    if(i.row() == -1){
        QMessageBox::warning(NULL, tr("Warning"), tr("Please select a series."));
        return;
    }

    QString msg = series_array[i.row()]->getName();
    msg.append(tr(" will be deleted."));

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Warning"));
    msgBox.setText(msg);
    msgBox.setInformativeText(tr("Are you sure?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText(tr("&Yes"));
    msgBox.button(QMessageBox::No)->setText(tr("&No"));
    msgBox.setIconPixmap(QPixmap (":/icons/imgs/stop.png"));

    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes){
        int pos = i.row();

        lstSeries->takeItem(i.row());
        emit del(series_array[i.row()]->getPosition());

        vector<Series*> sTemp;
        vector<Values> vTemp;

        while(series_array.size() > (pos + 1)){
            sTemp.push_back(series_array.back());
            series_array.pop_back();

            vTemp.push_back(seriesValues.back());
            seriesValues.pop_back();
        }

        series_array.pop_back();
        seriesValues.pop_back();

        while(sTemp.size() > 0){
            series_array.push_back(sTemp.back());
            sTemp.pop_back();

            seriesValues.push_back(vTemp.back());
            vTemp.pop_back();
        }

        for(unsigned int ind=pos; ind < series_array.size(); ind++){
            seriesValues[ind].position--;
        }

        if(series_array.size() > 0){
            if(pos > 0){
                pos--;
            }

            lstSeries->setCurrentRow(pos);
            const QAbstractItemModel* lstModel = i.model();
            i = lstSeries->currentIndex();
            refresh(i);

            checkPosition();
        }else{
            txtNewName->setText("");
            lblActiveItem->setText(tr("You haven't selected an item yet."));
            i = QModelIndex();
        }
    }
}

QString ModifyDialog::dirtyStr(QString str){
    str = str.replace("&&", "&");

    return str;
}
