#include "lightmodel.h"
#include "shader.h"
#include "texture.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//--------------------------------------------------------------------------
light_model_app::light_model_app()
	: OpenGLApp()
{

}

//--------------------------------------------------------------------------
void light_model_app::init()
{
	static const char title[] = "OpenGL Application";
	OpenGLApp::init();
	memcpy(info.title, title, sizeof(title));
}

//--------------------------------------------------------------------------
void light_model_app::startup(void)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	load_shaders();
	object.load("../media/models/dragon.sbm");
}

//--------------------------------------------------------------------------
void light_model_app::shutdown(void)
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
}

//--------------------------------------------------------------------------
void light_model_app::render(double t)
{
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat ones[] = { 1.0f };
	glm::vec3 lightdirection = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 lightposition = glm::vec3(40.0f, 40.0f, 40.0f);

	float distance = 25.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, ones);

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glUseProgram(program);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(60.0f), (float)info.windowWidth / (float)info.windowHeight, 1.0f, 10000.0f);
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0, distance, distance), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::rotate(model_matrix, glm::radians((float)t * 19.3f), glm::vec3(0.0f, 1.0f, 0.0f));
	//model_matrix = glm::rotate(model_matrix, glm::radians((float)currentTime * 21.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 mv_matrix = view_matrix * model_matrix;
	glm::mat4 mvproj_matrix = proj_matrix * view_matrix * model_matrix;

	glUniform3fv(uniforms.light_position, 1, &lightposition[0]);
	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &mv_matrix[0][0]);
	glUniformMatrix4fv(uniforms.view_matrix, 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(uniforms.model_matrix, 1, GL_FALSE, &model_matrix[0][0]);
	glUniformMatrix4fv(uniforms.mvproj_matrix, 1, GL_FALSE, &mvproj_matrix[0][0]);

	object.render();
}
//--------------------------------------------------------------------------
void light_model_app::load_shaders()
{
	static float mat_diffuse[] = { 0.8, 0.8, 0.8 };
	static float mat_spec[] = { 1.0, 1.0, 1.0 };
	static float light_diffuse[] = { 1.0, 1.0, 1.0 };
	static float light_ambient[] = { 0.2, 0.2, 0.2 };
	static float light_spec[] = { 1.0, 1.0, 1.0 };
	static float light_shiness = 128.0;
	glDeleteShader(program);
	program = LoadShadersVF("../media/glsl/modelviewer.vs", "../media/glsl/modelviewer.fs");
	glUseProgram(program);
	uniforms.mv_matrix = glGetUniformLocation(program, "mv_matrix");
	uniforms.view_matrix = glGetUniformLocation(program, "view_matrix");
	uniforms.model_matrix = glGetUniformLocation(program, "model_matrix");
	uniforms.mvproj_matrix = glGetUniformLocation(program, "mvproj_matrix");
	uniforms.light_position = glGetUniformLocation(program, "light_position");
	uniforms.mat_diffuse = glGetUniformLocation(program, "mat_diffuse");
	uniforms.mat_spec = glGetUniformLocation(program, "mat_spec");
	uniforms.light_ambient = glGetUniformLocation(program, "light_ambient");
	uniforms.light_diffuse = glGetUniformLocation(program, "light_diffuse");
	uniforms.light_spec = glGetUniformLocation(program, "light_spec");
	uniforms.light_shiness = glGetUniformLocation(program, "light_shiness");
	
	glUniform3fv(uniforms.mat_diffuse, 1, &mat_diffuse[0]);
	glUniform3fv(uniforms.mat_spec, 1, &mat_spec[0]);
	glUniform3fv(uniforms.light_diffuse, 1, &light_diffuse[0]);
	glUniform3fv(uniforms.light_ambient, 1, &light_ambient[0]);
	glUniform3fv(uniforms.light_spec, 1, &light_spec[0]);
	glUniform1f(uniforms.light_shiness, light_shiness);
	glUseProgram(0);
}
//---------------------------------------------------------------------------
void light_model_app::onKey(int key, int scancode, int action, int mods)
{
	if (action)
	{
		switch (key)
		{
		case 'R': load_shaders();
			break;
		default:
			break;
		}
	}
	OpenGLApp::onKey(key, scancode, action, mods);
}