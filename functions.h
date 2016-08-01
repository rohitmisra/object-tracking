#ifndef INTERNAL_FUNCTIONS_H_
#define INTERNAL_FUNCTIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <time.h>
using namespace cv;
namespace internalFunctions{
	Mat morphOps(Mat thresh){
	

	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);


	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
	
	return thresh;

}
	unsigned int root(unsigned int x){
    unsigned int a,b;
    b     = x;
    a = x = 0x3f;
    x     = b/x;
    a = x = (x+a)>>1;
    x     = b/x;
    a = x = (x+a)>>1;
    x     = b/x;
    x     = (x+a)>>1;
    return(x);  
}


string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,
                      Point2f &r){
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < /*EPS*/1e-8)
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
}


double distance(float x11, float y11, float x22, float y22){
	float first = (x11-x22)*(x11-x22);
	float second =(y11-y22)*(y11-y22);
	return sqrt(first+second);
}

}


#endif //INTERNAL_FUNCTIONS_H_