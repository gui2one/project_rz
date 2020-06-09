#pragma once
#include <stdio.h>
#include <thread>
#include <mutex>

#include "gui2oneFaceDetector.h"


/*
	singleton pattern : instantiate with getInstance() method
*/
class TrackooCore {


private:
	static TrackooCore* pinstance;
	static std::mutex mutex;
public:

	/* singleton pattern methods  */
	
	static TrackooCore* getInstance();

	TrackooCore(const TrackooCore& other) = delete;

	void operator=(const TrackooCore& other) = delete;

	/* "operational" stuff */


	gui2oneFaceDetector* face_detector;
	cv::Mat capture_frame;



protected:

	TrackooCore() {
		printf("creating instance\n");
	}

};



