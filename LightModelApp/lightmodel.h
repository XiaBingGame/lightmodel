#ifndef __TEMPLATE_APP_HEADER_H__
#define __TEMPLATE_APP_HEADER_H__

#include "OpenGLApp.h"
#include "model.h"

/** Class */
class light_model_app : public OpenGLApp
{
public:
	/** 构造函数. */
	light_model_app();

	/** 初始化函数.
	@remarks
		最初的初始化.
	*/
	void init();

	/// OpenGL 环境初始化.
	void startup();

	/// OpenGL 环境销毁.
	void shutdown();

	/// 渲染.
	void render(double t);


protected:
	virtual void onKey(int key, int scancode, int action, int mods);

private:
	void load_shaders();

	GLuint      program;		/// 程序对象
	GLuint      vao;			/// 顶点数组对象

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