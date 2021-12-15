//
// Created by Ofri on 12/15/2021.
//

#include "CLI.h"


CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    this->commands = new Command *[5];
    this->commands[0] = new UploadCommand(dio, "1. upload a time series csv file");
    this->commands[1] = new AlgorithmSettingsCommand(dio, "2. algorithm settings");
    this->commands[2] = new DetectAnomalyCommand(dio, "3. detect anomalies");
    this->commands[3] = new DisplayResultsCommand(dio, "4. display results");
    this->commands[4] = new AnalyzeAnomaliesCommand(dio, "5. upload anomalies and analyze results");
    this->numOfCommands = 5;
    this->mediator = new Mediator(this->commands[0], this->commands[1], this->commands[2], this->commands[3],
                                  this->commands[4]);
}


void CLI::start() {
    cout << "Welcome to the Anomaly Detection Server." << "\n" << "Please choose an option:" << "\n";
    for (int i = 0; i < this->numOfCommands; i++) {
        cout << commands[i]->getDescription() << "\n";
    }
    int choice;
    cin >> choice;
    while (choice != 6) {
        switch (choice) {
            case 1:
                commands[0]->execute();
                mediator->changeTableState(commands[0]->getTrainTable(), commands[0]->getTestTable());
            case 3:
                commands[2]->execute();
                mediator->changeReportsState(commands[2]->getReports());
            case 4:
                commands[3]->execute();
        }
        cin >> choice;
    }

}

CLI::~CLI() {
    delete dio;
    for (int i = 0; i < this->numOfCommands; i++) {
        delete commands[i];
    }
    delete commands;
}
