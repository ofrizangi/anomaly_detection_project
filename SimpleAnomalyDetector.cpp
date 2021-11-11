#include <iostream>
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"

using namespace std;
const float minAllowedCorrelation = 0.5;

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;




//this function creates a correlated features struct
correlatedFeatures correlatedFeaturesCreator(string feature1, string feature2, float correlation, vector<float> v1,
                                             vector<float> v2) {
    correlatedFeatures newPair;
    newPair.feature1 = feature1;
    newPair.feature2 = feature2;
    newPair.corrlation = correlation;
    //to get linear reg we need to calculate the points and size
    //calculate size:
    int sampleSize = v1.size();
    //points:
    //make array of points
    vector<Point*> points(sampleSize);
    //create points and put them in the array
    for (int k = 0; k < sampleSize; k++) {
        Point p(v1[k], v2[k]);
        points.push_back(&p);
    }
    //calculate linear_reg with the points and size
    newPair.lin_reg = linear_reg2(&v1[0],&v2[0], sampleSize);
    //find threshold:
    //init max threshold to 0
    float maxDev = 0;
    //calculate deviation for every point from the linear_reg line and save the biggest deviation
    for (int k = 0; k < sampleSize; k++) {
        float deviation = dev(Point(v1[k],v2[k]), newPair.lin_reg);
        if (maxDev < deviation)
            maxDev = deviation;
    }
    //max_dev *=1.1 for precision
    newPair.threshold = maxDev * 1.2;
    return newPair;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //get number of features
    vector<string> keys = ts.getAllKeys();
    int n = (int) keys.size();
    map<string, vector<float>> table = ts.getTable();
    //for i = 1 to number of features
    for (int i = 0; i < n; i++) {
        //init m = 0 , col = -1
        float maxCorrelation = 0;
        int column = -1;
        //inner loop for i+1 to n
        for (int j = i + 1; j < n; j++) {
            //calculate pearson between features i and j
            vector<float> featureIValues = table[keys[i]];
            vector<float> featureJValues = table[keys[j]];
            int sampleSize = (int) featureIValues.size();
            float correlation = pearson(&featureIValues[0], &featureJValues[0], sampleSize);
            //cout << "pearson for:" << keys[i] << " " << keys[j] <<  " is:" << correlation << endl;
            //if pearson feature i and feature j > m
            if (maxCorrelation < correlation) {
                //then m = pearson and col = j meaning we found a new max correlation
                maxCorrelation = correlation;
                column = j;
            }
        }
        if (column != -1) { // found a correlation between feature i and feature j
            if (abs(maxCorrelation) > minAllowedCorrelation) { //if the correlation between: i,j is strong enough
                //save them in the struct if they proceed the threshold
                correlatedFeatures correlation = correlatedFeaturesCreator(keys[i], keys[column], maxCorrelation,
                                                                           table[keys[i]], table[keys[column]]);
                this->normalModel.push_back(correlation);
            }
        }
    }
}
/*now that we have the vector of correlated pairs and their max allowed deviation calculated
  we are ready for detect */


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> reports;
    map<string, vector<float>> table = ts.getTable();
    // checking the number of lines in the table
    int numOfLines = ts.getNumberOfLines();
    if (numOfLines != 0) {
        // going over all the lines in the table
        for (auto const &correlation: this->normalModel) {
            vector<float> f1 = table[correlation.feature1];
            vector<float> f2 = table[correlation.feature2];
            // for each line going over all the correlation columns
            for (int i = 0; i < numOfLines; i++) {
                Point p(f1[i], f2[i]);
                float numDev = dev(p, correlation.lin_reg);
                if (numDev > correlation.threshold) {
                    string description = correlation.feature1 + "-" + correlation.feature2;
                    int timeStep = i+1;
                    cout<< "deviation detected: " << numDev << " " << description << " in time: " <<timeStep << endl;
                    AnomalyReport anomalyReport(description, timeStep);
                    reports.push_back(anomalyReport);
                }
            }
        }
    }
    return reports;
}


vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return this->normalModel;
}




