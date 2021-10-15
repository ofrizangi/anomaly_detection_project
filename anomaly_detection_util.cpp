#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>

//this is the source file for anomaly_detection_util library
//it's the ex1 for 89210 project
// returns the variance of X and Y
//helper method to calculate the sum of variables
float sumMembers(float* x, int size) {
    float sum = 0;
    //loop through floats and sum them
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum;
}

//helper method to calculate the sum of squares
float sumSquares(float* x, int size) {
    float sum = 0;
    //loop through floats and sum the squares of them
    for (int i = 0; i < size; i++) {
        sum += pow(x[i], 2);
    }
    return sum;
}

// returns the variance of X and Y
float var(float* x, int size) {
    /*add check if any of floats in x are negative?
    add check for valid size: not 0 or negative etc */

    //first some calculation preparations to simplify the formula
    float sum = sumMembers(x, size);
    float squareSum = sumSquares(x, size);
    float ro = sum / size ;
    //finally calculate variance using the formula
    float var = (squareSum / size)  - pow(ro, 2);
    return var;
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size);


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size);



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
    std::cout << avg(x, 5);


}//end of the library
