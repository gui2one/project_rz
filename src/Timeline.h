#pragma once 

#include "gtkmm.h"

class Timeline
{
public:

	Timeline();

	inline Gtk::Widget& operator()(){ return box; }

	Gtk::Box box;
	Gtk::DrawingArea drawing_area;

	void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

	bool  on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:



};