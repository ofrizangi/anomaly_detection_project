//Ofri Zangi 207488305
//Ben Plosk 208290833
#include "minCircle.h"
//a simple method to calc distance between two points on a 2-D plane
float distance(const Point& p1,const Point& p2) {
    float dx = pow( (p1.x - p2.x) ,2 );
    float dy = pow( (p1.y - p2.y) ,2 );
    return sqrt( (dx+dy) );
}
//a helper method for circle validation that tells if a point is inside the given circle
bool isInsideCircle(const Circle& c,const Point& p)
{
    if(distance(c.center, p) <= c.radius)
        return true;
    return false;
}
//a method to tell if a circle contains all the points
bool isValidCircle(const Circle& c,Point** points,int size)
{
    for (int i=0;i<size;i++)
        if (!isInsideCircle(c, *points[i]))
            return false;
    return true;
}
//creates a minimum circle that contains 2 given points using simple geometry
Circle circleFrom2Points(const Point& p1 ,const Point& p2 ) {
    float centerX = (p1.x + p2.x) / 2 ;
    float centerY = (p1.y + p2.y) / 2 ;
    Point center = Point(centerX,centerY);
    float r = distance(p1,center);
    return {center,r};
}
//a helper method to create a minimum circle for 3 points using geometrical formula
Point circleFrom3PointsCenter(float p2X,float p2Y,float p3X,float p3Y) {
    float delta2 = ( pow(p2X,2)+ pow(p2Y,2) );
    float delta3 = ( pow(p3X,2) + pow(p3Y,2) );
    float D = ( (p2X*p3Y) - (p2Y*p3X) );
    float centerX = ( ((p3Y*delta2) - (p2Y*delta3)) / (2*D)) ;
    float centerY = ( ((p2X*delta3) - (p3X*delta2)) / (2*D)) ;
    return {centerX,centerY};
}
//creates a minimum circle that contains 3 given points using geometric formula
Circle circleFrom3Points(const Point& p1,const Point& p2,const Point& p3) {
    Point center = circleFrom3PointsCenter(p2.x - p1.x,p2.y - p1.y,p3.x - p1.x,p3.y - p1.y);
    center.x += p1.x;
    center.y += p1.y;
    float r = distance(center,p1);
    return {center,r};
}
//helper method for the welzl algorithm, it's the returned value on the stopping condition
//it uses the methods for 2,3 point circles
Circle trivialCircle(Point** points,int size) {

    if (size == 1) {
        return {*points[0], 0};
    }
    else if (size == 2) {
        return circleFrom2Points(*points[0], *points[1]);
    }
    else if (size == 3) {
        //check if it can be achieved by a circle created by 2 points of the 3
        for (int i = 0; i <= 1; i++) {
            for (int j = i + 1; j <= 2; j++) {
                Circle c = circleFrom2Points(*points[i], *points[j]);
                //check if the third point is inside the circle made by the other 2
                if (isValidCircle(c, points,size))
                    return c;
            }
        }
        //if not create a circle from all the 3 points
        return circleFrom3Points(*points[0],*points[1],*points[2]);
    }
}
//a helper method to swap pointers in the points array
void swap(Point** p1,Point** p2){
    Point* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//the welzl algorithm for minimum enclosing circle
Circle welzlAlgo(Point** P,Point** R, int sizeOfP,int elementsInR) {
    //stopping condition
    if (sizeOfP == 0 || elementsInR == 3  ) {
        return trivialCircle(R,elementsInR);
    }
    //pick a random point p
    int i = rand() % sizeOfP;
    Point p = *P[i];
    swap(&P[i],&P[sizeOfP-1]);
    //recursively calculate the MES without the chosen point
    Circle withoutPoint = welzlAlgo(P, R, sizeOfP - 1,elementsInR);
    //if it also contains p it is the MES
    if(isInsideCircle(withoutPoint,p))
        return withoutPoint;
    //if it didn't it means p is supposed to be on the boundary of the MES so we add it to R
    R[elementsInR] = &p;
    //then recursively call the method with a bigger R
    return welzlAlgo(P, R, sizeOfP - 1,elementsInR+1);
}
//the MES method that calls the welzl algorithm
Circle findMinCircle(Point** points,size_t size) {
    //init R
     Point* a[3] = {0,0,0};
     Point** R = &a[0];
     //call welzl
    return welzlAlgo(points, R, size, 0);
}