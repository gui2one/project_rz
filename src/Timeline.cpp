#include "Timeline.h"

Timeline::Timeline() {

	

	box.pack_start(drawing_area);
	box.set_hexpand(true);
	box.set_vexpand(true);
	drawing_area.signal_draw().connect(sigc::mem_fun(this, &Timeline::on_draw));
	drawing_area.set_hexpand(true);
	drawing_area.set_vexpand(true);
}

void Timeline::draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	cr->rectangle(0, 0, width, height);
	cr->set_source_rgb(0.3, 0.3, 1.0);
	cr->fill();
}


bool Timeline::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation alloc;
	int baseline;
	box.get_allocated_size(alloc, baseline);
	//g_print("%d, %d\n", alloc.get_x(), alloc.get_y());
	drawing_area.set_size_request(alloc.get_width(), alloc.get_height());
	draw_rectangle(cr, alloc.get_width(), alloc.get_height());

	return true;
}
