#include "LightColor.h"

LightColor::LightColor()
{
	//set values for default constructor
	setLightState(NON_COLOR);
	LightColor::hue_threshold = NULL;

}

void LightColor::morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}

LightColor::LightColor(LightState state, Mat hsv_image) {

	setLightState(state);
	switch (state)
	{
	case NON_COLOR:
		break;
	case RED: 
	{
		// Threshold the HSV image, keep only the red pixels
		Mat lower_red_hue_range;
		Mat upper_red_hue_range;
		inRange(hsv_image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
		inRange(hsv_image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);

		// Combine the above two images
		Mat red_hue_image;
		addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_image);
		GaussianBlur(red_hue_image, red_hue_image, Size(9, 9), 2, 2);
		morphOps(red_hue_image);

		//Save value for red:
		LightColor::hue_threshold = red_hue_image;
		break;
	}
	case YELLOW: {
		Mat lower_yellow_hue_range;
		Mat upper_yellow_hue_range;
		inRange(hsv_image, Scalar(22, 100, 160), Scalar(34, 255, 255), lower_yellow_hue_range);
		inRange(hsv_image, Scalar(5, 50, 50), Scalar(15, 255, 255), upper_yellow_hue_range);
		//inRange(hsv_image, Scalar(0, 112, 134), Scalar(12, 227, 255), upper_yellow_hue_range);

		Mat yellow_hue_image;
		addWeighted(lower_yellow_hue_range, 1.0, upper_yellow_hue_range, 1.0, 0.0, yellow_hue_image);

		GaussianBlur(yellow_hue_image, yellow_hue_image, Size(9, 9), 2, 2);
		morphOps(yellow_hue_image);

		//Save value for Yellow:
		LightColor::hue_threshold = yellow_hue_image;
		break;
	}
	case GREEN: {
		Mat lower_green_hue_range;
		Mat upper_green_hue_range;
		inRange(hsv_image, Scalar(30, 59, 50), Scalar(79, 158, 171), lower_green_hue_range);
		inRange(hsv_image, Scalar(0, 255, 0), Scalar(229, 255, 204), upper_green_hue_range);

		Mat green_hue_image;
		addWeighted(lower_green_hue_range, 1.0, upper_green_hue_range, 1.0, 0.0, green_hue_image);

		GaussianBlur(green_hue_image, green_hue_image, Size(9, 9), 2, 2);
		morphOps(green_hue_image);

		//Save value for Green:
		LightColor::hue_threshold = green_hue_image;

		break;
	}
	default:
		break;
	}
}

LightColor::~LightColor(void)
{
}
