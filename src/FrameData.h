#pragma once
#include <opencv2/core.hpp>
#include <vector>
class FrameData {
public:
	cv::Mat cv_frame;
	std::vector<cv::Rect> faces_rects;
private:

};
