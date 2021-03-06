

#include "timeseries.h"
#ifndef ANOMALYDETECTOR_H
#define ANOMALYDETECTOR_H
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(const string description,const long timeStep) : description(description) , timeStep(timeStep){}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};

#endif