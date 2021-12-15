
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

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
        while (s != "done") {
            trainFile << s;
            s = read();
        }
        write("Upload complete.");
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

// you may add here helper classes




// you may edit this class
class Command {
protected:
    string description;
    DefaultIO *dio;
    TimeSeries trainTable;
    TimeSeries testTable;
    vector<AnomalyReport> reports;
public:
    Command(DefaultIO *dio, string description) : dio(dio), description(description), trainTable(nullptr), testTable(
            nullptr) {}
    virtual void execute() = 0;
    virtual ~Command() {}
    void setTableState(const TimeSeries & trainTable2, const TimeSeries & testTable2) {
        this->testTable = testTable2;
        this->trainTable = trainTable2;
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
    string getDescription(){
        return this->description;
    }
    vector<AnomalyReport> getReports(){
        return this->reports;
    }
};

class UploadCommand : public Command {

public:
    UploadCommand(DefaultIO * dio, string description) : Command(dio, description) {};

    virtual void execute()  {
        dio->write("Please upload your local train CSV file.\n");
        dio->downloadFile("anomalyTrain.csv");
        TimeSeries trainTable("anomalyTrain.csv");
        this->trainTable = trainTable;
        dio->write("Please upload your local test CSV file.\n");
        dio->downloadFile("anomalyTest.csv");
        TimeSeries testTable("anomalyTest.csv");
        this->testTable = testTable;
    }

};


class AlgorithmSettingsCommand: public Command{
public:
    AlgorithmSettingsCommand(DefaultIO * dio, string description) : Command(dio, description) {};

    virtual void execute(){

    }
};

class DetectAnomalyCommand : public Command{
public:
    DetectAnomalyCommand(DefaultIO * dio, string description) : Command(dio, description) {};
    virtual void execute(){
        auto * hybridAnomalyDetector = new HybridAnomalyDetector();
        hybridAnomalyDetector->learnNormal(this->trainTable);
        vector<AnomalyReport> reports = hybridAnomalyDetector->detect(this->testTable);
        dio->write("anomaly detection complete.\n");
        this->setReportsState(reports);
        delete hybridAnomalyDetector;
    }
};

class DisplayResultsCommand : public Command{
public:
    DisplayResultsCommand(DefaultIO * dio, string description) : Command(dio, description) {};
    virtual void execute(){
        for (auto const &item: this->reports){
            dio->write((float )item.timeStep);
            dio->write('\t' + item.description + '\n');
            dio->write("Done.\n");
        }
    }
};


class AnalyzeAnomaliesCommand : public Command{
public:
    AnalyzeAnomaliesCommand(DefaultIO * dio, string description) : Command(dio, description) {};
    virtual void execute(){

    }
};

// implement here your command classes

class Mediator {

    Command ** commands;
    int numOfCommands;
public:
    Mediator(Command * commandUpload, Command * commandSettings, Command * commandDetect, Command * commandResults , Command * commandAnalyze){
        this->commands = new Command*[5];
        this->commands[0] = commandUpload;
        this->commands[1] = commandSettings;
        this->commands[2] = commandDetect;
        this->commands[3] = commandResults;
        this->commands[4] = commandAnalyze;
        this->numOfCommands = 5;
    }
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

};

#endif /* COMMANDS_H_ */