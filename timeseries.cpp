//Ofri Zangi 207488305
//Ben Plosk 208290833

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "timeseries.h"

using namespace std;

/**
* Constructor.
* @param fileName the name of the table
*/
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
            // going over all the features
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

/**
* A helper function for the constructor  that splits a string by a specific
*
* @param s the string we want to split
* @param del the char we want to split by
* @return a vector of all the string parts
*/
vector<string> TimeSeries::splitByTav(const string &s, char del) {
    int start = 0;
    int end = (int) s.find(del);
    vector<string> names;
    while (end != -1) {
        names.push_back(s.substr(start, end - start));
        start = end + 1;
        end = (int) s.find(del, start);
    }
    end = (int) s.find("\r");
    names.push_back(s.substr(start, end - start));
    return names;
}

/**
* Returning all the features of the table
*
* @return a vector of all the features
*/
vector<string> TimeSeries::getAllKeys() const {
    vector<string> newVector;
    for (auto const &element: this->table) {
        newVector.push_back(element.first);
    }
    return newVector;
}

/**
* Printing a single vector of values.
*
* @param t the vector we want to print
*/
void printVector(vector<float> t) {
    vector<float>::iterator it;
    for (it = t.begin(); it != t.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

/**
* printing all the table.
*/
void TimeSeries::printTable() {
    map<string, vector<float>>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); it++) {
        cout << it->first << ":" << endl;
        printVector(it->second);
    }
}

/**
* @return the table we created in the constructor
*/
map<string, vector<float>> TimeSeries::getTable() const {
    return this->table;
}

/**
* @return the number of lines in the table
*/
int TimeSeries::getNumberOfLines() const {
    vector<string> keys = getAllKeys();
    if (keys.empty()) {
        return 0;
    }
    return (int) this->table.at(keys[0]).size();
}

/**
* Destructor.
*/
TimeSeries::~TimeSeries() = default;