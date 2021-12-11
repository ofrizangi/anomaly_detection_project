//Ofri Zangi 207488305
//Ben Plosk 208290833

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {

    struct CircleRadius{
    public:
        float operator()(correlatedFeatures * newPair, Point ** points ,int sampleSize) const{
            newPair->min_circle = findMinCircle(points, sampleSize);
            return newPair->min_circle.radius;
        }
    };

    struct detectByCircleRadius{
    public:
        bool operator() (const correlatedFeatures & newPair, Point p) {
            if (!isInsideCircle(newPair.min_circle, p))
                return true;
            return false;
        }
    };

public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void callCorrelatedFeaturesCreator(float maxCorrelation, vector<string> keys, map<string, vector<float>> table, int i,
                                               int column);
    virtual bool callDetectBy(correlatedFeatures correlation, Point p);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
