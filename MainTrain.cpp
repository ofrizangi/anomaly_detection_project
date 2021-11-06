
#include <iostream>
#include <vector>
#include "anomaly_detection_util.h"
#include "TimeSeries.h"

using namespace std;


void printVector(vector<float> t) {
    vector<float>::iterator it;
    for (it = t.begin(); it != t.end(); it++) {
        cout << *it << endl;
    }
}


int main() {


    TimeSeries *s = new TimeSeries("series.csv");
    map<string, vector<float>>::iterator it;
    for (it = s->table.begin(); it!=s->table.end(); it++) {
        cout << it->first << endl;
        printVector(it->second);
    }

    return 0;
}

