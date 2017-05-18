//#include <opencv2\opencv.hpp>
//#include <vector>
//#include <sstream>
//#include <string>
//#include <iostream>
//#include <vector>
//#include <math.h>
//#include "LightColor.h"
//using namespace cv;
//using namespace std;
//
////default capture width and height
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 480;
////max number of objects to be detected in frame
//const int MAX_NUM_OBJECTS = 50;
////minimum and maximum object area
//const int MIN_OBJECT_AREA = 20 * 20;
//const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//
////to draw traffic light.
//#define RED_DRAW_CENTER Point(400,460)
//#define YELLOW_DRAW_CENTER Point(450,460)
//#define GREEN_DRAW_CENTER Point(500,460)
//#define LIGHT_DRAW_RADIUS 15
//#define MY_COLOR_RED Scalar(0,0,255)
//#define MY_COLOR_GREEN Scalar(0,255,0)
//#define MY_COLOR_YELLOW Scalar(60,255,255)
//
////draw traffic light after detection.
//void drawTrafficLights(Mat &targetImg, LightState lightState) {
//	switch (lightState) {
//	case GREEN:
//		circle(targetImg, GREEN_DRAW_CENTER, LIGHT_DRAW_RADIUS, MY_COLOR_GREEN, -1);
//		break;
//	case YELLOW:
//		circle(targetImg, YELLOW_DRAW_CENTER, LIGHT_DRAW_RADIUS, MY_COLOR_YELLOW, -1);
//		break;
//	case RED:
//		circle(targetImg, RED_DRAW_CENTER, LIGHT_DRAW_RADIUS, MY_COLOR_RED, -1);
//		break;
//	case NON_COLOR:
//		break;
//	}
//}
//
////to call draw location function.
//void draw_locations(Mat & img, const vector< Rect > & locations, const Scalar & color, Mat HSV);
//
////link video and xml.
////#define VIDEO_FILE_NAME "E:\\CNTT\\DoAn1_v2\\VisualProject\\LightDetection_HaarCascade\\LightDetection_HaarCascade\\xxx3.mp4"
//#define CASCADE_FILE_NAME "E:\\CNTT\\DoAn1_v2\\VisualProject\\LightDetection_HaarCascade\\LightDetection_HaarCascade\\light.xml"
//#define WINDOW_NAME "WINDOW"
//
////main
//int main()
//{
//	VideoCapture cap(0);
//	Mat mFrame, mGray;
//	CascadeClassifier classifier;
//	vector<Rect> vFound;
//
//	classifier.load(CASCADE_FILE_NAME);
//
//	if (!cap.isOpened()) {
//		cout << "cannot open camera";
//	}
//	cap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
//	cap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
//	int count = 0;
//
//	while (true)
//	{
//		//store image to matrix
//		cap.read(mFrame);
//		cap >> mFrame;
//		if (mFrame.empty()) {
//			break;
//		}
//
//		if (count >= 1)
//		{
//			Mat hsv_image;
//			cvtColor(mFrame, hsv_image, COLOR_BGR2HSV);
//
//			// Apply the classifier to the frame
//			cvtColor(mFrame, mGray, COLOR_BGR2GRAY);
//			equalizeHist(mGray, mGray);
//			classifier.detectMultiScale(mGray, vFound, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//			draw_locations(mFrame, vFound, Scalar(0, 255, 0), hsv_image);
//			
//			count = 0;
//		}
//		imshow(WINDOW_NAME, mFrame);
//		count++;
//		waitKey(1);
//	}
//
//	return 0;
//}
//
//
////detect color function.
//vector<LightColor> trackFilteredObject(LightColor theLight) {
//
//	vector <LightColor> lights;
//
//	Mat temp;
//	theLight.getHueThreshold().copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
//	//use moments method to find our filtered object
//	double refArea = 0;
//	//bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		int numObjects = hierarchy.size();
//		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//		if (numObjects<MAX_NUM_OBJECTS) {
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//				if (area>MIN_OBJECT_AREA) {
//
//					LightColor light = theLight;
//
//					light.xPos = moment.m10 / area;
//					light.yPos = moment.m01 / area;
//
//					lights.push_back(light);
//
//				}
//			}
//			return lights;
//		}
//	}
//}
//
////check color in detection area.
//bool checkLightPosition(vector< Rect >::const_iterator loc, const vector<LightColor> & lights)
//{
//	vector<LightColor>::const_iterator light = lights.begin();
//	vector<LightColor>::const_iterator light_end = lights.end();
//
//	for (; light != light_end; ++light)
//	{
//		if (light->xPos > loc->x && light->xPos < loc->x + loc->width
//			&& light->yPos > loc->y && light->yPos < loc->y + loc->height)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
////draw detection area after Apply the classifier.
//void draw_locations(Mat & img, const vector< Rect > & locations, const Scalar & color, Mat HSV)
//{
//	if (!locations.empty())
//	{
//		//create new color.
//		LightColor red(RED, HSV), yellow(YELLOW, HSV), green(GREEN, HSV);
//
//		//find color in frame.
//		vector<LightColor> reds = trackFilteredObject(red);
//		vector<LightColor> yellows = trackFilteredObject(yellow);
//		vector<LightColor> greens = trackFilteredObject(green);
//
//		//get detection area
//		vector< Rect >::const_iterator loc = locations.begin();
//		vector< Rect >::const_iterator end = locations.end();
//		for (; loc != end; ++loc)
//		{
//			//find the top image.
//			if (loc->y + loc->height <= FRAME_HEIGHT / 2)
//			{
//
//
//				//check color position to draw traffic light.
//				if (checkLightPosition(loc, reds))
//				{
//					drawTrafficLights(img, RED);
//					//draw the area.
//					rectangle(img, *loc, color, 2);
//				}
//				else if (checkLightPosition(loc, yellows))
//				{
//					drawTrafficLights(img, YELLOW);
//					//draw the area.
//					rectangle(img, *loc, color, 2);
//				}
//				else if (checkLightPosition(loc, greens))
//				{
//					drawTrafficLights(img, GREEN);
//					//draw the area.
//					rectangle(img, *loc, color, 2);
//				}
//			}
//		}
//	}
//}