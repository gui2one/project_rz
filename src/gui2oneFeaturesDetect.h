#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/face/facemark.hpp"

#include "pch.h"

class gui2oneFeaturesDetect
{

public:
	
	gui2oneFeaturesDetect();

	void getFeatures(cv::Mat& image);

	cv::CascadeClassifier face_cascade;
	cv::Ptr < cv::face::Facemark > facemark;

	std::vector<std::vector<cv::Point2f>> m_shapes;
};
