#pragma once

//#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"


class gui2oneFaceDetector
{

public :
	gui2oneFaceDetector();

	~gui2oneFaceDetector();

	void initCvDnnNet();
	std::vector<cv::Rect> detectFaces(cv::Mat& frame);
	void update();

	
	cv::Mat input_frame;

	cv::dnn::Net m_dnn_net;
	std::vector<cv::Rect> faces;
	

	

private:
};

