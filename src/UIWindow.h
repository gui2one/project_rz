#pragma once
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
class UIWindow : public Gtk::Window
{
public:
	UIWindow();
	~UIWindow() override;


protected:

	void on_btn_clicked();
	void on_window_realize();

private:

	Gtk::Button m_button;
	Gtk::Frame m_frame;
};

