#include "series.h"

Series::Series(MainWindow *window, int ID, QString name, QString season, QString episode, bool finish, int position){
    this->window = window;
    this->ID = ID;
    this->name = name;
    this->season = season;
    this->episode = episode;
    this->finish = finish;
    this->position = position;
    sChanges = false;
    eChanges = false;
    fChanges = false;

    if(window != NULL)
        scaLayout = window->findChild<QGridLayout*>("scaLayout");
}

Series::~Series(){
    delete window;
    delete scaLayout;
    delete hLay;
    delete grpSeries;
    delete lblEpisode;
    delete lblSeason;
    delete txtSeason;
    delete txtEpisode;
    delete chkFinish;
    delete btnSave;
}

void Series::init(){
    QPixmap savePNG(":/icons/imgs/floppy.png");
    QPixmap modifyPNG(":/icons/imgs/modify.png");

    QIcon saveICO(savePNG);
    QIcon modifyICO(modifyPNG);

    hLay = new QHBoxLayout();
    grpSeries = new QGroupBox(name);

    lblSeason = new QLabel(tr("Season:"));
    lblEpisode = new QLabel(tr("Episode:"));

    txtSeason = new QLineEdit();
    txtSeason->setText(season);
    txtSeason->setAlignment(Qt::AlignHCenter);
    txtSeason->setMaxLength(4);
    txtEpisode = new QLineEdit();
    txtEpisode->setText(episode);
    txtEpisode->setAlignment(Qt::AlignHCenter);
    txtEpisode->setMaxLength(4);

    chkFinish = new QCheckBox(tr("Finish"));
    chkFinish->setChecked(finish);

    btnSave = new QPushButton(tr("Save"));
    btnSave->setIcon(saveICO);
    btnSave->setStyleSheet("max-width: 120px");
}

void Series::createSeries(){
    hLay->addWidget(lblSeason);
    hLay->addWidget(txtSeason);
    hLay->addWidget(lblEpisode);
    hLay->addWidget(txtEpisode);
    hLay->addWidget(chkFinish);
    hLay->addWidget(btnSave);

    grpSeries->setLayout(hLay);

    scaLayout->addWidget(grpSeries, position, 0, NULL);

    connect(txtSeason, SIGNAL(textEdited(QString)), this, SLOT(seasonChanged(QString)));
    connect(txtEpisode, SIGNAL(textEdited(QString)), this, SLOT(episodeChanged(QString)));
    connect(chkFinish, SIGNAL(stateChanged(int)), this, SLOT(finishChanged(int)));
    connect(btnSave, SIGNAL(released()), this, SLOT(saveSeries()));
}

void Series::seasonChanged(QString text){
    if(text != season){
        lblSeason->setStyleSheet("font-weight: 600;");
        sChanges = true;
    }else{
        lblSeason->setStyleSheet("font-weight: 400;");
        sChanges = false;
    }

    emit somethingChanged();
}

void Series::episodeChanged(QString text){
    if(text != episode){
        lblEpisode->setStyleSheet("font-weight: 600;");
        eChanges = true;
    }else{
        lblEpisode->setStyleSheet("font-weight: 400;");
        eChanges = false;
    }

    emit somethingChanged();
}

void Series::finishChanged(int state){
    if((finish && state == 2) || (!finish && state == 0)){
        fChanges = false;
    }else if((finish && state == 0) || (!finish && state == 2)){
        fChanges = true;
    }

    emit somethingChanged();
}

void Series::saveSeries(){
    season = txtSeason->text();
    episode = txtEpisode->text();
    finish = chkFinish->checkState() == 2;

    emit save(position);
    lblSeason->setStyleSheet("font-weight: 400;");
    lblEpisode->setStyleSheet("font-weight: 400;");
    sChanges = false;
    eChanges = false;
    fChanges = false;

    emit somethingChanged();
}

void Series::removeFromGUI(){
    QLayoutItem* it = scaLayout->takeAt(scaLayout->indexOf(grpSeries));
    delete it->widget();
    delete it;
}

void Series::reDraw(){
    init();
    createSeries();

    if(sChanges){
        lblSeason->setStyleSheet("font-weight: 600;");
    }

    if(eChanges){
        lblEpisode->setStyleSheet("font-weight: 600;");
    }
}

// SETTER AND GETTER METHODS

void Series::setWindow(MainWindow* window){
    this->window = window;

    scaLayout = window->findChild<QGridLayout*>("scaLayout");
}

void Series::setID(int ID){
    this->ID = ID;
}

void Series::setPosition(int position){
    this->position = position;
}

void Series::setName(QString name){
    this->name = name;
    grpSeries->setTitle(name);
}

void Series::setSeason(QString season){
    this->season = season;
}

void Series::setEpisode(QString episode){
    this->episode = episode;
}

void Series::setFinish(bool finish){
    this->finish = finish;
}

void Series::setChanges(bool changes){
    sChanges = changes;
    eChanges = changes;
    fChanges = changes;
}

int Series::getID(){
    return ID;
}

QString Series::getName(){
    return name;
}

QString Series::getSeason(){
    return season;
}

QString Series::getEpisode(){
    return episode;
}

bool Series::getFinish(){
    return finish;
}

int Series::getPosition(){
    return position;
}

bool Series::getChanges(){
    return sChanges || eChanges || fChanges;
}
