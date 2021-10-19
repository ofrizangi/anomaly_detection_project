
#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;

bool wrong(float val, float expected) {
    return val < expected - 0.001 || val > expected + 0.001;
}

// this is a simple test to put you on the right track
int main() {

    float X[] = {2, 4, 6, 8, 10};
    float Y[] = {12, 11, 8, 3, 1};
    std::cout << "var X is " << var(X, 5) << "\n"; //8
    std::cout << "var Y is " << var(Y, 5) << "\n"; //18.8
    std::cout << "cov X Y is " << cov(X, Y, 5) << "\n"; //-12
    std::cout << "correlation X Y is " << pearson(X, Y, 5) << "\n"; //-0.9785
    float f1 = 1.567;
    float f2 = 2.789;

    Point *p1[5];
    for (int i = 0; i < 5; i++)
        p1[i] = new Point(X[i], Y[i]);

    Line l1 = linear_reg(p1, 5);
    cout << l1.a << " " << l1.b << endl;
    cout << dev(Point(3,2), l1) << endl;


    const int N = 10;
    float x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float y[] = {2.1, 4.2, 6.1, 8.1, 10.3, 12.2, 14.4, 16.1, 18.2, 20.3};

    Point *ps[N];
    for (int i = 0; i < N; i++)
        ps[i] = new Point(x[i], y[i]);

    Line l = linear_reg(ps, N);
    cout << l.a << " " << l.b << endl;
    Point p(4, 8);

    float v[] = {var(x, N), cov(x, y, N), pearson(x, y, N), l.a, l.b, l.f(4), dev(p, l)};
    float e[] = {8.25, 16.63, 0.999, 2.015, 0.113, 8.176, 0.176};

    cout << var(x, N) << endl;
    cout << cov(x, y, N) << endl;
    cout << pearson(x, y, N) << endl;
    cout << l.f(4) << endl;
    cout << dev(p, l) << endl;


    for (int i = 0; i < 7; i++)
        if (wrong(v[i], e[i]))
            cout << "error for check " << i << " (-14)" << endl;


    for (int i = 0; i < N; i++)
        delete ps[i];

    cout << "done" << endl;
    return 0;
}

