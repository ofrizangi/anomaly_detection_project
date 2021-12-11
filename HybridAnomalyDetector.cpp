//Ofri Zangi 207488305
//Ben Plosk 208290833

#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() = default;

/**
* Calls the function CorrelatedFeaturesCreator with the object function we want to set the correlated feature by
*/
void HybridAnomalyDetector::callCorrelatedFeaturesCreator(float maxCorrelation, vector<string> keys,
                                                          map<string, vector<float>> table, int i, int column) {
    if (abs(maxCorrelation) >= 0.9){
        correlatedFeatures correlation = correlatedFeaturesCreator(keys[i], keys[column], maxCorrelation,
                                                                   table[keys[i]], table[keys[column]],
                                                                   Regression());
        this->normalModel.push_back(correlation);
    }
    else if (abs(maxCorrelation) >= 0.5){
        correlatedFeatures correlation = correlatedFeaturesCreator(keys[i], keys[column], maxCorrelation,
                                                                   table[keys[i]], table[keys[column]],
                                                                   CircleRadius());
        this->normalModel.push_back(correlation);
    }
}

/**
* Calls the function detect by with the object function we want to detect with
*/
bool HybridAnomalyDetector::callDetectBy(correlatedFeatures correlation, Point p) {
    if (correlation.min_circle.radius == 0)
        return IfDetectBy(detectByRegression(), correlation, p);
    return IfDetectBy(detectByCircleRadius(), correlation, p);
}

HybridAnomalyDetector::~HybridAnomalyDetector() = default;