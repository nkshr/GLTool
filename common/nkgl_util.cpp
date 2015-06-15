#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "nkgl_util.h"

using namespace std;

char* load_shader_file(char *fname)
{
	FILE *fp;
	char * buf = NULL;
	int count = 0;

	fp = fopen(fname, "rt");
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		count = ftell(fp);
		rewind(fp);

		if (count > 0)
		{
			buf = (char *)malloc(sizeof(char)* (count + 1));
			count = (int)fread(buf, sizeof(char), count, fp);
			buf[count] = '\0';
		}
		fclose(fp);
	}
	return buf;
}

void add_shader(GLuint shader_prog, const char* pshader_file, GLenum shader_type)
{
	GLuint sobj = glCreateShader(shader_type);
	if (sobj == 0)
	{
		cerr << "Error: Couldn't create shader obj " << shader_type << endl;
		exit(1);
	}

	const GLchar *p[1];
	p[0] = pshader_file;
	GLint lengths[1];
	lengths[0] = (GLint)strlen(pshader_file);
	glShaderSource(sobj, 1, p, lengths);
	glCompileShader(sobj);
	GLint success;
	glGetShaderiv(sobj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[1024];
		glGetShaderInfoLog(sobj, 1024, NULL, info_log);
		exit(1);
	}

	glAttachShader(shader_prog, sobj);
}

void lv_spro(GLint shader_program)	//link and valid shader program.
{
	GLint spro = shader_program;
	GLint success = 0;
	GLchar error_log[1024] = { 0 };

	glLinkProgram(spro);
	glGetProgramiv(spro, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(spro, sizeof(error_log), NULL, error_log);
		cerr << "Error: Couldn't link shader program: " << error_log << endl;
		exit(1);
	}

	glValidateProgram(spro);
	glGetProgramiv(spro, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(spro, sizeof(error_log), NULL, error_log);
		cerr << "Error: Invalid shader program: " << error_log << endl;
		exit(1);
	}

	glUseProgram(spro);
}