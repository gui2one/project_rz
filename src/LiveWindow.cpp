#include "LiveWindow.h"

LiveWindow::LiveWindow()
{
	set_title("Live Window");

	

	
	add(m_gl_area);
	signal_realize().connect(sigc::mem_fun(this, &LiveWindow::on_window_realize));
	m_gl_area.signal_realize().connect(sigc::mem_fun(this, &LiveWindow::on_gl_area_realize), false);
	m_gl_area.signal_render().connect(sigc::mem_fun(this, &LiveWindow::on_gl_area_render), false);

	set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);

	set_size_request(640, 360);

	show_all();


	Mesh mesh = Utils::makeSimpleQuad(1,1);
	m_mesh_object.setMesh(mesh);


	m_default_shader.loadVertexShaderSource("../../src/res/shaders/screen_shader.vert");
	m_default_shader.loadFragmentShaderSource("../../src/res/shaders/screen_shader.frag");
	m_default_shader.createShader();
}

void LiveWindow::on_window_realize()
{

		m_gl_area.queue_draw();
		g_print("gl_on_realize\n");
	
}

gboolean LiveWindow::on_gl_area_render(const Glib::RefPtr<Gdk::GLContext>& context)
{
	//g_print("render gl\n");


	GLCall(glClearColor(0.0, 0.5, 0.5, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	glLoadIdentity();
/*
	glMatrixMode(GL_PROJECTION);

	glMatrixMode(GL_MODELVIEW);*/

	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	GLCall(glPointSize(3.0));

	m_default_shader.useProgram();
	m_mesh_object.render();
	GLCall(glUseProgram(0));
	
	m_gl_area.queue_render();
	return true;
}

void LiveWindow::on_gl_area_realize()
{
	

	m_gl_area.make_current();

	if (glewInit() != GLEW_OK) {
		g_print("error with GLEW\n");
	}else{
		printf("GLEW ok\n");
	}

	const unsigned char * gl_version = glGetString(GL_VERSION);
	const unsigned char * glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	g_print("\nOpengl Version Info \n");
	g_print("---------------------------\n");
	g_print("\t-OpenGL : %s\n", gl_version);
	g_print("\t-Shading Language : %s\n", glsl_version);
	g_print("---------------------------\n");

	glEnable(GL_DEPTH_TEST);
	m_gl_area.queue_render();


}
