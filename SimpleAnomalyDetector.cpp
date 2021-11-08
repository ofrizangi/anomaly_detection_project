
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
public:
    SimpleAnomalyDetector() {};
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts){
        //for i = 1 to number of features
        //m = 0 , col = -1
        //inner loop for i+1 to n
        //if pearson feature i and feature j > m
        //then m = pearson and col = j meaning we found a new max correlation
        //finished with inner loop
        //if col != -1 then we found a correlation between feature i and feature j
        //still need to decide how to calculate threshold
        //save them in the struct(use pearson and linear_reg) if they proceed the threshold
        //add them all to vector<correlated features>
        //continue with outer i loop to find all correlated features and add to the vector

        //now we have a vector with the pairs.
        //for each pair make a list of 2-D points (for each loop)
        //for each point, check the deviation from the linear reg line and save as max_dev
        //max_dev *=1.1 for precision
        //save for each pair of correlated features the max_dev(map?threshold?)
        //now that we have the vector of correlated pairs and their max allowed div we are ready for detect

    }
    virtual vector<AnomalyReport> detect(const TimeSeries& ts) {
        //create an empty vector of anomaly report to return in the end
        //for each line/timestep in the time series
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
