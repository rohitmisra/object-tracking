
#include <sstream>
#include <string>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <time.h>
#include "functions.h"
using namespace cv;
using namespace internalFunctions;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 75;
int H_MAX = 217;
int S_MIN = 128;
int S_MAX = 255;
int V_MIN = 80;
int V_MAX = 255;

int H_MIN2 = 49;
int H_MAX2 = 105;
int S_MIN2 = 51;
int S_MAX2 = 148;
int V_MIN2 = 0;
int V_MAX2 = 157;
cv::Mat dst;
int count1 = 0;
int count2 = 0;

time_t time1[10000];
time_t time2[10000];

int tracex1[90000];
int tracey1[90000];
int tracex2[90000];
int tracey2[90000];

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20 * 20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image1";
const string windowName4 = "Thresholded Image2";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Object1";
const string trackbarWindowName2 = "Object2";

void on_trackbar(int, void*) {

}



void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);

	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, 255, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, 255, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, 255, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, 255, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, 255, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, 255, on_trackbar);

}


void drawObject(int x, int y, Mat &frame, String shape) {

	tracex1[count1] = x;
	tracey1[count1] = y;

	count1++;

	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	if (y - 25>0)
		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
	if (y + 25<FRAME_HEIGHT)
		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
	if (x - 25>0)
		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
	if (x + 25<FRAME_WIDTH)
		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

	putText(frame, shape, Point(x, y + 30), 1, 2, Scalar(0, 255, 0), 2);

}




void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed, String shape) {

	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;


				if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {

					x = moment.m10 / area;
					y = moment.m01 / area;
					objectFound = true;
					refArea = area;
				}
				else objectFound = false;


			}

			if (objectFound == true) {

				time1[count1] = time(0);

				if (std::abs(x - tracex1[count1 - 1])<10) {
					x = tracex1[count1 - 1];
				}
				if (std::abs(y - tracey1[count1 - 1])<10) {
					y = tracey1[count1 - 1];
				}
				drawObject(x, y, cameraFeed, shape);
			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
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
	int x = 0, y = 0;

	//create slider bars for HSV filtering
	createTrackbars();
	//createTrackbars2();


	
	//video capture object to acquire webcam feed
	VideoCapture capture;
	capture.open(0);
	//open capture object at location zero (default location for webcam)
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);


	while (1) {

		capture.read(cameraFeed);
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
		threshold = morphOps(threshold);
		//trackFilteredObject(x,y,threshold,cameraFeed);
		cv::Mat edges;
		cv::Canny(threshold, edges, 100, 200, 3, false);
		dst.create(cameraFeed.size(), cameraFeed.type());
		dst = Scalar::all(1);

		dst.copyTo(cameraFeed, edges);



		// Find contours
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(edges.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		std::vector<cv::Point> approx;
		cv::Mat dst = src.clone();

		String shape = "";
		for (int i = 0; i < contours.size(); i++)
		{
			// Approximate contour with accuracy proportional
			// to the contour perimeter
			cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

			// Skip small or non-convex objects 
			if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
				continue;

			if (approx.size() == 3)
			{
				//setLabel(dst, "TRI", contours[i]);    // Triangles
				shape = "Triangle";
			}
			else if (approx.size() >= 4 && approx.size() <= 6)
			{
				// Number of vertices of polygonal curve
				int vtc = approx.size();

				// Get the cosines of all corners
				std::vector<double> cos;
				for (int j = 2; j < vtc + 1; j++)
					cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));

				// Sort ascending the cosine values
				std::sort(cos.begin(), cos.end());

				// Get the lowest and the highest cosine
				double mincos = cos.front();
				double maxcos = cos.back();

				// Use the degrees obtained above and the number of vertices
				// to determine the shape of the contour
				if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
					//setLabel(dst, "RECT", contours[i]);
					shape = "Rectangle";
				else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
					//setLabel(dst, "PENTA", contours[i]);
					shape = "pentagon";
				else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
					//setLabel(dst, "HEXA", contours[i]);
					shape = "Hexagon";
			}
			else
			{
				// Detect and label circles
				double area = cv::contourArea(contours[i]);
				cv::Rect r = cv::boundingRect(contours[i]);
				int radius = r.width / 2;

				if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
					std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
					//setLabel(dst, "CIR", contours[i]);
					shape = "Circle";
			}
		}

		trackFilteredObject(x, y, threshold, cameraFeed, shape);

		imshow(windowName, cameraFeed);
		imshow("Threshold", threshold);
		cv::waitKey(10);
	}


	return 0;
}
