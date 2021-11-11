//Ofri Zangi 207488305
//Ben Plosk

#include "anomaly_detection_util.h"
#include <cmath>
#include <stdexcept>

/**
* Helper method to calculate the sum of variables.
* @param x a pointer to an array
* @param size the size of the array
*/
float sumMembers(float *x, int size) {
    float sum = 0;
    //loop through floats and sum them
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum;
}

/**
* Helper method to calculate the sum of squares.
* @param x a pointer to an array
* @param size the size of the array
*/
float sumSquares(float *x, int size) {
    float sum = 0;
    //loop through floats and sum the squares of them
    for (int i = 0; i < size; i++) {
        sum += (float) pow(x[i], 2);
    }
    return sum;
}

/**
* Helper method to calculate the average of the numbers n the array.
* @param x a pointer to an array
* @param size the size of the array
*/
float avg(float *x, int size) {
    float sum = sumMembers(x, size);
    return sum / (float) size;
}

/**
* Returns the variance of X
* @param x a pointer to an array
* @param size the size of the array
*/
float var(float *x, int size) {
    //check if size and x are valid
    if (size < 1)
        throw std::invalid_argument("size must be positive");
    if (x == nullptr)
        throw std::invalid_argument("null pointer passed");
    //first some calculation preparations to simplify the formula
    float squareSum = sumSquares(x, size);
    float ro = avg(x, size);
    //finally calculate variance using the formula
    float var = (squareSum / (float) size) - (float) pow(ro, 2);
    return var;
}

/**
* returns the covariance of X and Y
* @param x a pointer to an array
* @param y a pointer to an array
* @param size the size of the array
*/
float cov(float *x, float *y, int size) {
    //check if size and x are valid
    if (size < 1)
        throw std::invalid_argument("size must be positive");
    if (x == nullptr)
        throw std::invalid_argument("null pointer passed");
    //calculate avg to use later in the loop
    float ruX = avg(x, size);
    float ruY = avg(y, size);
    //init sum
    float sum = 0;
    //sum the product of (Xi - ruX) * (Yi - ruY) like the formula said
    for (int i = 0; i < size; i++) {
        float deltaX = x[i] - ruX;
        float deltaY = y[i] - ruY;
        sum += (deltaX * deltaY);
    }
    //cov is the sum divided by the population size
    float cov = sum / (float) size;
    //return the covariance
    return cov;
}

/**
* returns the Pearson correlation coefficient of X and Y
* @param x a pointer to an array
* @param y a pointer to an array
* @param size the size of the array
*/
float pearson(float *x, float *y, int size) {
    //check if size and x are valid
    if (size < 1)
        throw std::invalid_argument("size must be positive");
    if (x == nullptr)
        throw std::invalid_argument("null pointer passed");
    //calculate covariance
    float covariance = cov(x, y, size);
    //calculate the deviation using variance
    float varX = var(x, size);
    float varY = var(y, size);
    float deviation = sqrtf((varX * varY));
    //calculate pearson correlation
    float correlation = covariance / deviation;
    //return the pearson correlation
    return correlation;
}

/**
* performs a linear regression and return the line equation
* @param points a pointer to an array of points
* @param size the size of the array
*/
Line linear_reg(Point **points, int size) {
    //check if size and points are valid
    if (size < 1)
        throw std::invalid_argument("size must be positive");
    if (points == nullptr)
        throw std::invalid_argument("null pointer passed");
    float x[sizeof(points)/sizeof(Point*)],y[sizeof(points)/sizeof(Point*)];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * avg(x, size);
    Line l(a, b);
    return l;
}

/**
* returns the deviation between a point and the line equation of the points int the array
* @param p the point we want its' deviation from the line
* @param points a pointer to an array of points
* @param size the size of the array
*/
float dev(Point p, Point **points, int size) {
    //check if size and points are valid
    if (size < 1)
        throw std::invalid_argument("size must be positive");
    if (points == nullptr)
        throw std::invalid_argument("null pointer passed");
    Line l = linear_reg(points, size);
    float yLinePoint = l.f(p.x);
    return fabsf(yLinePoint - p.y);
}

/**
* returns the deviation between a point and a line
* @param p the point we want its' deviation from the line
* @param points a pointer to an array of points
*/
float dev(Point p, Line l) {
    float yLinePoint = l.f(p.x);
    return fabsf(yLinePoint - p.y);
}

Line linear_reg2(float* x,float* y, int size) {
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * avg(x, size);
    Line l(a, b);
    return l;
}