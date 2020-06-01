#include "UIWindow.h"

UIWindow::UIWindow():
	m_button("press me"),
	m_frame("Params")
{

	
	//frame.set_hexpand(true);
	//frame.set_vexpand(true);
	m_button.set_border_width(10);
	set_title("Trackoo 0.001 alpha");
	signal_realize().connect(sigc::mem_fun(this, &UIWindow::on_window_realize));
	set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_NORMAL);


	m_button.signal_clicked().connect(sigc::mem_fun(*this, &UIWindow::on_btn_clicked));



	set_default_size(1280, 720);

	//frame.add(m_button);
	m_frame.add(m_button);
	add(m_frame);


	show_all();

	
}

UIWindow::~UIWindow()
{
}

void UIWindow::on_btn_clicked()
{
	g_print("clicked ::\n");
}

void UIWindow::on_window_realize()
{
	g_print("UI Realize\n");

}



