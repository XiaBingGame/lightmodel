#ifndef __TEMPLATE_APP_HEADER_H__
#define __TEMPLATE_APP_HEADER_H__

#include "OpenGLApp.h"
#include "model.h"

/** Class */
class light_model_app : public OpenGLApp
{
public:
	/** ���캯��. */
	light_model_app();

	/** ��ʼ������.
	@remarks
		����ĳ�ʼ��.
	*/
	void init();

	/// OpenGL ������ʼ��.
	void startup();

	/// OpenGL ��������.
	void shutdown();

	/// ��Ⱦ.
	void render(double t);


protected:
	virtual void onKey(int key, int scancode, int action, int mods);

private:
	void load_shaders();

	GLuint      program;		/// �������
	GLuint      vao;			/// �����������

	sb6::object     object;

	struct
	{
		GLuint       mv_matrix;
		GLuint		view_matrix;
		GLuint		model_matrix;
		GLuint		mvproj_matrix;
		GLuint		light_position;
		GLuint		mat_diffuse;
		GLuint		mat_spec;
		GLuint		light_ambient;
		GLuint		light_diffuse;
		GLuint		light_spec;
		GLuint		light_shiness;
	} uniforms;
};


#endif