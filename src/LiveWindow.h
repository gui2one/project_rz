#pragma once
#include <gtkmm.h>
#include "GL/glew.h"

#include "pch.h"

#include "3d_utils.h"
#include "core.h"
#include "FrameData.h"
#include "trackoo_core.h"
#include "opencv2/imgproc.hpp"

class LiveWindow : public Gtk::Window
{
public:
	LiveWindow();

	void on_window_realize();
	inline void setFrameData(FrameData* ptr)
	{
		frame_data = ptr;
	}

	gboolean on_gl_area_render(const Glib::RefPtr<Gdk::GLContext>& context);

	
	inline void bindCore(TrackooCore * ptr) { core = ptr;  }

	void on_gl_area_realize();

	void BindCVMat2GLTexture(cv::Mat& image, GLuint& imageTexture);

private:
	Gtk::Button m_button;
	Gtk::GLArea m_gl_area;

	MeshObject m_mesh_object;
	Shader  m_screen_shader;

	Texture m_texture;
	GLuint texture_id;

	FrameData* frame_data = nullptr;

	TrackooCore* core = nullptr;

protected:
	
};

