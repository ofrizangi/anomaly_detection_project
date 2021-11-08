
#ifndef EX1_SIMPLEANOMALYDETECTOR_H
#define EX1_SIMPLEANOMALYDETECTOR_H
struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float correlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};
#endif //EX1_SIMPLEANOMALYDETECTOR_H
