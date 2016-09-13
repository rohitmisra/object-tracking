#ifndef INTERNAL_FUNCTIONS_H_
#define INTERNAL_FUNCTIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using std::string;
using std::vector;
namespace internalFunctions {
	Mat morphOps(Mat thresh) {


		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
		//dilate with larger element so make sure object is nicely visible
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

		erode(thresh, thresh, erodeElement);
		erode(thresh, thresh, erodeElement);


		dilate(thresh, thresh, dilateElement);
		dilate(thresh, thresh, dilateElement);

		return thresh;

	}
	unsigned int root(unsigned int x) {
		unsigned int a, b;
		b = x;
		a = x = 0x3f;
		x = b / x;
		a = x = (x + a) >> 1;
		x = b / x;
		a = x = (x + a) >> 1;
		x = b / x;
		x = (x + a) >> 1;
		return(x);
	}


	string intToString(std::int_fast32_t number) {
		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,
		Point2f &r) {
		Point2f x = o2 - o1;
		Point2f d1 = p1 - o1;
		Point2f d2 = p2 - o2;

		float cross = d1.x*d2.y - d1.y*d2.x;
		if (abs(cross) < /*EPS*/1e-8)
			return false;

		double t1 = (x.x * d2.y - x.y * d2.x) / cross;
		r = o1 + d1 * t1;
		return true;
	}


	double distance(float x11, float y11, float x22, float y22) {
		float first = (x11 - x22)*(x11 - x22);
		float second = (y11 - y22)*(y11 - y22);
		return sqrt(first + second);
	}

}
Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}


void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

	namedWindow("drawing", CV_WINDOW_AUTOSIZE);
	cv::imshow("drawing", canny_output);

	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	cv::imshow("Contours", drawing);
}
/**
* Helper function to display text in the center of a contour
*/



String findShape(Mat src) {
	String shape = "no shape found";
	//cv::Mat src = cv::imread("polygon.png");

	/*if (src.empty())
	return "No object found";
	/// Load source image and convert it to gray
	src = imread("c:\\1\\shapes2.jpg");

	*/

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	// Convert to grayscale
	cv::Mat gray;
	cv::cvtColor(src, gray, CV_BGR2GRAY);

	// Use Canny instead of threshold to catch squares with gradient shading
	cv::Mat bw;
	cv::Canny(gray, bw, 0, 50, 5);

	// Find contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	cv::Mat dst = src.clone();

	for (int i = 0; i < contours.size(); i++)
	{
		// Approximate contour with accuracy proportional
		// to the contour perimeter
		cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

		// Skip small or non-convex objects 
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;
		std::cout << approx.size();
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
				shape = "Rect";
			else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
				//setLabel(dst, "PENTA", contours[i]);
				shape = "penta";
			else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
				//setLabel(dst, "HEXA", contours[i]);
				shape = "Hexa";

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

	cv::imshow("src", src);
	cv::imshow("dst", dst);
	cv::waitKey(0);
	return shape;
}




#endif //INTERNAL_FUNCTIONS_H_