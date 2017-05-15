#pragma once
#include <string>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

enum LightState
{
	NON_COLOR,
	RED, YELLOW, GREEN
};

class LightColor
{
public:
	LightColor();
	~LightColor(void);

	LightColor(LightState state, Mat hsv_image);

	int xPos = 0, yPos = 0;
	Mat getHueThreshold(){ return hue_threshold; }

	LightState getLightState() { return lightState; }
	void setLightState(LightState lt) { lightState = lt; }

private:

	void morphOps(Mat &thresh);

	LightState lightState;
	Mat hue_threshold;
};