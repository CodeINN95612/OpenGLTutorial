#include "Shader.hpp"
#include "Engine/Utils/Archivo.hpp"
#include "Engine/Plataforma/Assert.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


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
		std::string vertexShader = Archivo::Leer(archivoVertexShader);
		std::string fragmentShader = Archivo::Leer(archivoFragmentShader);

		GL_ASSERT(!vertexShader.empty(), "No se pudo abrir el archivo del vertex shader");
		GL_ASSERT(!vertexShader.empty(), "No se pudo abrir el archivo del fragment shader");

		std::shared_ptr<Shader> retorno = std::make_shared<Shader>(vertexShader.c_str(), fragmentShader.c_str());

		return retorno;
	}

	void Shader::Bind()
	{
		glUseProgram(m_Programa);
	}

	void Shader::Uniform1f(const char* nombre, float val)
	{
		int32_t location = GetUniformLocation(nombre);
		glUniform1f(location, val);
	}

	void Shader::Uniform4f(const char* nombre, const glm::vec4& valores)
	{
		int32_t location = GetUniformLocation(nombre);
		glUniform4f(location, valores.r, valores.g, valores.b, valores.a);
	}

	void Shader::UniformMat4(const char* nombre, const glm::mat4& valores)
	{
		int32_t location = GetUniformLocation(nombre);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(valores));
	}

	void Shader::UniformTextura(const char* nombre, int val)
	{
		int32_t location = GetUniformLocation(nombre);
		glUniform1i(location, val);
	}

	int32_t Shader::GetUniformLocation(const char* nombre)
	{
		Bind();
		int32_t location = glGetUniformLocation(m_Programa, nombre);
		GL_ASSERT(location > -1, "No fue posible encontrar el Uniform");
		return location;
	}
}