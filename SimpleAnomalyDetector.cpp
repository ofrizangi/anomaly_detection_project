#include "TimeSeries.h"
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"

using namespace std;


SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

//float * fromVecToArr(vector<float> s , int size){
//    //float * arr = new array<float>();
//    for (int i = 0; i < size; i++) {
//        arr[i] = s[i];
//    }
//    return arr;
//}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //get number of features
    vector<string> keys = ts.getAllKeys();
    int n = keys.size();
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
            // float * x = featureIValues;
            int sampleSize = featureIValues.size();

            float correlate = pearson(featureIValues, featureJValues, sampleSize);
            //if pearson feature i and feature j > m
            if (maxCorrelation < correlate) {
                //then m = pearson and col = j meaning we found a new max correlation
                maxCorrelation = correlate;
                column = j;
            }
        }
        //if col != -1 then we found a correlation between feature i and feature j
        if (column != -1) {
            //save them in the struct(use pearson and linear_reg) if they proceed the threshold
            correlatedFeatures correlation;
            //get the info for the struct
            correlation.feature1 = keys[i];
            correlation.feature2 = keys[column];
            correlation.correlation = maxCorrelation;
            //to get linear reg we need to calculate the points and size
            //calculate size:
            int sampleSize = table[keys[i]].size();
            //points:
            //get the float vectors to make the points from
            vector<float> feature1Values = table[keys[i]];
            vector<float> feature2Values = table[keys[column]];
            //make array of points
            Point *points;
            //create points and put them in the array
            for (int k = 0; k < sampleSize; k++) {
                Point *p = new Point(feature1Values[k], feature2Values[k]);
                points[k] = *p;
            }
            //calculate linear_reg with the points and size
            correlation.lin_reg = linear_reg(&points, sampleSize);
            //find threshold:
            //init max threshold to 0
            float maxDev = 0;
            //calculate deviation for every point from the linear_reg line and save the biggest deviation
            for (int k = 0; k < sampleSize; k++) {
                float d = dev(points[k], correlation.lin_reg);
                if (maxDev < d)
                    maxDev = d;
            }
            //max_dev *=1.1 for precision
            correlation.threshold = maxDev * 1.1;
            this->normalModel.push_back(correlation);
        }
    }

}


/*now that we have the vector of correlated pairs and their max allowed deviation calculated
  we are ready for detect */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> reports();
    map<string, vector<float>> table = ts.getTable();
    vector <string> keys = ts.getAllKeys();

    for(auto correlation : this->normalModel){

    }
    // the number of lines in the table
    int numOfLines;

    for(int i=0; i<numOfLines; i++){

    }



}
//    //vector<AnomalyReport> reports =  new vector<AnomalyReport>();
//    vector<float>::iterator it;


//vector<correlatedFeatures>::iterator it;

//for(it = this.normalModel.begin; )

//for each line/timestamp in the time series
//for each pair of correlated features from learn normal(we need to save the vector,maybe as instance var?)
//take the data for feature 1 and feature 2 and make a point
//calculate the dev of the point from the linear_reg line of the pair(the line is saved in the struct)
//if the dev>max_dev then create anomaly report with the names of the features and time
//add the new report to the vector
//end of for each loop(both)
//return the vector with the reports
//}

vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return this->normalModel;
}




