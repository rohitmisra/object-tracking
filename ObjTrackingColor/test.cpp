////objectTrackingTutorial.cpp
//
////Written by  Kyle Hounslow 2013
//
////Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
////, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
////and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
////The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
////THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
////FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
////LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
////IN THE SOFTWARE.
//
//#include <sstream>
//#include <string>
//#include <iostream>
//#include <opencv\highgui.h>
//#include <opencv\cv.h>
//#include <time.h>
//using namespace cv;
////initial min and max HSV filter values.
////these will be changed using trackbars
//int H_MIN = 159;
//int H_MAX = 227;
//int S_MIN = 86;
//int S_MAX = 243;
//int V_MIN = 56;
//int V_MAX = 255;
//
//int H_MIN2 = 78;
//int H_MAX2 = 125;
//int S_MIN2 = 125;
//int S_MAX2 = 255;
//int V_MIN2 = 0;
//int V_MAX2 = 255;
//
//int count1 = 0;
//int count2 = 0;
//
//time_t time1 [10000];
//time_t time2 [10000];
//
//int tracex1[90000];
//int tracey1[90000];
//int tracex2[90000];
//int tracey2[90000];
//
////default capture width and height
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 480;
////max number of objects to be detected in frame
//const int MAX_NUM_OBJECTS=50;
////minimum and maximum object area
//const int MIN_OBJECT_AREA = 20*20;
//const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
////names that will appear at the top of each window
//const string windowName = "Original Image";
//const string windowName1 = "HSV Image";
//const string windowName2 = "Thresholded Image1";
//const string windowName4 = "Thresholded Image2";
//const string windowName3 = "After Morphological Operations";
//const string trackbarWindowName = "Object1";
//const string trackbarWindowName2 = "Object2";
//void on_trackbar( int, void* )
//{//This function gets called whenever a
//	// trackbar position is changed
//
//
//
//
//
//}
//
//
//unsigned int root(unsigned int x){
//    unsigned int a,b;
//    b     = x;
//    a = x = 0x3f;
//    x     = b/x;
//    a = x = (x+a)>>1;
//    x     = b/x;
//    a = x = (x+a)>>1;
//    x     = b/x;
//    x     = (x+a)>>1;
//    return(x);  
//}
//
//
//string intToString(int number){
//
//
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}
//void createTrackbars(){
//	//create window for trackbars
//
//
//    namedWindow(trackbarWindowName,0);
//	//create memory to store trackbar name on window
//	char TrackbarName[50];
//	sprintf( TrackbarName, "H_MIN", H_MIN);
//	sprintf( TrackbarName, "H_MAX", H_MAX);
//	sprintf( TrackbarName, "S_MIN", S_MIN);
//	sprintf( TrackbarName, "S_MAX", S_MAX);
//	sprintf( TrackbarName, "V_MIN", V_MIN);
//	sprintf( TrackbarName, "V_MAX", V_MAX);
//	//create trackbars and insert them into window
//	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
//	//the max value the trackbar can move (eg. H_HIGH), 
//	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
//	//                                  ---->    ---->     ---->      
//    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, 255, on_trackbar );
//    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, 255, on_trackbar );
//    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, 255, on_trackbar );
//    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, 255, on_trackbar );
//    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, 255, on_trackbar );
//    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, 255, on_trackbar );
//
//
//}
//
//
//void createTrackbars2(){
//	//create window for trackbars
//
//
//    namedWindow(trackbarWindowName2,0);
//	//create memory to store trackbar name on window
//	char TrackbarName2[50];
//	sprintf( TrackbarName2, "H_MIN", H_MIN2);
//	sprintf( TrackbarName2, "H_MAX", H_MAX2);
//	sprintf( TrackbarName2, "S_MIN", S_MIN2);
//	sprintf( TrackbarName2, "S_MAX", S_MAX2);
//	sprintf( TrackbarName2, "V_MIN", V_MIN2);
//	sprintf( TrackbarName2, "V_MAX", V_MAX2);
//	//create trackbars and insert them into window
//	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
//	//the max value the trackbar can move (eg. H_HIGH), 
//	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
//	//                                  ---->    ---->     ---->      
//    createTrackbar( "H_MIN", trackbarWindowName2, &H_MIN2, 255, on_trackbar );
//    createTrackbar( "H_MAX", trackbarWindowName2, &H_MAX2, 255, on_trackbar );
//    createTrackbar( "S_MIN", trackbarWindowName2, &S_MIN2, 255, on_trackbar );
//    createTrackbar( "S_MAX", trackbarWindowName2, &S_MAX2, 255, on_trackbar );
//    createTrackbar( "V_MIN", trackbarWindowName2, &V_MIN2, 255, on_trackbar );
//    createTrackbar( "V_MAX", trackbarWindowName2, &V_MAX2, 255, on_trackbar );
//
//
//}
//void drawObject(int x, int y,Mat &frame){
//
//	//use some of the openCV drawing functions to draw crosshairs
//	//on your tracked image!
//
//    //UPDATE:JUNE 18TH, 2013
//    //added 'if' and 'else' statements to prevent
//    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)
//	
//	tracex1[count1] = x;
//	tracey1[count1] = y;
//	
//	count1++;
//
//
//	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
//    if(y-25>0)
//    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
//    if(y+25<FRAME_HEIGHT)
//    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
//    if(x-25>0)
//    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
//    if(x+25<FRAME_WIDTH)
//    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);
//
//	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
//
//}
//
//
//void drawObject2(int x, int y,Mat &frame){
//
//	//use some of the openCV drawing functions to draw crosshairs
//	//on your tracked image!
//
//    //UPDATE:JUNE 18TH, 2013
//    //added 'if' and 'else' statements to prevent
//    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)
//	tracex2[count2] = x;
//	tracey2[count2] = y;
//	time2[count2] = time(0);
//	count2++;
//
//
//	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
//    if(y-25>0)
//    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
//    if(y+25<FRAME_HEIGHT)
//    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
//    if(x-25>0)
//    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
//    if(x+25<FRAME_WIDTH)
//    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);
//
//	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
//
//}
//
//Mat morphOps(Mat thresh){
//
//	//create structuring element that will be used to "dilate" and "erode" image.
//	//the element chosen here is a 3px by 3px rectangle
//
//	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
//    //dilate with larger element so make sure object is nicely visible
//	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));
//
//	erode(thresh,thresh,erodeElement);
//	erode(thresh,thresh,erodeElement);
//
//
//	dilate(thresh,thresh,dilateElement);
//	dilate(thresh,thresh,dilateElement);
//	
//	return thresh;
//
//}
//void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){
//
//	Mat temp;
//	threshold.copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
//	//use moments method to find our filtered object
//	double refArea = 0;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		int numObjects = hierarchy.size();
//        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//        if(numObjects<MAX_NUM_OBJECTS){
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
//					
//					x = moment.m10/area;
//					y = moment.m01/area;
//					objectFound = true;
//					refArea = area;
//				}else objectFound = false;
//
//
//			}
//			//let user know you found an object
//			if(objectFound ==true){
//				//putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
//				//draw object location on screen
//				time1[count1] = time(0);
//				
//				if(std::abs(x-tracex1[count1-1])<5){
//					x=tracex1[count1-1];
//				}
//				if(std::abs(y-tracey1[count1-1])<5){
//					y=tracey1[count1-1];
//				}
//				drawObject(x,y,cameraFeed);}
//
//		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
//	}
//}
//
//void trackFilteredObject2(int &x2, int &y2, Mat threshold, Mat &cameraFeed){
//
//	Mat temp;
//	threshold.copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
//	//use moments method to find our filtered object
//	double refArea = 0;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		int numObjects = hierarchy.size();
//        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//        if(numObjects<MAX_NUM_OBJECTS){
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
//					x2 = moment.m10/area;
//					y2= moment.m01/area;
//					objectFound = true;
//					refArea = area;
//				}else objectFound = false;
//
//
//			}
//			//let user know you found an object
//			if(objectFound ==true){
//				//putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
//				
//				time2[count2] = time(0);
//				//draw object location on screen
//				if(std::abs(x2-tracex2[count2-1])<5){
//					x2=tracex2[count2-1];
//				}
//				if(std::abs(x2-tracex2[count2-1])<5){
//					y2=tracey2[count2-1];
//				}
//				
//				drawObject2(x2,y2,cameraFeed);}
//
//		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
//	}
//}
//
//
//
//bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,
//                      Point2f &r){
//    Point2f x = o2 - o1;
//    Point2f d1 = p1 - o1;
//    Point2f d2 = p2 - o2;
//
//    float cross = d1.x*d2.y - d1.y*d2.x;
//    if (abs(cross) < /*EPS*/1e-8)
//        return false;
//
//    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
//    r = o1 + d1 * t1;
//    return true;
//}
//
//
//double distance(float x11, float y11, float x22, float y22){
//	float first = (x11-x22)*(x11-x22);
//	float second =(y11-y22)*(y11-y22);
//	return sqrt(first+second);
//}
//
//int main(int argc, char* argv[])
//{
//	//some boolean variables for different functionality within this
//	//program
//    bool trackObjects = true;
//    bool useMorphOps = true;
//	//Matrix to store each frame of the webcam feed
//	Mat cameraFeed;
//	//matrix storage for HSV image
//	Mat HSV;
//	//matrix storage for binary threshold image
//	Mat threshold;
//	Mat threshold2;
//	//x and y values for the location of the object
//	int x=0, y=0;
//	int x2=0, y2=0;
//	//create slider bars for HSV filtering
//	//createTrackbars();
//	//createTrackbars2();
//	//VideoCapture capture("C:\\Users\\rohit.misra\\Downloads\\1.avi"); 
//	//video capture object to acquire webcam feed
//	VideoCapture capture;
//	capture.open(1);
//	//open capture object at location zero (default location for webcam)
//	//set height and width of capture frame
//	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
//	//start an infinite loop where webcam feed is copied to cameraFeed matrix
//	//all of our operations will be performed within this loop
//	int xprev=0, yprev=0;
//	int x2prev=0, y2prev=0;
//	
//
//
//	
//	while(1){
//		
//		 
//		//store image to matrix
//		capture.read(cameraFeed);
//		//convert frame from BGR to HSV colorspace
//		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
//		//filter HSV image between values and store filtered image to
//		//threshold matrix
//		
//
//
//		//perform morphological operations on thresholded image to eliminate noise
//		//and emphasize the filtered object(s)
//		//if(useMorphOps)
//		
//		
//		//pass in thresholded frame to our object tracking function
//		//this function will return the x and y coordinates of the
//		//filtered object
//		
//		
//		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
//		threshold = morphOps(threshold);
//		trackFilteredObject(x,y,threshold,cameraFeed);
//
//		inRange(HSV,Scalar(H_MIN2,S_MIN2,V_MIN2),Scalar(H_MAX2,S_MAX2,V_MAX2),threshold2);
//		threshold2 = morphOps(threshold2);
//		trackFilteredObject2(x2,y2,threshold2,cameraFeed);
//		
//		
//		//tracex2[count2] = x2;
//		//tracey2[count2] = x2;
//
//		//if(count1>2){
//		//	for(int i = 1; i<count1; i ++){
//		//		//circle(cameraFeed,Point(tracex1[i],tracey1[i]),1,Scalar(0,255,0),1);
//		//		cv::line(cameraFeed, cv::Point(tracex1[i],tracey1[i]), cv::Point(tracex1[i-1],tracey1[i-1]),Scalar(170,1,20),1,8,0);
//		//		
//		//	}
//		//}
//		Vec4f line; 
//		Point2i pointDraw; 
//		int* pointx = new int [20];
//		int* pointy = new int [20];
//		float x1new;
//		float y1new;
//		 vector<Point2i> vecDraw; 
//		if(count1>20){
//			for(int i = count1; i>count1-20; i --){
//				pointDraw.x=tracex1[i]; 
//				pointDraw.y=tracey1[i]; 
//				vecDraw.insert(vecDraw.end(),pointDraw); 
//				
//			}
//			
//			vecDraw[0]= vecDraw[1];
//			fitLine(vecDraw,line,CV_DIST_L2,0,0.01,0.01);
//
//			//float slope = (x-((*((cv::Matx<float,4,1>*)(&(line)))).val)[2])/(y-((*((cv::Matx<float,4,1>*)(&(line)))).val)[3]);
//			//float slope = atan2(((float)y-(float)((*((cv::Matx<float,4,1>*)(&(line)))).val)[3],(float)x-(float)((*((cv::Matx<float,4,1>*)(&(line)))).val)[2]));
//			//float x1new = x - 300 * cos(slope);
//			//float y1new = y - 300 * sin(slope);
//			x1new = x + (x-((*((cv::Matx<float,4,1>*)(&(line)))).val)[2])*200;
//			y1new = y + (y-((*((cv::Matx<float,4,1>*)(&(line)))).val)[3])*200;
//			cv::line(cameraFeed,Point(x,y),Point(x1new,y1new),Scalar(170,1,20),1,8,0);
//			
//		}
//
//
//		
//
//		Vec4f line2; 
//		Point2i pointDraw2; 
//		int* pointx2 = new int [20];
//		int* pointy2 = new int [20];
//		vector<Point2i> vecDraw2; 
//		float x2new;
//		float y2new;
//		if(count2>20){
//			for(int i = count2; i>count2-20; i --){
//				pointDraw2.x=tracex2[i]; 
//				pointDraw2.y=tracey2[i]; 
//				vecDraw2.insert(vecDraw2.end(),pointDraw2); 
//				
//			}
//			
//			vecDraw2[0]= vecDraw2[1];
//			fitLine(vecDraw2,line2,CV_DIST_L2,0,0.01,0.01);
//
//			//float slope = (x-((*((cv::Matx<float,4,1>*)(&(line)))).val)[2])/(y-((*((cv::Matx<float,4,1>*)(&(line)))).val)[3]);
//			//float slope = atan2(((float)y-(float)((*((cv::Matx<float,4,1>*)(&(line)))).val)[3],(float)x-(float)((*((cv::Matx<float,4,1>*)(&(line)))).val)[2]));
//			//float x1new = x - 300 * cos(slope);
//			//float y1new = y - 300 * sin(slope);
//			x2new = x2 + (x2-((*((cv::Matx<float,4,1>*)(&(line2)))).val)[2])*200;
//			y2new = y2 + (y2-((*((cv::Matx<float,4,1>*)(&(line2)))).val)[3])*200;
//			cv::line(cameraFeed,Point(x2,y2),Point(x2new,y2new),Scalar(160,2,20),1,8,0);
//			
//		}
//
//
//		
//
//		
//		//if(count2>2){
//		//	for(int i = 1; i<count2; i ++){
//		//		//circle(cameraFeed,Point(tracex2[i],tracey2[i]),1,Scalar(0,255,0),1);
//		//		cv::line(cameraFeed, cv::Point(tracex2[i],tracey2[i]), cv::Point(tracex2[i-1],tracey2[i-1]),Scalar(170,1,20),1,8,0);
//		//	}
//		//}
//
//
//		double velocity1 = 0;
//		if(count1>25){
//			float first = (tracex1[count1-1]-tracex1[count1-20])*(tracex1[count1-1]-tracex1[count1-20]);
//			float second =(tracey1[count1-1]-tracey1[count1-20])*(tracey1[count1-1]-tracey1[count1-20]);
//			velocity1 =  sqrt(first+second)/((time1[count1-1]-time1[count1-20]));
//
//			//std::cout<<"velocity of red object = "<<velocity1<<"\n";
//		}
//
//		double velocity2 = 0;
//		if(count2>25){
//			float first = (tracex2[count2-1]-tracex2[count2-20])*(tracex2[count2-1]-tracex2[count2-20]);
//			float second =(tracey2[count2-1]-tracey2[count2-20])*(tracey2[count2-1]-tracey2[count2-20]);
//			velocity2 =  sqrt(first+second)/((time2[count2-1]-time2[count2-20]));
//
//		//	std::cout<<"velocity of blue object = "<<velocity2<<"\n";
//		}
//		
//		if(count1>20 && count2>20){
//			Point2f intersctionPoint; 
//			if(intersection(Point(x,y),Point(x1new,y1new),Point(x2,y2),Point(x2new,y2new),intersctionPoint)==true){
//				
//				double time1 = distance(intersctionPoint.x,intersctionPoint.y,x,y)/std::ceil(velocity1+2);
//				double time2 = distance(intersctionPoint.x,intersctionPoint.y,x2,y2)/std::ceil(velocity2+2);
//				//std::cout<<velocity1<<" vs "<<velocity2<<"\n";
//				std::cout<<"time to intersection:" << abs(time1)<<" vs "<< abs(time2)<<"\n";
//				
//				if(std::abs(time1-time2)<2){
//					circle(cameraFeed,intersctionPoint,20,Scalar(0,0,255),2);
//				}else{
//					circle(cameraFeed,intersctionPoint,20,Scalar(0,255,255),2);
//				}
//			}
//		}
//
//
//		//putText(cameraFeed,"Distance between objects: "+distance,Point(0, 200),1,2,Scalar(0,0,255),2);
//		//show frames 
//		//std::cout<<"distance = "<<intToString(distance)<<"\n";
//
//
//		/*if(distance<12){
//			std::cout<<"Chances of collision!!!!"<<"\n";
//			cv::line(cameraFeed, cv::Point(x, y), cv::Point(x2, y2),Scalar(0,0,255),2,8,0);
//		}else{
//			cv::line(cameraFeed, cv::Point(x, y), cv::Point(x2, y2),Scalar(0,255,0),2,8,0);
//		}*/
//
//		//imshow(windowName2,threshold);
//		//imshow(windowName4,threshold2);
//		imshow(windowName,cameraFeed);
//		//imshow(windowName1,HSV);
//		
//
//		//delay 30ms so that screen can refresh.
//		//image will not appear without this waitKey() command
//
//		waitKey(10);
//	}
//
//	
//	return 0;
//}
