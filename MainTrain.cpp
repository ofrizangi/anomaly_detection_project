
#include <iostream>
#include <vector>
#include "anomaly_detection_util.h"
#include "TimeSeries.h"
#include "SimpleAnomalyDetector.h"

using namespace std;


//void printVector(vector<float> t) {
//    vector<float>::iterator it;
//    for (it = t.begin(); it != t.end(); it++) {
//        cout << *it << endl;
//    }
//}


//int main() {
//
//
//    TimeSeries *s = new TimeSeries("series.csv");
//    map<string, vector<float>>::iterator it;
//    for (it = s->table.begin(); it!=s->table.end(); it++) {
//        cout << it->first << endl;
//        printVector(it->second);
//    }
//
//    return 0;
//}

int main(){
    TimeSeries t("series.csv");
    SimpleAnomalyDetector s;
    s.learnNormal(t);
    vector<correlatedFeatures> c = s.getNormalModel();
    //vector<correlatedFeatures>:: iterator it;
    //for(int it = c.begin(); it!=c.end();it++){

    return 0;
}