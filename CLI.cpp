//Ofri Zangi 207488305
//Ben Plosk 208290833

#include "CLI.h"


CLI::CLI(DefaultIO *dio) : dio(dio) {
}

void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for (int i = 0; i < size; i++) {
        string str = to_string(i+1);
        dio->write(str + ".");
        dio->write(this->commands[i]->getDescription());
        dio->write("\n");
    }
    dio->write("6.exit\n");
}

void CLI::start() {
    Command *commands[5];
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
    vector<AnomalyReport> *r = new vector<AnomalyReport>();
    CommandMediator mediator = CommandMediator(d, t1, t2, r);
    for (int i = 0; i < size; i++) {
        commands[i]->setMediator(&mediator);
    }
    this->printMenu();
    string choiceStr = dio->read();;
    int choice = atoi(choiceStr.c_str());
    while (choice <= size && choice >= 1) {
        this->commands[(int) choice - 1]->execute();
        this->printMenu();
        choiceStr = dio->read();
        choice = atoi(choiceStr.c_str());
    }
}

CLI::~CLI() {}
