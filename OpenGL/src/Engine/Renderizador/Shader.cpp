#include "Shader.hpp"

#include <glad/glad.h>

#include "Utils/Archivo.hpp"

#include <assert.h>

namespace GL
{
	Shader::Shader(const char* vertexShader, const char* fragmentShader)
	{
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		m_Programa = glCreateProgram();

		glShaderSource(m_VertexShader, 1, &vertexShader, nullptr);
		glShaderSource(m_FragmentShader, 1, &fragmentShader, nullptr);

		glCompileShader(m_VertexShader);
		glCompileShader(m_FragmentShader);

		glAttachShader(m_Programa, m_VertexShader);
		glAttachShader(m_Programa, m_FragmentShader);

		glLinkProgram(m_Programa);
		Bind();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Programa);
		glDeleteShader(m_FragmentShader);
		glDeleteShader(m_VertexShader);
	}

	std::shared_ptr<Shader> Shader::DesdeArchivo(const char* archivoVertexShader, const char* archivoFragmentShader)
	{
		char* vertexShader = nullptr;
		char* fragmentShader = nullptr;

		assert(Archivo::Leer(archivoVertexShader, &vertexShader) && "No se pudo abrir el archivo del vertex shader");
		assert(Archivo::Leer(archivoFragmentShader, &fragmentShader) && "No se pudo abrir el archivo del fragment shader");

		std::shared_ptr<Shader> retorno = std::make_shared<Shader>(vertexShader, fragmentShader);

		Archivo::Liberar(vertexShader);
		Archivo::Liberar(fragmentShader);

		return retorno;
	}

	void Shader::Bind()
	{
		glUseProgram(m_Programa);
	}

	void Shader::Uniform4f(const char* nombre, const glm::vec4& valores)
	{
		int32_t location = GetUniformLocation(nombre);
		glUniform4f(location, valores.r, valores.g, valores.b, valores.a);
	}

	int32_t Shader::GetUniformLocation(const char* nombre)
	{
		Bind();
		int32_t location = glGetUniformLocation(m_Programa, nombre);
		assert(location > -1 && "No fue posible encontrar el Uniform");
		return location;
	}
}