//
// Created by Ofri on 12/15/2021.
//

#include "CLI.h"


CLI::CLI(DefaultIO *dio): dio(dio) {
//    this->dio = dio;
//    Command* c1 = new UploadCommand(dio);
//    Command* c2 = new AlgorithmSettingsCommand(dio);
//    Command* c3 = new DetectAnomalyCommand(dio);
//    Command* c4 = new DisplayResultsCommand(dio);
//    Command* c5 = new AnalyzeAnomaliesCommand(dio);
//    HybridAnomalyDetector d = HybridAnomalyDetector();
//    TimeSeries t1 = TimeSeries();
//    TimeSeries t2 = TimeSeries();
//    vector<AnomalyReport> r =vector<AnomalyReport>();
//    this->mediator = CommandArrayMediator(d,t1,t2,r,c1,c2,c3,c4,c5);
//    for(int i =0;i<this->mediator.getSize() ;i++) {
//        this->mediator.getArray()[i]->setMediator(&(this->mediator));
//    }
}
void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for(int i =0;i<size ;i++) {
        dio->write(i+1);
        dio->write(".");
        dio->write(this->commands[i]->getDescription());
        dio->write("\n");
    }
    dio->write("6.exit\n");
}

void CLI::start() {
     Command* commands[5];
     commands[0] = new UploadCommand(dio);
     commands[1] = new AlgorithmSettingsCommand(dio);
     commands[2] = new DetectAnomalyCommand(dio);
     commands[3] = new DisplayResultsCommand(dio);
     commands[4] = new AnalyzeAnomaliesCommand(dio);
     this->commands = commands;
     this->size = 5;
    HybridAnomalyDetector d = HybridAnomalyDetector();
    TimeSeries t1 = TimeSeries();
    TimeSeries t2 = TimeSeries();
    vector<AnomalyReport>* r =new vector<AnomalyReport>();
    CommandMediator mediator = CommandMediator(d,t1,t2,r);
     for(int i=0;i<size;i++) {
         commands[i]->setMediator(&mediator);
     }
    this->printMenu();
    float choice ;
    dio->read(&choice);
    while (choice <=size && choice>=1) {
        this->commands[(int)choice-1]->execute();
        this->printMenu();
        dio->read(&choice);
    }
}

CLI::~CLI() {}
