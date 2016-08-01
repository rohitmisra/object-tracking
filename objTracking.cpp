
#include <sstream>
#include <string>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <time.h>
#include "OpenNI.h"
#include "functions.h"
using namespace cv;
using namespace internalFunctions;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 159;
int H_MAX = 227;
int S_MIN = 86;
int S_MAX = 243;
int V_MIN = 56;
int V_MAX = 255;

int H_MIN2 = 49;
int H_MAX2 = 105;
int S_MIN2 = 51;
int S_MAX2 = 148;
int V_MIN2 = 0;
int V_MAX2 = 157;

int count1 = 0;
int count2 = 0;

time_t time1 [10000];
time_t time2 [10000];

int tracex1[90000];
int tracey1[90000];
int tracex2[90000];
int tracey2[90000];

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image1";
const string windowName4 = "Thresholded Image2";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Object1";
const string trackbarWindowName2 = "Object2";

void on_trackbar( int, void* ){

}



void createTrackbars(){
	//create window for trackbars


    namedWindow(trackbarWindowName,0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf( TrackbarName, "H_MIN", H_MIN);
	sprintf( TrackbarName, "H_MAX", H_MAX);
	sprintf( TrackbarName, "S_MIN", S_MIN);
	sprintf( TrackbarName, "S_MAX", S_MAX);
	sprintf( TrackbarName, "V_MIN", V_MIN);
	sprintf( TrackbarName, "V_MAX", V_MAX);
	
    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, 255, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, 255, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, 255, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, 255, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, 255, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, 255, on_trackbar );

}


void createTrackbars2(){
	//create window for trackbars

    namedWindow(trackbarWindowName2,0);
	//create memory to store trackbar name on window
	char TrackbarName2[50];
	sprintf( TrackbarName2, "H_MIN", H_MIN2);
	sprintf( TrackbarName2, "H_MAX", H_MAX2);
	sprintf( TrackbarName2, "S_MIN", S_MIN2);
	sprintf( TrackbarName2, "S_MAX", S_MAX2);
	sprintf( TrackbarName2, "V_MIN", V_MIN2);
	sprintf( TrackbarName2, "V_MAX", V_MAX2);
	    
    createTrackbar( "H_MIN", trackbarWindowName2, &H_MIN2, 255, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName2, &H_MAX2, 255, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName2, &S_MIN2, 255, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName2, &S_MAX2, 255, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName2, &V_MIN2, 255, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName2, &V_MAX2, 255, on_trackbar );


}
void drawObject(int x, int y,Mat &frame){
	
	tracex1[count1] = x;
	tracey1[count1] = y;
	
	count1++;

	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    if(y-25>0)
    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
    if(x-25>0)
    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);

}


void drawObject2(int x, int y,Mat &frame){
	
	tracex2[count2] = x;
	tracey2[count2] = y;
	time2[count2] = time(0);
	count2++;

	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    if(y-25>0)
    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
    if(x-25>0)
    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);

}


