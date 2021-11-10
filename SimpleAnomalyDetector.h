#include "AnomalyReport.h"
struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float correlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
private:
    vector<correlatedFeatures> normalModel;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};
