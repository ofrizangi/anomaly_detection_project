//Ofri Zangi 207488305
//Ben Plosk 208290833

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "minCircle.h"

#include<algorithm>

struct correlatedFeatures {
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle min_circle;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {

protected:
    float threshold;
    vector<correlatedFeatures> normalModel;

    struct Regression {
    public:
        float operator()(correlatedFeatures *newPair, Point **p, int sampleSize) const {
            float maxDev = 0;
            //calculate deviation for every point from the linear_reg line and save the biggest deviation
            for (int k = 0; k < sampleSize; k++) {
                float deviation = dev(*p[k], newPair->lin_reg);
                if (maxDev < deviation)
                    maxDev = deviation;
            }
            return maxDev;
        }
    };

    struct detectByRegression {
    public:
        bool operator()(const correlatedFeatures & newPair, Point p) const {
            float numDev = dev(p, newPair.lin_reg);
            if (numDev > newPair.threshold)
                return true;
            return false;
        }
    };

public:
    float getThreshold() {
        return this->threshold;
    }

    void setThreshold(float newThreshold) {
        if(newThreshold < 1 && newThreshold > 0)
            this->threshold = newThreshold;
        else
            cout << "please choose a value between 0 and 1." << endl;

    }

    /**
    * This function creates a correlated features struct
    */
    template<class Tfunc>
    correlatedFeatures correlatedFeaturesCreator(string feature1, string feature2, float correlation, vector<float> v1,
                                                 vector<float> v2, const Tfunc &f) {
        int sampleSize = v1.size();
        struct correlatedFeatures newPair =
                {feature1, feature2, correlation, linear_reg2(&v1[0], &v2[0], sampleSize), 0,
                 Circle(Point(0, 0), 0)};

        Point** points = new Point*[v1.size()];
        //create points and put them in the array
        for (int k = 0; k < sampleSize; k++) {
            Point* p = new Point(v1[k], v2[k]);
            points[k] = p;
        }
        float maxDev = f(&newPair, points, sampleSize);
        //max_dev *=1.1 for precision
        newPair.threshold = maxDev * (float) 1.1;
        newPair.min_circle.radius *= (float) 1.1;

        for (int k = 0; k < sampleSize; k++) {
            delete points[k];
        }
        return newPair;
    }

    /**
    * This function returns TRUE if there is a deviation of the point p
    */
    template<class Tfunc2>
    bool IfDeviationBy(Tfunc2 f, correlatedFeatures correlation, Point p) {
        if (f(correlation, p)) {
            return true;
        }
        return false;
    }

    /**
    * Calls the function detect by with the object function we want to detect with
    */
    virtual bool callDetectBy(correlatedFeatures correlation, Point p);

    /**
    * Calls the function CorrelatedFeaturesCreator with the object function we want to set the correlated feature by
    */
    virtual void
    callCorrelatedFeaturesCreator(float maxCorrelation, vector<string> keys, map<string, vector<float>> table, int i,
                                  int column);

    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel();
};