void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				}else objectFound = false;


			}
			
			if(objectFound ==true){
				
				time1[count1] = time(0);
				
				if(std::abs(x-tracex1[count1-1])<10){
					x=tracex1[count1-1];
				}
				if(std::abs(y-tracey1[count1-1])<10){
					y=tracey1[count1-1];
				}
				drawObject(x,y,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

void trackFilteredObject2(int &x2, int &y2, Mat threshold, Mat &cameraFeed){

	Mat temp;
	threshold.copyTo(temp);
	
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
       
        if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x2 = moment.m10/area;
					y2= moment.m01/area;
					objectFound = true;
					refArea = area;
				}else objectFound = false;


			}
	
			if(objectFound ==true){
				
				time2[count2] = time(0);
				
				if(std::abs(x2-tracex2[count2-1])<10){
					x2=tracex2[count2-1];
				}
				if(std::abs(x2-tracex2[count2-1])<10){
					y2=tracey2[count2-1];
				}
				
				drawObject2(x2,y2,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}





int main(int argc, char* argv[])
{
	//some boolean variables for different functionality within this
	//program
    bool trackObjects = true;
    bool useMorphOps = true;
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	Mat threshold2;
	//x and y values for the location of the object
	int x=0, y=0;
	int x2=0, y2=0;
	//create slider bars for HSV filtering
	createTrackbars();
	createTrackbars2();
	
	
	//VideoCapture capture("C:\\Users\\rohit.misra\\Downloads\\1.avi"); 
	//video capture object to acquire webcam feed
	VideoCapture capture;
	capture.open(2);
	//open capture object at location zero (default location for webcam)
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	int xprev=0, yprev=0;
	int x2prev=0, y2prev=0;

	while(1){
		
		 
		capture.read(cameraFeed);
		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
		threshold = morphOps(threshold);
		trackFilteredObject(x,y,threshold,cameraFeed);

		inRange(HSV,Scalar(H_MIN2,S_MIN2,V_MIN2),Scalar(H_MAX2,S_MAX2,V_MAX2),threshold2);
		threshold2 = morphOps(threshold2);
		trackFilteredObject2(x2,y2,threshold2,cameraFeed);
		
		
		
		Vec4f line; 
		Point2i pointDraw; 
		int* pointx = new int [20];
		int* pointy = new int [20];
		float x1new;
		float y1new;
		vector<Point2i> vecDraw; 
		if(count1>20){
			for(int i = count1; i>count1-20; i --){
				pointDraw.x=tracex1[i]; 
				pointDraw.y=tracey1[i]; 
				vecDraw.insert(vecDraw.end(),pointDraw); 
				
			}
			
			vecDraw[0]= vecDraw[1];
			fitLine(vecDraw,line,CV_DIST_L2,0,0.01,0.01);

			
			x1new = x + (x-((*((cv::Matx<float,4,1>*)(&(line)))).val)[2])*200;
			y1new = y + (y-((*((cv::Matx<float,4,1>*)(&(line)))).val)[3])*200;
			cv::line(cameraFeed,Point(x,y),Point(x1new,y1new),Scalar(170,1,20),1,8,0);
			
		}


		

		Vec4f line2; 
		Point2i pointDraw2; 
		int* pointx2 = new int [20];
		int* pointy2 = new int [20];
		vector<Point2i> vecDraw2; 
		float x2new;
		float y2new;
		if(count2>20){
			for(int i = count2; i>count2-20; i --){
				pointDraw2.x=tracex2[i]; 
				pointDraw2.y=tracey2[i]; 
				vecDraw2.insert(vecDraw2.end(),pointDraw2); 
				
			}
			
			vecDraw2[0]= vecDraw2[1];
			fitLine(vecDraw2,line2,CV_DIST_L2,0,0.01,0.01);

			
			x2new = x2 + (x2-((*((cv::Matx<float,4,1>*)(&(line2)))).val)[2])*200;
			y2new = y2 + (y2-((*((cv::Matx<float,4,1>*)(&(line2)))).val)[3])*200;
			cv::line(cameraFeed,Point(x2,y2),Point(x2new,y2new),Scalar(160,2,20),1,8,0);
			
		}


		

		
		

		double velocity1 = 0;
		if(count1>25){
			float first = (tracex1[count1-1]-tracex1[count1-20])*(tracex1[count1-1]-tracex1[count1-20]);
			float second =(tracey1[count1-1]-tracey1[count1-20])*(tracey1[count1-1]-tracey1[count1-20]);
			velocity1 =  sqrt(first+second)/((time1[count1-1]-time1[count1-20]));

			}

		double velocity2 = 0;
		if(count2>25){
			float first = (tracex2[count2-1]-tracex2[count2-20])*(tracex2[count2-1]-tracex2[count2-20]);
			float second =(tracey2[count2-1]-tracey2[count2-20])*(tracey2[count2-1]-tracey2[count2-20]);
			velocity2 =  sqrt(first+second)/((time2[count2-1]-time2[count2-20]));

		
		}
		
		if(count1>20 && count2>20){
			Point2f intersctionPoint; 
			if(intersection(Point(x,y),Point(x1new,y1new),Point(x2,y2),Point(x2new,y2new),intersctionPoint)==true){
				
				double time1 = distance(intersctionPoint.x,intersctionPoint.y,x,y)/std::ceil(velocity1+2);
				double time2 = distance(intersctionPoint.x,intersctionPoint.y,x2,y2)/std::ceil(velocity2+2);
				//std::cout<<velocity1<<" vs "<<velocity2<<"\n";
				std::cout<<"time to intersection:" << abs(time1)<<" vs "<< abs(time2)<<"\n";
				
				if(std::abs(time1-time2)>2){
					circle(cameraFeed,intersctionPoint,20,Scalar(0,0,255),2);
				}else{
					circle(cameraFeed,intersctionPoint,20,Scalar(0,255,255),2);
				}
			}
		}




		imshow(windowName2,threshold);
		imshow(windowName4,threshold2);
		imshow(windowName,cameraFeed);
		imshow(windowName1,HSV);
		

		
		waitKey(10);
	}

	
	return 0;
}
