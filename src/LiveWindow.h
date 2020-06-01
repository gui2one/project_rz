#pragma once
#include <gtkmm.h>
#include "GL/glew.h"

#include "pch.h"

#include "3d_utils.h"
#include "core.h"

class LiveWindow : public Gtk::Window
{
public:
	LiveWindow();

	void on_window_realize();


	gboolean on_gl_area_render(const Glib::RefPtr<Gdk::GLContext>& context);

	void on_gl_area_realize();

private:
	Gtk::Button m_button;
	Gtk::GLArea m_gl_area;

	MeshObject m_mesh_object;
	Shader  m_default_shader;

protected:
	
};

