#include "my_widget.h"


MyWidget::MyWidget()
{
	label.set_text("my widget !!!");
	vbox.set_hexpand(true);
	vbox.pack_start(label, false, false);

	button_1.set_label("press me");
	button_1.set_hexpand(true);
	vbox.pack_start(button_1, false, false);

	
}

Gtk::Widget& MyWidget::operator()()
{
	return vbox;
}
