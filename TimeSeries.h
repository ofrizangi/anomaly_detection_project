#include <vector>
#include <map>
#include <fstream>
using namespace std;


#ifndef TIMESERIESPROJECT_TIMESERIES_H
#define TIMESERIESPROJECT_TIMESERIES_H


class TimeSeries {
    map<string, vector<float>> table;

public:
    TimeSeries(const char *fileName);

    map<string, vector<float>> getTable() const;

    vector<string> getAllKeys () const;
    void printTable();

    float getValue(string feature, float time);

private:
    vector<string> splitByTav(string s, char del);


};

#endif
