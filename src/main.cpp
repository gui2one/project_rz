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
#include "FrameData.h"


FrameData current_frame_data;
gui2oneFaceDetector face_detector;

Glib::RefPtr<Gtk::Application> app;





void capture_loop() {

	cv::Mat captured;
	cv::VideoCapture cap("../../data/videos/public_stade_rennais.mp4");
	while (true) {

		cap >> captured;

		if (!captured.empty()) {
			current_frame_data.cv_frame = captured;
		}

	}
}

void face_detect_loop() {

	while (true)
	{
		face_detector.update();
	}
}

void on_activate() {
	printf("Application Activate Event\n");
}

int main(int argc, char *argv[])
{
	std::thread t_capture(capture_loop);
	


	
	face_detector.setFrameData(&current_frame_data);
	std::thread t_face_detect(face_detect_loop);

	app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	app->signal_activate().connect(&on_activate);

	UIWindow ui_window;
	LiveWindow live_window;

	live_window.setFrameData(&current_frame_data);


	//while (true) 
	//{
	//	cv::imshow("capture", current_frame);

	//	if (cv::waitKey(5) >= 0)
	//		break;
	//}

	return app->run(ui_window, argc, argv);
}