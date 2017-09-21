#ifndef GAME_ENGINE_GLSL_PROGRAM_HPP
#define GAME_ENGINE_GLSL_PROGRAM_HPP

#include <GL\glew.h>

#include <string>

namespace GameEngine
{
	namespace Rendering
	{
		// This class is used to compile, link and use a GLSL shader program
		// Reference available at http://www.opengl.org/wiki/Shader_Compilation
		class GLSLProgram
		{
		public:
			GLSLProgram() = default;

			void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

			void LinkShaders();

			void AddAttribute(const std::string& attributeName);
			GLint GetUniformLocation(const std::string& unfiromAttribute);

			void Bind();
			void Unbind();
		private:
			void CompileShader(const std::string& path, GLint shaderType, GLuint& shader);

			int m_numAttributes = 0;

			GLuint m_programID = 0;
			GLuint m_vertexShaderID = 0;
			GLuint m_fragmentShaderID = 0;
		};
	}
}

#endif