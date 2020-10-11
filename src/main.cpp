#include <gtkmm.h>
#include "my_widget.h"
#include "Timeline.h"
#include "GL/glew.h"


#include <vector>

#include "gui2oneFaceDetector.h"
#include "LiveWindow.h"
#include "UIWindow.h"

#include <thread>
#include "pch.h"

#include "trackoo_core.h"
#include "aaa.h"

gui2oneFaceDetector face_detector;
gui2oneFeaturesDetect features_detect;

TrackooCore * tk_core;
Glib::RefPtr<Gtk::Application> app;


//aaa* _aaa = new aaa();


void capture_loop() {

	cv::Mat captured;
	cv::VideoCapture cap(0);
	while (true) {

		cap >> captured;

		if (!captured.empty()) {
			tk_core->capture_frame = captured;
		}

	}
}

void face_detect_loop() {

	while (true)
	{
		face_detector.setInputFrame(tk_core->capture_frame);
		face_detector.update();

		features_detect.getFeatures(tk_core->capture_frame);
	}
}

void on_activate() {
	printf("Application Activate Event\n");
}

int main(int argc, char *argv[])
{

	/* create TrackooCore singleton instance*/
	tk_core = TrackooCore::getInstance();

	/* Start capture thread*/
	std::thread t_capture(capture_loop);
	
	
	

	std::thread t_face_detect(face_detect_loop);

	app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	app->signal_activate().connect(&on_activate);

	UIWindow ui_window;
	LiveWindow live_window;


	tk_core->face_detector = &face_detector;
	tk_core->features_detect = &features_detect;
	live_window.bindCore(tk_core);

	//while (true) 
	//{
	//	cv::imshow("capture", current_frame);

	//	if (cv::waitKey(5) >= 0)
	//		break;
	//}

	return app->run(ui_window, argc, argv);
}