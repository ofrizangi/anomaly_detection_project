#include "TimeSeries.cpp"
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"

    vector<correlatedFeatures> normalModel;
    SimpleAnomalyDetector::SimpleAnomalyDetector(): this.normalModel = new vector<correlatedFeatures>() {};
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts){
        //get number of features
        vector<string> keys = ts.getAllKeys();
        int n = keys.size();
        //for i = 1 to number of features
        for(int i =0; i<n;i++) {
            //init m = 0 , col = -1
            float maxCorrelation = 0;
            int column = -1;
            //inner loop for i+1 to n
            for(int j=i+1;j<n;j++) {
                //calculate pearson between features i and j
                vector<float> featureIValues = ts.table.find(keys[i]);
                vector<float> featureJValues = ts.table.find(keys[j]);
                int sampleSize = featureIValues.size();
                float pearson = pearson(featureIValues,featureJValues,sampleSize);
                //if pearson feature i and feature j > m
                if(maxCorrelation<pearson) {
                    //then m = pearson and col = j meaning we found a new max correlation
                    maxCorrelation = pearson;
                    column = j;
                }
            }  //finished with inner loop
            //if col != -1 then we found a correlation between feature i and feature j
            if(column != -1) {
                //still need to decide how to calculate threshold!!(wait for answer in forum)
                //save them in the struct(use pearson and linear_reg) if they proceed the threshold
                correlatedFeatures correlation;
                //get the info for the struct
                correlation.feature1 = keys[i];
                correlation.feature2 = keys[column];
                correlation.correlation = maxCorrelation;
                //to get linear reg we need to calculate the points and size
                //calculate size:
                int sampleSize = ts.table.find(keys[i]).size();
                //points:
                //get the float vectors to make the points from
                vector<float> feature1Values = ts.table.find(keys[i]);
                vector<float> feature2Values = ts.table.find(keys[column]);
                //make array of points
                Point points[sampleSize];
                //create points and put them in the array
                for(int k=0;k<sampleSize;k++) {
                    point p = new Point(feature1Values[k],feature2Values[k]);
                    points[k]=p;
                }
                //calculate linear_reg with the points and size
                correlation.lin_reg = linear_reg(points,sampleSize);
                //find threshold:
                //init max threshold to 0
                float maxDev = 0;
                //calculate deviation for every point from the linear_reg line and save the biggest deviation
                for(Point p: points) {
                    float dev = dev(p,correlation.lin_reg);
                    if(maxDev < dev)
                        maxdev = dev;
                }
                //max_dev *=1.1 for precision
                correlation.threshold = maxDev*1.1;
                this.NormalModel.push_back(correlation);
            }
        }//continue with outer loop to find all correlated features and add to the vector


    } // end of learNormal method
/*now that we have the vector of correlated pairs and their max allowed deviation calculated
  we are ready for detect */
    virtual vector<AnomalyReport> detect(const TimeSeries& ts) {
        //create an empty vector of anomaly report to return in the end
        //for each line/timestamp in the time series
        //for each pair of correlated features from learn normal(we need to save the vector,maybe as instance var?)
        //take the data for feature 1 and feature 2 and make a point
        //calculate the dev of the point from the linear_reg line of the pair(the line is saved in the struct)
        //if the dev>max_dev then create anomaly report with the names of the features and time
        //add the new report to the vector
        //end of for each loop(both)
        //return the vector with the reports
    }
    vector<correlatedFeatures> getNormalModel();
};
