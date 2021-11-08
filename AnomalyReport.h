

#ifndef EX1_ANOMALYREPORT_H
#define EX1_ANOMALYREPORT_H
#include "TimeSeries.h"
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
#endif //EX1_ANOMALYREPORT_H
