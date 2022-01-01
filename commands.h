//Ofri Zangi 207488305
//Ben Plosk 208290833

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include <iomanip>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class RangePair {
    long start;
    long finish;
public:
    RangePair() {this->start =0; this->finish = 0;}
    RangePair(long x,long y)  {this->start = x; this->finish = y;}
    void setStart(long newStart) {this->start = newStart;}
    void setFinish(long newFinish) {this->finish = newFinish;}
    long getStart() {return this->start;}
    long getFinish() {return this->finish;}
    bool Intersection(RangePair other) {
        if((this->getStart() <= other.getFinish() &&
            this->getFinish() >= other.getFinish() )||
           (this->getFinish() >= other.getStart() &&
            this->getFinish() <= other.getFinish())||
           (this->getStart() >= other.getStart() &&
            this->getFinish() <= other.getFinish() ) ||
           (this->getStart() <= other.getStart() &&
            this->getFinish() >= other.getFinish()))
            return true;
        else
            return false;
    }
};

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
        while (s != "done" && s != "done\r") {
            trainFile << "\n";
            trainFile << s;
            s = read();
        }
        trainFile.close();
        write("Upload complete.\n");
    }
};





class Command;

class CommandMediator {
protected:
    HybridAnomalyDetector detector ;
    TimeSeries trainTable ;
    TimeSeries testTable ;
    vector<AnomalyReport>* reports ;
public:
    CommandMediator(HybridAnomalyDetector detector,TimeSeries trainTable,TimeSeries testTable,vector<AnomalyReport>* reports) :
            detector(detector) , trainTable(trainTable), testTable(testTable) ,reports(reports) {};


    void update(HybridAnomalyDetector detector){
        this->detector = detector;
    }
    void update(TimeSeries trainTable,TimeSeries testTable){
        this->trainTable = trainTable;
        this->testTable = testTable;
    }
    void update(vector<AnomalyReport>* reports){
        for(AnomalyReport report : *(reports) ) {
            this->reports->push_back(report);
        }
    }
    HybridAnomalyDetector getDetector() {
        return this->detector;
    }
    TimeSeries getTrainTable() {
        return this->trainTable;
    }
    TimeSeries getTestTable() {
        return this->testTable;
    }
    vector<AnomalyReport>* getReports() {
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
        dio->write("\n");
        float f = 0;
        dio->write("Type a new threshold\n");
        dio->read(&f);
        HybridAnomalyDetector h = this->mediator->getDetector();
        h.setThreshold(f);
        this->mediator->update(h);
    }
};

class DetectAnomalyCommand : public Command{
public:
    DetectAnomalyCommand(DefaultIO * dio) : Command(dio) {this->description = "detect anomalies";};
    virtual void execute(){
        HybridAnomalyDetector h = this->mediator->getDetector();
        h.learnNormal(this->mediator->getTrainTable());
        vector<AnomalyReport> reports = h.detect( (this->mediator->getTestTable()) );
        dio->write("anomaly detection complete.\n");
        this->mediator->update(&reports);
    }
};

class DisplayResultsCommand : public Command{
public:
    DisplayResultsCommand(DefaultIO * dio) : Command(dio) {this->description = "display results";};
    virtual void execute(){
        for (auto const &item: *(this->mediator->getReports()) ){
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
        vector<RangePair> anomaly_ranges = vector<RangePair>();
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
            RangePair pair = RangePair(numStart,numEnd);
            anomaly_ranges.push_back(pair);
            //push range to range vector
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
        for(AnomalyReport report :*(this->mediator->getReports())) {
            report_ranges.insert({report.description,vector<long>()});
        }
//        fill the vectors with the times
        for(AnomalyReport report : *(this->mediator->getReports()) ) {
            report_ranges[report.description].push_back(report.timeStep);
        }
        vector<RangePair> all_ranges = vector<RangePair>();
        //for each vector take the subsequent times and make a range of them
        for(auto const& report : report_ranges) {
            string description = report.first;
            RangePair currentPair = RangePair(report.second[0],report.second[0]);
            for(int i=0 ; i<report.second.size()-1;i++) {
                if(report.second[i+1] - report.second[i] == 1 ) {
                    currentPair.setFinish(report.second[i+1]);
                }
                else {
                    all_ranges.push_back(currentPair);
                    currentPair = RangePair(report.second[i+1],report.second[i+1]);
                }
                if(i+1 == report.second.size()-1)
                    all_ranges.push_back(currentPair);
            }
        }
        int falsePositive = 0, truePositive = 0;
        //for each such range, if it matches with number in anomalies vector TP++ ,if not FP++
        for(RangePair trueAnomaly : anomaly_ranges) {
            for(RangePair anomalyDetected : all_ranges){
                if(trueAnomaly.Intersection(anomalyDetected) == true ) {
                    truePositive++;
                    break;
                }
            }
        }
        for(RangePair anomalyDetected : all_ranges) {
            bool flag = true;
            for(RangePair trueAnomaly : anomaly_ranges){
                if(anomalyDetected.Intersection(trueAnomaly) == true) {
                    flag = false;
                    break;
                }
            }
            if(flag == true)
                falsePositive++;
        }

        //calculate rates
        float truePositiveRate = (float)truePositive/anomalyLines;
        float falseAlarmRate = (float)falsePositive/positiveLines;
        //round up to 3 digits after decimal
        truePositiveRate*=1000;
        falseAlarmRate*=1000;
        int truePositiveRate2 =truePositiveRate;
        int falseAlarmRate2 = falseAlarmRate;
        truePositiveRate = (float)truePositiveRate2/1000;
        falseAlarmRate = (float)falseAlarmRate2/1000;
        //write rates
        dio->write("True Positive Rate: ");
        dio->write(truePositiveRate);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(falseAlarmRate);
        dio->write("\n");
    }
};

#endif /* COMMANDS_H_ */
