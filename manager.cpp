#include "manager.h"

vector<Series*> series_glob;
int ID_glob;

Manager::Manager(QObject *parent){
    w = new MainWindow();
    w->show();

#ifdef _WIN32
    WCHAR temp[100];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, temp);

    wstring ws(temp);
    string str(ws.begin(), ws.end());

    mainFolder = str;
    mainFolder.append("\\series");

#elif __APPLE__
    struct passwd *pw = getpwuid(getuid());
    mainFolder = pw->pw_dir;
    mainFolder = mainFolder + "/.series";

#elif __unix__
    struct passwd *pw = getpwuid(getuid());
    mainFolder = pw->pw_dir;
    mainFolder = mainFolder + "/.series";
#endif

    btnSaveAll = w->findChild<QPushButton*>("btnSaveAll");
    connect(btnSaveAll, SIGNAL(released()), this, SLOT(saveAll()));

    btnAddSeries = w->findChild<QPushButton*>("btnAddSeries");
    connect(btnAddSeries, SIGNAL(released()), this, SLOT(insertNewSeries()));

    btnModify = w->findChild<QPushButton*>("btnModify");
    connect(btnModify, SIGNAL(released()), this, SLOT(modifySeries()));

    exitAction = w->findChild<QAction*>("actionExit");
    connect(exitAction, SIGNAL(triggered()), w, SLOT(close()));

    aboutAction = w->findChild<QAction*>("actionAbout");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(openAbout()));

    insSeries = new InsertDialog(w);
    insSeries->setWindowModality(Qt::WindowModal);
    modSeries = new ModifyDialog(w);
    modSeries->setWindowModality(Qt::WindowModal);
    aboutSeries = new AboutDialog(w);

    connect(insSeries, SIGNAL(newSeries(QString, QString, QString)), this, SLOT(addSeries(QString, QString, QString)));
    connect(modSeries, SIGNAL(del(int)), this, SLOT(deleteSeries(int)));
    connect(modSeries, SIGNAL(changeName(int, QString)), this, SLOT(changeSeriesName(int, QString)));
    connect(modSeries, SIGNAL(changePosition(int, int, int)), this, SLOT(changeSeriesPosition(int, int, int)));
    connect(modSeries, SIGNAL(endRepositioning()), this, SLOT(orderSeries()));
    connect(w, SIGNAL(saveChanges()), this, SLOT(saveAll()));
}

Manager::~Manager(){
    delete w;
    delete modSeries;
    delete insSeries;
    delete btnAddSeries;
    delete btnSaveAll;
    delete btnModify,
    delete db;
}

// callback functions for querys

int qryLoad_callback(void* data, int argc, char** argv, char** azColName){
    data = 0;

    bool finish = argv[4][0] == '1';

    series_glob.push_back(new Series(NULL, atoi(argv[0]), argv[1], argv[2], argv[3], finish, atoi(argv[5])));

    return 0;
}

int qryID_callback(void* data, int argc, char** argv, char** azColName){
    data = 0;

    ID_glob = atoi(argv[0]);

    return 0;
}

//main controls

void Manager::main(){
    if(!checkMainFolder()){
        QMessageBox::critical(NULL, tr("Error"), tr("Fatal error while checking your home."));
        return;
    }

    if(!checkDb()){
        TutorialDialog* tutorial = new TutorialDialog(w);
        tutorial->setWindowModality(Qt::WindowModal);
        tutorial->show();
        openDb(true);
    }else{
        openDb(false);
        loadSeries();
    }
}

//check if the main folder exists; if not, create it

bool Manager::checkMainFolder(){
    bool issue = false;

    DIR *dp;
    dp = opendir(mainFolder.c_str());

	if (dp == NULL){
        string create = "mkdir " + mainFolder;
		system(create.c_str());

		dp = opendir(mainFolder.c_str());
        if(dp == NULL){
            issue = true;
        }
	}

	closedir(dp);
	return !issue;
}

//check if db already exists; this determines the first access (if db doesn't exists yet)

bool Manager::checkDb(){
    bool exist = false;

    DIR *dp;
	struct dirent *dirp;
	vector<string> files = vector<string>();

	dp = opendir(mainFolder.c_str());

	while ((dirp = readdir(dp)) != NULL){
        files.push_back(string(dirp->d_name));
	}

    closedir(dp);

	for(vector<string>::iterator i = files.begin(); i != files.end() && !exist; ++i){
        if(*i == "series.sqlite")
            exist = true;
	}

	return exist;
}

