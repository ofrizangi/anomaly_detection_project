/*
void changeTableState(const TimeSeries & table1, const TimeSeries & table2) {
    for (int i=0; i< this->numOfCommands; i++){
        this->commands[i]->setTableState(table1, table2);
    }
}
void changeReportsState(const vector<AnomalyReport> & r){
    for (int i=0; i< this->numOfCommands; i++){
        this->commands[i]->setReportsState(r);
    }
}
~Mediator() {
    delete commands;
}
*/


/*
class CommandArrayMediator : public CommandMediator {
//    Command** commands = nullptr;
//    int size = 0;
public:
    CommandArrayMediator(HybridAnomalyDetector detector,TimeSeries trainTable,TimeSeries testTable,
                         vector<AnomalyReport> reports) :
            CommandMediator(detector,trainTable,testTable,reports)
    {
//            this->commands = new Command*[5];
//            this->commands[0] = commandUpload;
//            this->commands[1] = commandSettings;
//            this->commands[2] = commandDetect;
//            this->commands[3] = commandResults;
//            this->commands[4] = commandAnalyze;
//            this->size = 5;
    }

    void update(HybridAnomalyDetector detector){
        this->detector = detector;
    }
    void update(TimeSeries trainTable,TimeSeries testTable){
        this->trainTable = trainTable;
        this->testTable = testTable;
    }
    void update(vector<AnomalyReport> reports){
        this->reports = reports;
    }
//    Command** getArray() {
//        return this->commands;
//    }
//    int getSize() {
//        return this->size;
//    }
    ~CommandArrayMediator(){
//        delete &(this->detector);
//        delete &(this->trainTable);
//        delete &(this->testTable);
//        delete &(this->reports);
    };
};
*/


/*void setTableState(const TimeSeries & trainTable, const TimeSeries & testTable) {
    this->testTable = testTable;
    this->trainTable = trainTable;
}
void setReportsState(const vector<AnomalyReport> & report){
    this->reports.clear();
    for ( auto const &item:report){
        this->reports.push_back(item);
    }
}
TimeSeries getTestTable(){
    return this->testTable;
}
TimeSeries getTrainTable(){
    return this->trainTable;
}
 vector<AnomalyReport> getReports(){
    return this->reports;
}
 */



/*
 // need this???????????
class StandardIO : public DefaultIO {

    virtual string read() {
        string s;
        cin >> s;
        return s;
    }

    virtual void write(string text) {
        cout << text;
    }

    virtual void write(float f) {
        cout << f;
    }

    virtual void read(float *f) {
        cin >> *f;
    }
};
 */