#pragma once

//#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

class gui2oneFaceDetector
{

public :
	gui2oneFaceDetector();

	~gui2oneFaceDetector();

	void update();

	std::vector<cv::Rect> faces;
	cv::CascadeClassifier detector;
	cv::Mat input_frame;

private:
};

