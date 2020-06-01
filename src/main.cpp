#include <gtkmm.h>
#include "my_widget.h"
#include "Timeline.h"
#include "GL/glew.h"


#include <vector>

#include "gui2oneFaceDetector.h"
#include "LiveWindow.h"
#include "UIWindow.h"




Glib::RefPtr<Gtk::Application> app;

void func() {
	printf("my FUNCTION\n");
}

int main(int argc, char *argv[])
{

	//gui2oneFaceDetector face_detector;
	app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");


	app->signal_activate().connect(&func);

	UIWindow ui_window;
	LiveWindow live_window;	
	

	return app->run(ui_window, argc, argv);
}