//open db connection (create it, if necessary)

void Manager::openDb(bool create){
    string dbPath = mainFolder + "/series.sqlite";

    if(sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK){
        QString err = tr("Error while opening the database.");
        QMessageBox::critical(NULL, tr("Error"), err);
    }

    if(create){
        char* queryError = 0;

        const char* query = "CREATE TABLE Series(" \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, " \
        "Name varchar(100) NOT NULL, " \
        "Season varchar(5) NOT NULL, " \
        "Episode varchar(5) NOT NULL, " \
        "Finish BOOLEAN NOT NULL, " \
        "Position INTEGER NOT NULL)";

        if(sqlite3_exec(db, query, NULL, 0, &queryError) != SQLITE_OK){
            QString error = tr("Error while creating the database: ");
            error.append(queryError);

            QMessageBox::critical(NULL, tr("Error"), error);
        }
    }
}

void Manager::loadSeries(){
    string query = "SELECT * FROM Series ORDER BY Position DESC";
    char* queryError = 0;

    if(sqlite3_exec(db, query.c_str(), qryLoad_callback, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while reading from database: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);
        return;
    }

    Series* s;
    int n = series_glob.size();
    for(int i=0; i < n; i++){
        s = series_glob.back();
        series_array.push_back(s);
        series_glob.pop_back();
    }

    checkIssues();

    for(unsigned int i=0; i < series_array.size(); i++){
        series_array[i]->setWindow(w);
        series_array[i]->init();
        series_array[i]->createSeries();
        connect(series_array[i], SIGNAL(save(int)), this, SLOT(saveSeries(int)));
        connect(series_array[i], SIGNAL(somethingChanged()), this, SLOT(changes()));
    }
}

//public slots

void Manager::addSeries(QString name, QString season, QString episode){
    QString nameClean = cleanStr(name);
    name = cleanStrGUI(name);

    string nameStr = nameClean.toUtf8().constData();
    string seasonStr = season.toUtf8().constData();
    string episodeStr = episode.toUtf8().constData();

    int position = series_array.size();

    char pos[21];
    sprintf(pos, "%d", position);

    string query = "INSERT INTO Series (Name, Season, Episode, Finish, Position) VALUES ('" + nameStr + "', '" + seasonStr + "', '" + episodeStr + "', 0, " + pos + ")";
    char* queryError = 0;

    if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while creating new series: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);
    }

    query = "SELECT ID FROM Series WHERE Position=";
    query.append(pos);

    if(sqlite3_exec(db, query.c_str(), qryID_callback, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while creating new series: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);
    }

    series_array.push_back(new Series(w, -1, name, season, episode, false, position));

    series_array[position]->setID(ID_glob);
    series_array[position]->init();
    series_array[position]->createSeries();
    connect(series_array[position], SIGNAL(save(int)), this, SLOT(saveSeries(int)));
    connect(series_array[position], SIGNAL(somethingChanged()), this, SLOT(changes()));

    ID_glob = -1;
}


void Manager::saveSeries(int position){
    char intPos[21];
    sprintf(intPos, "%d", position);

    string pos = string(intPos);

    string finish;

    if(series_array[position]->getFinish()){
        finish = "1";
    }else{
        finish = "0";
    }

    string season = series_array[position]->getSeason().toUtf8().constData();
    string episode = series_array[position]->getEpisode().toUtf8().constData();
    string query = "UPDATE Series SET Season='" + season + "', Episode='" + episode + "', Finish=" + finish + " WHERE Position=" + pos;

    char *queryError = 0;

    if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while saving series: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);
    }
}

void Manager::saveAll(){
    for(unsigned int i=0; i<series_array.size(); i++){
        series_array[i]->saveSeries();
    }
}

void Manager::insertNewSeries(){
    insSeries->show();
}

void Manager::modifySeries(){
    modSeries->setSeries(series_array);
    modSeries->createList();
    modSeries->show();
}

void Manager::deleteSeries(int pos){
    char num1[21], num2[21], *queryError = 0;
    sprintf(num1, "%d", pos);

    string query = "DELETE FROM Series WHERE Position=";
    query.append(num1);

    if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while deleting data from database: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);
        return;
    }

    vector<Series*> temp;

    while(series_array.size() > (pos + 1)){
        temp.push_back(series_array.back());
        series_array.pop_back();

        temp[temp.size()-1]->removeFromGUI();
    }

    series_array[pos]->removeFromGUI();
    series_array.pop_back();

    while(temp.size() > 0){
        series_array.push_back(temp.back());
        temp.pop_back();
    }

    for(int i=pos; i<series_array.size(); i++){
        sprintf(num1, "%d", i);
        sprintf(num2, "%d", series_array[i]->getID());

        query = "UPDATE Series SET Position=";
        query.append(num1);
        query.append(" WHERE ID=");
        query.append(num2);

        if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
            QString error = tr("Error while updating series in the database: ");
            error.append(queryError);

            QMessageBox::critical(NULL, tr("Error"), error);
        }

        series_array[i]->setPosition(i);
        series_array[i]->reDraw();
    }

