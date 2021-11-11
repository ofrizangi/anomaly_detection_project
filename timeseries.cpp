#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "timeseries.h"

using namespace std;

TimeSeries::TimeSeries(const char *fileName) {
    fstream readFile;
    readFile.open(fileName, ios::in);
    if (readFile.is_open()) {
        //getting the features
        string names;
        getline(readFile, names);
        vector<string> properties = splitByTav(names, ',');

        //an array that contains all the vectors, each place holds a vector
        vector<float> *arr = new vector<float>[properties.size()];

        //making vectors for every feature
        vector<string>::iterator it;
        vector<string> values;
        int place = 0;
        while (getline(readFile, names)) {
            values = splitByTav(names, ',');
            for (it = values.begin(); it != values.end(); it++) {
                arr[place].push_back(stof(*it));
                place++;
            }
            place = 0;
        }
        // building the set
        place = 0;
        for (it = properties.begin(); it != properties.end(); it++) {
            this->table.insert({*it, arr[place]});
            place++;
        }
        delete[] arr;
    }
    readFile.close();
}

// a help function for the constructor that splits a string by a specific char
vector<string> TimeSeries::splitByTav(const string & s, char del) {
    int start = 0;
    int end = (int)s.find(del);
    vector<string> names;
    while (end != -1) {
        names.push_back(s.substr(start, end - start));
        start = end + 1;
        end = (int)s.find(del, start);
    }
    end = (int)s.find("\r");
    names.push_back(s.substr(start, end - start));
    return names;
}

//returning all the features of the table
vector<string> TimeSeries::getAllKeys() const {
    vector<string> newVector;
    for (auto const & element: this->table) {
        newVector.push_back(element.first);
    }
    return newVector;
}

// printing a single vector of values
void printVector(vector<float> t) {
    vector<float>::iterator it;
    for (it = t.begin(); it != t.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

// printing all the table
void  TimeSeries::printTable()  {
    map<string, vector<float>>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); it++) {
        cout << it->first <<":" << endl;
        printVector(it->second);
    }
}

// returning the value of a feature i and time j
//treating the time column as if it's always called 'Time' , but we have to find a way to recognize the column
//float TimeSeries::getValue(string feature, float time) {
//    vector<float>::iterator it;
//    vector<float> times = this->table["Time"];
//    int place = 0;
//    // we want to find the right place in the vector
//    for (it = times.begin(); it != times.end(); it++) {
//        if (time == *it) {
//            break;
//        }
//        place++;
//    }
//    vector<float> values = this->table[feature];
//    return values[place];
//}


map<string, vector<float>> TimeSeries::getTable() const {
    return this->table;
}

int TimeSeries::getNumberOfLines() const{
    vector<string> keys = getAllKeys();
    if(keys.empty()){
        return 0;
    }
    return (int)this->table.at(keys[0]).size();
}

TimeSeries::~TimeSeries() = default;