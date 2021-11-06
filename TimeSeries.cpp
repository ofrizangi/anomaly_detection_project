#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
//#include "TimeSeries.h"

using namespace std;


class TimeSeries {

public:
    map<string, vector<float>> table;


public:
    TimeSeries(string fileName) {
        ifstream readFile(fileName);
        string names;
        getline(readFile, names);
        vector<string> properties = splitBy(names, ',');
        vector<float> arr[properties.size()];

        vector<string>::iterator it;
        vector<string> values;
        while (getline(readFile, names)) {
            values = splitBy(names, ',');
            int place = 0;
            for (it = values.begin(); it != values.end(); it++) {
                arr[place].push_back(stof(*it));
                place++;
                it++;
            }
        }
        vector<string>::iterator itr;
        for (itr = properties.begin(); itr != properties.end(); it++) {
            this->table.insert({*itr, arr[0]});
        }
    }


    vector<string> splitBy(string s, char del) {
        int start = 0;
        int end = s.find(del);
        vector<string> names;
        while (end != -1) {
            names.push_back(s.substr(start, end - start));
            start = end + 1;
            end = s.find(del, start);
        }
        names.push_back(s.substr(start, s.length() - 1));
        return names;
    }


};
