#include "gui2oneFaceDetector.h"
#include <vector>
#include <stdio.h>
#include <iostream>
gui2oneFaceDetector::gui2oneFaceDetector()
{
	printf("--- Face Detector Init ---\n");

	input_frame = cv::imread("data/group_1.jpg", cv::IMREAD_COLOR);
	
	initCvDnnNet();
	
	cv::VideoCapture cap("../../data/videos/public_stade_rennais.mp4");	

	if (!cap.isOpened()) {

		printf("capture not Opened \n");
	}

	cv::Mat frame, small, grey;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);

		
		// check if we succeeded
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// show live and wait for a key with timeout long enough to show images
		
		cv::resize(frame, small, cv::Size(1024, 576));

		//detector.detectMultiScale(small, faces);
		faces = detectFaces(small);
		for (auto face : faces) {
			cv::rectangle(small, face, (0, 0, 255), 2);
		}

		
		imshow("Live", small);
		if (cv::waitKey(5) >= 0)
			break;
	}
	
	
}

gui2oneFaceDetector::~gui2oneFaceDetector()
{
}

void gui2oneFaceDetector::update()
{


	//cv::imshow("capture", input_frame);
}

void gui2oneFaceDetector::initCvDnnNet()
{
	// "./data/deploy.prototxt.txt", "./data/res10_300x300_ssd_iter_140000.caffemodel"

	//m_dnn_net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL_FP16 || cv::dnn::DNN_TARGET_OPENCL);
	//m_dnn_net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	
	m_dnn_net = cv::dnn::readNetFromCaffe("./data/deploy.prototxt.txt", "./data/res10_300x300_ssd_iter_140000.caffemodel");


	m_dnn_net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	m_dnn_net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);

}

std::vector<cv::Rect> gui2oneFaceDetector::detectFaces(cv::Mat& frame)
{
	cv::Mat inputBlob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(640, 360), 0, false, false);
	m_dnn_net.setInput(inputBlob, "data");
	cv::Mat detection = m_dnn_net.forward("detection_out");
	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());



	std::vector<cv::Rect> rectangles;
	rectangles.clear();
	for (int i = 0; i < detectionMat.rows; i++)
	{

		float confidence = detectionMat.at<float>(i, 2);
		float confidenceThreshold = 0.9;
		int frameWidth = frame.cols;
		int frameHeight = frame.rows;
		if (confidence > confidenceThreshold)
		{
			//printf("Confidence : %.3f\n", confidence);
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);


			//cv::Rect rect(cv::Point(x1, y1), cv::Point(x2, y2));
			
			cv::Point p1 = cv::Point(x1, y1);
			cv::Point p2 = cv::Point(x2, y2);
			cv::Rect rect = cv::Rect(p1, p2);


			rectangles.push_back(rect);
			//frame = frame(rect);
			//cv::resizeWindow("edges", rect.size());
		}
	}

	return rectangles;
}
