#include <iostream>
#include "anomaly_detection_util.h"

/**
 * Returns the variance of a ......
 *
 * @param x a pointer to an array of numbers
 * @param size the size of the array
 * @return the variance ............
 */
float var(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + x[i];
    }
    float u = (1 / (float) size) * sum;
    sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + (x[i] - u) * (x[i] - u);
    }
    return (1 / (float) size) * sum;
}

int main() {
    float *x;
    float ar[5] = {1, 2, 3, 4, 5};
    x = ar;
    std::cout << var(x, 5) << std::endl;
    return 0;
}
