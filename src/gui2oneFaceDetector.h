#pragma once

//#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "FrameData.h"

class gui2oneFaceDetector
{

public :
	gui2oneFaceDetector();

	~gui2oneFaceDetector();



	void initCvDnnNet();
	inline void setInputFrame(cv::Mat _frame) { m_input_frame = _frame; }
	std::vector<cv::Rect> detectFaces(cv::Mat& frame);
	void update();

	inline cv::Mat getCaptureFrame() {
		return m_input_frame;
	};
	
	

	cv::dnn::Net m_dnn_net;

	cv::Size m_process_size;
	std::vector<cv::Rect> faces_rects;
	
	

	

private:
	cv::Mat m_input_frame;

};

	