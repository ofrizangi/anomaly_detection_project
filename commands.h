
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {};

    void downloadFile(const char *fileName) {
        ofstream trainFile(fileName);
        string s = read();
        trainFile << s;
        s = read();
        while (s != "done") {
            trainFile << "\n";
            trainFile << s;
            s = read();
        }
        trainFile.close();
        write("Upload complete.\n");
    }

    // you may add additional methods here
};


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

class Command;

class CommandMediator {
protected:
    HybridAnomalyDetector detector ;
    TimeSeries trainTable ;
    TimeSeries testTable ;
    vector<AnomalyReport> reports ;
public:
    CommandMediator(HybridAnomalyDetector detector,TimeSeries trainTable,TimeSeries testTable,vector<AnomalyReport> reports) :
    detector(detector) , trainTable(trainTable), testTable(testTable) ,reports(reports) {};


    virtual void update(HybridAnomalyDetector detector) = 0;
    virtual void update(TimeSeries trainTable,TimeSeries testTable) = 0;
    virtual void update(vector<AnomalyReport> reports) = 0;
    HybridAnomalyDetector getDetector() {
        return this->detector;
    }
    TimeSeries getTrainTable() {
        return this->trainTable;
    }
    TimeSeries getTestTable() {
        return this->testTable;
    }
    vector<AnomalyReport> getReports() {
        return this->reports;
    }
};

class Command {
protected:
    CommandMediator* mediator = nullptr;
    string description;
    DefaultIO *dio;

public:
    Command(DefaultIO *dio) : dio(dio) {};
    Command(DefaultIO *dio, string description) : dio(dio), description(description)  {}
    virtual void execute() = 0;
    virtual ~Command() {}
    void setMediator(CommandMediator* mediator){
        this->mediator = mediator;
    }
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
    string getDescription(){
        return this->description;
    }
};

class UploadCommand : public Command {

public:
    UploadCommand(DefaultIO * dio) : Command(dio)  {this->description = "upload a time series csv file";};
    virtual void execute()  {
        dio->write("Please upload your local train CSV file.\n");
        dio->downloadFile("anomalyTrain.csv");
        TimeSeries trainTable("anomalyTrain.csv");
        dio->write("Please upload your local test CSV file.\n");
        dio->downloadFile("anomalyTest.csv");
        TimeSeries testTable("anomalyTest.csv");
        this->mediator->update(trainTable,testTable);
    }
};


class AlgorithmSettingsCommand: public Command{
public:
    AlgorithmSettingsCommand(DefaultIO * dio) : Command(dio) {this->description = "algorithm settings";};

    virtual void execute(){
        dio->write("The current correlation threshold is ");
        dio->write(this->mediator->getDetector().getThreshold());
        dio->write('\n');
        float f = 0;
        dio->read(&f);
        this->mediator->getDetector().setThreshold(f);
    }
};

class DetectAnomalyCommand : public Command{
public:
    DetectAnomalyCommand(DefaultIO * dio) : Command(dio) {this->description = "detect anomalies";};
    virtual void execute(){
        this->mediator->getDetector().learnNormal(this->mediator->getTrainTable());
        vector<AnomalyReport> reports = this->mediator->getDetector().detect( (this->mediator->getTestTable()) );
        dio->write("anomaly detection complete.\n");
        this->mediator->update(reports);
    }
};

class DisplayResultsCommand : public Command{
public:
    DisplayResultsCommand(DefaultIO * dio) : Command(dio) {this->description = "display results";};
    virtual void execute(){
        for (auto const &item: (this->mediator->getReports()) ){
            dio->write((float)item.timeStep);
            dio->write('\t' + item.description + '\n');
        }
        dio->write("Done.\n");
    }
};


class AnalyzeAnomaliesCommand : public Command{
public:
    AnalyzeAnomaliesCommand(DefaultIO * dio) : Command(dio) {this->description = "upload anomalies and analyze results";};
    virtual void execute(){
        dio->write("Please upload your local anomalies file.\n");
        //dio->downloadFile("Anomalies.csv");
        vector<int> Anomalies = vector<int>();
        int anomalyLines = 0;
        string s = dio->read();
        while (s != "done") {
            anomalyLines++;
            //split s into start - finish
            int stringStart = 0;
            int stringEnd = (int) s.find(',');
            int numStart = stoi(s.substr(stringStart,stringEnd-stringStart));
            stringStart = stringEnd+1;
            stringEnd = (int) s.find('\r');
            int numEnd = stoi(s.substr(stringStart,stringEnd-stringStart));
            //push in vector all numbers between start and finish
            for(int i = numStart ; i<=numEnd ; i++) {
                Anomalies.push_back(i);
            }
            //read next line
            s = dio->read();
        }
        dio->write("Upload complete.\n");
        //calculate N
        //first calc total amount of lines
        int totalLines = this->mediator->getTestTable().getNumberOfLines();
        int negativeLines = Anomalies.size();
        int positiveLines = totalLines - negativeLines;
        //calculate TP FP
        //calc whole reports as ranges
        map<string,vector<long>> report_ranges = map<string,vector<long>>();
        //add all descriptions and create vectors for them
        for(AnomalyReport report :this->mediator->getReports()) {
            report_ranges.insert({report.description,vector<long>()});
        }
        //fill the vectors with the times
        for(AnomalyReport report : this->mediator->getReports()) {
            report_ranges[report.description].push_back(report.timeStep);
        }
        //for each vector take the subsequent times and make a range of them
        for(AnomalyReport report : this->mediator->getReports()) {
            for(int i=0 ; i<report_ranges[report.description].size()-1;i++) {
                if(report_ranges[report.description][i+1] - report_ranges[report.description][i] == 1 )
            }
        }

        //for each such range, if it matches with number in anomalies vector TP++
        //if not FP++

        //calculate rates
        //false alarm rate = FP/positiveLines
        //true positive rate = TP/anomalyLines
        //write rates
    }
};

class CommandArrayMediator : public CommandMediator {
    Command** commands;
    int size;
public:
    CommandArrayMediator(HybridAnomalyDetector detector,TimeSeries trainTable,TimeSeries testTable,
                         vector<AnomalyReport> reports,Command * commandUpload, Command * commandSettings,
                         Command * commandDetect,Command * commandResults ,Command * commandAnalyze) :
            CommandMediator(detector,trainTable,testTable,reports){
        this->commands = new Command*[5];
        this->commands[0] = commandUpload;
        this->commands[1] = commandSettings;
        this->commands[2] = commandDetect;
        this->commands[3] = commandResults;
        this->commands[4] = commandAnalyze;
        this->size = 5;
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
    Command** getArray() {
        return this->commands;
    }
    int getSize() {
        return this->size;
    }
    ~CommandArrayMediator(){
        delete &(this->detector);
        delete &(this->trainTable);
        delete &(this->testTable);
        delete &(this->reports);
    };
};

#endif /* COMMANDS_H_ */
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