#include <vector>
#include <map>
using namespace std;


#ifndef TIMESERIESPROJECT_TIMESERIES_H
#define TIMESERIESPROJECT_TIMESERIES_H


class TimeSeries {
public:
    map<string, vector<float>> table;
public:
    TimeSeries(string s);
};

//std::vector <std::string> splitBy(std::string s, char tav);



#endif
