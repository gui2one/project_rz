#pragma once
#include <gtkmm.h>
#include <stdio.h>


// pattern found here :https://stackoverflow.com/questions/41344241/gtkmm-c11-how-to-create-a-custom-composite-widget-out-of-other-widgets
class MyWidget : public Gtk::Widget
{
public:
	MyWidget();
	Gtk::Widget& operator()();

	Gtk::Box vbox { Gtk::ORIENTATION_HORIZONTAL };
	Gtk::Label label;
	Gtk::Button button_1;

private:

	

};
