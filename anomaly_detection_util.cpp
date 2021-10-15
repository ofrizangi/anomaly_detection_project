#include "anomaly_detection_util.h"

//this is the source file for anomaly_detection_util library
//it's the ex1 for 89210 project
// returns the variance of X and Y
float var(float *x, int size);

// returns the covariance of X and Y
float cov(float *x, float *y, int size);


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size);


class Line {
public:
    float a, b;

    Line() : a(0), b(0) {}

    Line(float a, float b) : a(a), b(b) {}

    float f(float x) {
        return a * x + b;
    }
};

class Point {
public:
    float x, y;

    Point(float x, float y) : x(x), y(y) {}
};

/**
 * Calculates the average of an array.
 *
 * @param filename GIF File name to be loaded
 * @return Inited GIF Handler or NULL for error
 */
float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + x[i];
    }
    return sum / (float) size;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size) {

}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {

}

// returns the deviation between point p and the line
float dev(Point p, Line l) {

}

int main() {

    float *x;
    float t[] = {1, 2, 3, 4, 5};
    x = t;
    std::cout << avg(x, 5) << std::endl;


}//end of the library
