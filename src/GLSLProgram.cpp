#include "GLSLProgram.hpp"
#include "Utility.hpp"

#include <fstream>
#include <vector>

namespace GameEngine
{
	namespace Rendering
	{
		void GLSLProgram::CompileShader(const std::string& path, GLint shaderType, GLuint& shader)
		{
			shader = glCreateShader(shaderType);

			if (shader == 0)
			{
				Private::Utility::Error::FatalError("Shader " + path + " failed to be created!");
			}

			std::ifstream file(path);

			if (file.fail())
			{
				Private::Utility::Error::FatalError("Failed to open file " + path);
			}

			// Read all the data from the file into one file
			std::string fileContents("");

			std::string line;

			while (std::getline(file, line))
			{
				fileContents += line + "\n";
			}

			file.close();

			// Load the file contents
			const char* contentsPtr = fileContents.c_str();
			glShaderSource(shader, 1, &contentsPtr, nullptr);

			// Compile our shader
			glCompileShader(shader);

			GLint success = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (success == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<char> errorLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

				glDeleteShader(shader);

				std::printf("%s\n", &errorLog[0]);
				Private::Utility::Error::FatalError("Shader failed to compile " + path);
			}
		}

		void GLSLProgram::CompileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		{
			m_programID = glCreateProgram();

			CompileShader(vertexShaderPath, GL_VERTEX_SHADER, m_vertexShaderID);
			CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER, m_fragmentShaderID);
		}

		void GLSLProgram::LinkShaders()
		{
			glAttachShader(m_programID, m_vertexShaderID);
			glAttachShader(m_programID, m_fragmentShaderID);

			glLinkProgram(m_programID);

			GLint isLinked = 0;
			glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);

			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<char> errorLog(maxLength);
				glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

				glDeleteProgram(m_programID);

				glDeleteShader(m_vertexShaderID);
				glDeleteShader(m_fragmentShaderID);

				std::printf("%s\n", &errorLog[0]);
				Private::Utility::Error::FatalError("Program failed to link");
			}

			glDetachShader(m_programID, m_vertexShaderID);
			glDetachShader(m_programID, m_fragmentShaderID);

			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);
		}

		void GLSLProgram::AddAttribute(const std::string& attributeName)
		{
			glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
		}

		GLint GLSLProgram::GetUniformLocation(const std::string& uniformName)
		{
			GLint uniformLocation = glGetUniformLocation(m_programID, uniformName.c_str());

			if (uniformLocation == GL_INVALID_INDEX)
			{
				Private::Utility::Error::FatalError("Uniform " + uniformName + " not found in shader");
			}

			return uniformLocation;
		}

		void GLSLProgram::Bind()
		{
			glUseProgram(m_programID);
			for (int i = 0; i < m_numAttributes; i++)
			{
				glEnableVertexAttribArray(i);
			}
		}

		void GLSLProgram::Unbind()
		{
			glUseProgram(0);
			for (int i = 0; i < m_numAttributes; i++)
			{
				glDisableVertexAttribArray(i);
			}
		}
	}
}