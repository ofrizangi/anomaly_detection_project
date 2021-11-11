//Ofri Zangi 207488305
//Ben Plosk


#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"

#include<algorithm>
struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector: public TimeSeriesAnomalyDetector{
private:
    vector<correlatedFeatures> normalModel;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};

