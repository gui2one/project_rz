#include "LiveWindow.h"

LiveWindow::LiveWindow()
{
	//printf("LIVE WINDOW constructor\n");
	set_title("Live Window");
	set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);
	set_size_request(1280, 720);

	
	add(m_gl_area);
	signal_realize().connect(sigc::mem_fun(this, &LiveWindow::on_window_realize));
	m_gl_area.signal_realize().connect(sigc::mem_fun(this, &LiveWindow::on_gl_area_realize), false);
	m_gl_area.signal_render().connect(sigc::mem_fun(this, &LiveWindow::on_gl_area_render), false);


	show_all();


	Mesh mesh = Utils::makeSimpleQuad(2,2);
	Utils::translateMesh(mesh, glm::vec3(-1.0, -1.0, 0.0));
	m_mesh_object.setMesh(mesh);


	m_screen_shader.loadVertexShaderSource("../../src/res/shaders/screen_shader.vert");
	m_screen_shader.loadFragmentShaderSource("../../src/res/shaders/screen_shader.frag");
	m_screen_shader.createShader();

	m_texture.load("data/image.jpg");

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glGenTextures(1, &texture_id);
}

void LiveWindow::on_window_realize()
{

		m_gl_area.queue_draw();
		//g_print("gl_on_realize\n");
	
}

gboolean LiveWindow::on_gl_area_render(const Glib::RefPtr<Gdk::GLContext>& context)
{
	
	
	if (core != nullptr) {

		//g_print("accessing Core\n");
		cv::Mat temp = core->capture_frame;
		//float ratio = temp.size().width / core->face_detector->m_process_size.width;
		float ratio = temp.size().width / (float)temp.size().height;

		//printf("ratio : %.3f \n", ratio);
		for (auto rect : core->face_detector->faces_rects) 
		{
			
			cv::Rect new_rect = rect;
			//new_rect.x *= ratio;
			new_rect.y *= ratio;
			//new_rect.width *= ratio;
			new_rect.height *= ratio;
			cv::rectangle(temp, new_rect, cv::Scalar(0, 0, 255), 2);
		}

		for (auto shape : core->features_detect->m_shapes) {
			for (auto point : shape) {

				cv::circle(temp, point, 5, cv::Scalar(255,0,0));
			}
		}
		BindCVMat2GLTexture(temp, m_texture.id);

		GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
		//glLoadIdentity();



		m_screen_shader.useProgram();
		glBindTexture(GL_TEXTURE_2D, m_texture.id);
		m_mesh_object.render();
		glBindTexture(GL_TEXTURE_2D, 0);
		GLCall(glUseProgram(0));
	
		m_gl_area.queue_render();

	}
	return true;
}

void LiveWindow::on_gl_area_realize()
{
	

	m_gl_area.make_current();

	if (glewInit() != GLEW_OK) {
		g_print("error with GLEW\n");
	}else{
		//printf("GLEW ok\n");
	}

	const unsigned char * gl_version = glGetString(GL_VERSION);
	const unsigned char * glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	g_print("\nOpengl Version Info \n");
	g_print("---------------------------\n");
	g_print("\t-OpenGL : %s\n", gl_version);
	g_print("\t-Shading Language : %s\n", glsl_version);
	g_print("---------------------------\n");

	GLCall(glEnable(GL_DEPTH_TEST));
	
	m_gl_area.queue_render();


}


void LiveWindow::BindCVMat2GLTexture(cv::Mat& image, GLuint& imageTexture)
{
	if (image.empty()) {
		//std::cout << "image empty" << std::endl;
	}
	else {
		
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, imageTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		cv::Mat rgb_image;
		cv::cvtColor(image, rgb_image, cv::COLOR_BGR2RGB);

		glTexImage2D(GL_TEXTURE_2D,         // Type of texture
			0,                   // Pyramid level (for mip-mapping) - 0 is the top level
			GL_RGB,              // Internal colour format to convert to
			image.cols,          // Image width  i.e. 640 for Kinect in standard mode
			image.rows,          // Image height i.e. 480 for Kinect in standard mode
			0,                   // Border width in pixels (can either be 1 or 0)
			GL_RGB,              // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,    // Image data type
			rgb_image.ptr());        // The actual image data itself
	}
}
