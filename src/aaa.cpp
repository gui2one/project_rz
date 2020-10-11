#include "aaa.h"

aaa::aaa()
{
	
	cv::CascadeClassifier face_cascade;
	face_cascade.load("./data/cascades/lbpcascade_frontalface_improved.xml");
	cv::Mat img = cv::imread("./data/image.jpg");
	cv::imshow("aaa", img);


	cv::Ptr < cv::face::Facemark > facemark = cv::face::createFacemarkKazemi();
	facemark->loadModel("./data/model/face_landmark_model.dat");
	//cout << "Loaded model" << endl;

	printf("AAAA !!!!\n");

	std::vector<cv::Rect> faces;
	//resize(img, img, cv::Size(460, 460), 0, 0, cv::INTER_LINEAR_EXACT);

	cv::Mat gray;
	
	if (img.channels() > 1) {
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	}
	else {
		gray = img.clone();
	}
	equalizeHist(gray, gray);

	face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

	std::vector< std::vector<cv::Point2f> > shapes;

	if (facemark->fit(img, faces, shapes))
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			cv::rectangle(img, faces[i], cv::Scalar(255, 0, 0));
		}
		for (unsigned long i = 0; i < faces.size(); i++) {
			for (unsigned long k = 0; k < shapes[i].size(); k++)
				cv::circle(img, shapes[i][k], 2, cv::Scalar(0, 0, 255), cv::FILLED);
		}
		cv::namedWindow("Detected_shape");
		imshow("Detected_shape", img);
		cv::waitKey(0);
	}
}
