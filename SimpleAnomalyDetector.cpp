//Ofri Zangi 207488305
//Ben Plosk 208290833

#include <iostream>
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"

using namespace std;


/**
* Constructor.
*/
SimpleAnomalyDetector::SimpleAnomalyDetector() {threshold = 0.9;};

/**
* Destructor.
*/
SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;


/**
* Calls the function CorrelatedFeaturesCreator with the object function we want to set the correlated feature by
*/
void SimpleAnomalyDetector::callCorrelatedFeaturesCreator(float maxCorrelation, vector<string> keys,
                                                          map<string, vector<float>> table, int i, int column) {
    if (abs(maxCorrelation) >= this->threshold) {
        correlatedFeatures correlation = correlatedFeaturesCreator(keys[i], keys[column], maxCorrelation,
                                                                   table[keys[i]], table[keys[column]],
                                                                   Regression());
        this->normalModel.push_back(correlation);
    }
}

/**
* This function learns the data the is given to it by calculating a vector of correlated pairs,
* and their max allowed deviation.
*
* @param ts the data we want to learn
*/
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //get number of features
    vector<string> keys = ts.getAllKeys();
    int n = (int) keys.size();
    map<string, vector<float>> table = ts.getTable();
    //for i = 1 to number of features
    for (int i = 0; i < n; i++) {
        int column = -1;
        float maxCorrelation = 0;
        for (int j = i + 1; j < n; j++) {
            //calculate pearson between features i and j
            vector<float> featureIValues = table[keys[i]];
            vector<float> featureJValues = table[keys[j]];
            int sampleSize = (int) featureIValues.size();
            float correlation = pearson(&featureIValues[0], &featureJValues[0], sampleSize);
            //if pearson feature i and feature j > m
            if (maxCorrelation < correlation) {
                //then m = pearson and col = j meaning we found a new max correlation
                maxCorrelation = correlation;
                column = j;
            }
        }
        if (column != -1) { // found a correlation between feature i and feature j
            callCorrelatedFeaturesCreator(maxCorrelation, keys, table, i, column);
        }
    }
}

/**
* Calls the function detect by with the object function we want to detect with
*/
bool SimpleAnomalyDetector::callDetectBy(correlatedFeatures correlation, Point p) {
    return IfDeviationBy(detectByRegression(), correlation, p);
}

/**
* Detecting exceptions from the new data we got by the normal data we calculated in function learnNormal
*
* @param ts the data we want to detect
*/
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
                if (callDetectBy(correlation, p)){
                    string description = correlation.feature1 + "-" + correlation.feature2;
                    int timeStep = i + 1;
                    AnomalyReport anomalyReport(description, timeStep);
                    reports.push_back(anomalyReport);
                }
            }
        }
    }
    return reports;
}

/**
@return the vector of all the correlated features.
*/
vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return this->normalModel;
}
