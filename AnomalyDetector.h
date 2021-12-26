

#include "timeseries.h"
#ifndef ANOMALYDETECTOR_H
#define ANOMALYDETECTOR_H
class AnomalyReport{
public:
    string description;
    long timeStep;
    AnomalyReport(string description, long timeStep) : description(description){this->timeStep = timeStep;}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};

#endif