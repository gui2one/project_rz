#include "gui2oneFeaturesDetect.h"

gui2oneFeaturesDetect::gui2oneFeaturesDetect()
{
	

	face_cascade.load("./data/cascades/lbpcascade_frontalface_improved.xml");
	//face_cascade.load("./data/cascades/lbpcascade_profileface.xml");
	//cv::Mat img = cv::imread("./data/image.jpg");
	//cv::imshow("aaa", img);


	facemark = cv::face::createFacemarkKazemi();
	facemark->loadModel("./data/model/face_landmark_model.dat");
	//cout << "Loaded model" << endl;

	//printf("AAAA !!!!\n");

	
	//resize(img, img, cv::Size(460, 460), 0, 0, cv::INTER_LINEAR_EXACT);



	

	
}

void gui2oneFeaturesDetect::getFeatures(cv::Mat & img)
{
	if (img.empty()) {

		//printf("Features image empty !! \n");

	}
	cv::Mat gray;

	if (img.channels() > 1) {
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	}
	else {
		gray = img.clone();
	}
	equalizeHist(gray, gray);
	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

	if (faces.size() > 0) {
		
		//return std::vector<std::vector<cv::Point2f>>();


		//std::vector< std::vector<cv::Point2f> > shapes;
		if (facemark->fit(img, faces, m_shapes))
		{
			//for (size_t i = 0; i < faces.size(); i++)
			//{
			//	cv::rectangle(gray, faces[i], cv::Scalar(255, 0, 0));
			//}
			//for (unsigned long i = 0; i < faces.size(); i++) {
			//	for (unsigned long k = 0; k < m_shapes[i].size(); k++)
			//		cv::circle(gray, m_shapes[i][k], 2, cv::Scalar(0, 0, 255), cv::FILLED);
			//}
			//cv::namedWindow("Detected_shape");
			//imshow("Detected_shape", img);
			//cv::waitKey(0);
		}
	}
	else {
		//printf("no face found\n");
	}
	//return std::vector<std::vector<cv::Point2f>>();
}
