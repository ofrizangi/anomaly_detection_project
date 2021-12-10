#include "minCircle.h"
float distance(const Point& p1,const Point& p2) {
    float dx = pow( (p1.x - p2.x) ,2 );
    float dy = pow( (p1.y - p2.y) ,2 );
    return sqrt( (dx+dy) );
}
bool isInsideCircle(const Circle& c,const Point& p)
{
    if(distance(c.center, p) <= c.radius)
        return true;
    return false;
}

bool isValidCircle(const Circle& c,const vector<Point>& points)
{
    for (Point p : points)
        if (isInsideCircle(c, p))
            return false;
    return true;
}

Circle circleFrom2Points(const Point& p1 ,const Point& p2 ) {
    float centerX = (p1.x + p2.x) / 2 ;
    float centerY = (p1.y + p2.y) / 2 ;
    Point center = Point(centerX,centerY);
    float r = distance(p1,center);
    return {center,r};
}
Point circleFrom3PointsCenter(float p2X,float p2Y,float p3X,float p3Y) {
    float delta2 = ( pow(p2X,2)+ pow(p2Y,2) );
    float delta3 = ( pow(p3X,2) + pow(p3Y,2) );
    float D = ( (p2X*p3Y) - (p2Y*p3X) );
    float centerX = ( ((p3Y*delta2) - (p2Y*delta3)) / (2*D)) ;
    float centerY = ( ((p2X*delta3) - (p3X*delta2)) / (2*D)) ;
    return {centerX,centerY};
}
Circle circleFrom3Points(const Point& p1,const Point& p2,const Point& p3) {
    Point center = circleFrom3PointsCenter(p2.x - p1.x,p2.y - p1.y,p3.x - p1.x,p3.y - p1.y);
    center.x += p1.x;
    center.y += p1.y;
    float r = distance(center,p1);
    return {center,r};
}

Circle trivialCircle(vector<Point>& points) {
    if (points.size() == 1) {
        return {points[0], 0};
    }
    else if (points.size() == 2) {
        return circleFrom2Points(points[0], points[1]);
    }
    else if (points.size() == 3) {
        for (int i = 0; i <= 1; i++) {
            for (int j = i + 1; j <= 2; j++) {
                Circle c = circleFrom2Points(points[i], points[j]);
                if (isValidCircle(c, points))
                    return c;
            }
        }
        return circleFrom3Points(points[0],points[1],points[2]);
    }
}
Circle welzlAlgo(vector<Point>& P,vector<Point> R, int n) {
    if ( R.size() == 3 || n == 0 ) {
        return trivialCircle(R);
    }

    int i = rand() % n;
    Point p = P[i];
    swap(P[i],P[n-1]);

    Circle d = welzlAlgo(P, R, n - 1);
    if(isInsideCircle(d,p))
        return d;

    R.push_back(p);
    return welzlAlgo(P, R, n - 1);
}
Circle findMinCircle(Point** points,size_t size) {
    vector<Point> pointsVector ;
    for(int i=0;i<size;i++)
        pointsVector.push_back(*points[i]);
    return welzlAlgo(pointsVector,{},size);
}