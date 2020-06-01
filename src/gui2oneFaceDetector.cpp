#include "gui2oneFaceDetector.h"
#include <vector>

gui2oneFaceDetector::gui2oneFaceDetector()
{
	printf("--- Face Detector Init ---\n");



	cv::Mat small;

	
	input_frame = cv::imread("data/group_1.jpg", cv::IMREAD_COLOR);
	cv::resize(input_frame, small, cv::Size(200, 200));
	
	

	detector.load("../../data/haar_cascades/haarcascade_frontalface_alt.xml");

	
	



	
}

gui2oneFaceDetector::~gui2oneFaceDetector()
{
}

void gui2oneFaceDetector::update()
{
	detector.detectMultiScale(input_frame, faces);

	for (auto face : faces) {

		cv::rectangle(input_frame, face, cv::Scalar(0, 0, 255));
	}
	// printf("num faces :  %d \n", faces.size());
	cv::imshow("capture", input_frame);
}
