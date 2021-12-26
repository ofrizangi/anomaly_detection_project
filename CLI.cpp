//
// Created by Ofri on 12/15/2021.
//

#include "CLI.h"


CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    Command* c1 = new UploadCommand(dio);
    Command* c2 = new AlgorithmSettingsCommand(dio);
    Command* c3 = new DetectAnomalyCommand(dio);
    Command* c4 = new DisplayResultsCommand(dio);
    Command* c5 = new AnalyzeAnomaliesCommand(dio);

    this->mediator = new CommandArrayMediator(HybridAnomalyDetector(), TimeSeries(),TimeSeries() ,
                                              vector<AnomalyReport>(),c1,c2,c3,c4,c5);
    for(int i =0;i<this->mediator->getSize() ;i++) {
        this->mediator->getArray()[i]->setMediator(this->mediator);
    }
}


void CLI::start() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for(int i =0;i<this->mediator->getSize() ;i++) {
        dio->write(i+1);
        dio->write(".");
        dio->write(this->mediator->getArray()[i]->getDescription());
        dio->write("\n");
    }
    float choice ;
    dio->read(&choice);
    while (choice <=6 && choice>=1) {
        this->mediator->getArray()[(int)choice-1]->execute();
        dio->read(&choice);
    }
}

CLI::~CLI() {
    delete dio;
    delete mediator;
}
