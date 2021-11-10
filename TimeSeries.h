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
    int getNumberOfLines() const;
    ~TimeSeries();


private:
    vector<string> splitByTav(const string & s, char del);


};

#endif