// do this operations to resize the GUI, because if the last series is deleted, the layout won't resize

    if(pos == series_array.size() && pos != 0){
        series_array[pos-1]->removeFromGUI();
        series_array[pos-1]->reDraw();
    }

}

void Manager::changeSeriesName(int pos, QString name){
    QString nameClean = cleanStr(name);
    name = cleanStrGUI(name);

    char numPos[21], *queryError = 0;
    sprintf(numPos, "%d", pos);

    string query = "UPDATE Series SET Name='";
    query.append(nameClean.toUtf8().constData());
    query.append("' WHERE Position=");
    query.append(numPos);

    if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while renaming series: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);

        return;
    }

    series_array[pos]->setName(name);
}

void Manager::changeSeriesPosition(int ID, int oldPos, int newPos){
    char IDstr[21], pos[21], *queryError = 0;

    sprintf(IDstr, "%d", ID);
    sprintf(pos, "%d", newPos);

    string query = "UPDATE Series SET Position=";
    query.append(pos);
    query.append(" WHERE ID=");
    query.append(IDstr);

    if(sqlite3_exec(db, query.c_str(), NULL, 0, &queryError) != SQLITE_OK){
        QString error = tr("Error while repositioning series: ");
        error.append(queryError);

        QMessageBox::critical(NULL, tr("Error"), error);

        return;
    }

    series_array[oldPos]->setPosition(newPos);
}

void Manager::orderSeries(){
    int length = series_array.size();

    for(int i=0; i<length; i++){
        series_array[i]->removeFromGUI();
    }

    bubbleSort();

    for(int i=0; i<length; i++){
        series_array[i]->reDraw();
    }
}

void Manager::changes(){
    w->setModify(series_array[0]->getChanges());

    for(unsigned int i=1; i<series_array.size(); i++){
        w->setModify(w->getModify() || series_array[i]->getChanges());
    }
}

void Manager::openAbout(){
    aboutSeries->show();
}

//private functions

void Manager::bubbleSort(){
    int length = series_array.size();
    Series* temp;

    for(int i=0; i<length-1; i++){
        for(int j=length-1; j>i; j--){
            if(series_array[j]->getPosition() < series_array[j - 1]->getPosition()){
                temp = series_array[j];
                series_array[j] = series_array[j - 1];
                series_array[j - 1] = temp;
            }
        }
    }
}

void Manager::checkIssues(){
    bool issues = false;
    string query;
    char *queryError = 0;

    for(unsigned int i=0; i<series_array.size() && !issues; i++){
        if(series_array[i]->getPosition() < 0 || (series_array[i]->getPosition() != i)){
            issues = true;
        }

        for(unsigned int j=i+1; j<series_array.size() && !issues; j++){
            if((series_array[i]->getPosition() == series_array[j]->getPosition()) || series_array[j]->getPosition() < 0){
                issues=true;
            }
        }
    }

    if(issues){
        QMessageBox::warning(NULL, tr("ARGH"), tr("ARGH! Something went wrong, series' positions may be different."));

        char num1[21], num2[21];
        for(unsigned int i=0; i<series_array.size(); i++){
            sprintf(num1, "%d", i);
            sprintf(num2, "%d", series_array[i]->getID());

            query = "UPDATE Series SET Position=";
            query.append(num1);
            query.append(" WHERE ID=");
            query.append(num2);

            if(sqlite3_exec(db, query.c_str(), qryLoad_callback, 0, &queryError) != SQLITE_OK){
                QString error = tr("Error while writing into database: ");
                error.append(queryError);

                QMessageBox::critical(NULL, tr("Error"), error);
                return;
            }

            series_array[i]->setPosition(i);
        }
    }
}

QString Manager::cleanStr(QString str){
    str = str.replace("'", "''");
    str = str.replace("""", """""");
    str = str.replace("&", "&&");

    return str;
}

QString Manager::cleanStrGUI(QString str){
    str = str.replace("&", "&&");

    return str;
}

