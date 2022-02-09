#include "Game.hpp"

#include <glm/glm.hpp>

#include <glad/glad.h>

Game::Game()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();

	CrearShader();

	float vertices[] = {
		 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};

	glCreateBuffers(1, &m_ObjetoVertexBuffer);
	glNamedBufferStorage(m_ObjetoVertexBuffer, sizeof(vertices), vertices, GL_MAP_WRITE_BIT /* GL_DYNAMIC_STORAGE_BIT*/);

	//Crear Vertex Arrays
	glCreateVertexArrays(1, &m_ObjetoVertexArray);

	glVertexArrayVertexBuffer(m_ObjetoVertexArray, 0, m_ObjetoVertexBuffer, 0, 5 * sizeof(float));

	glEnableVertexArrayAttrib(m_ObjetoVertexArray, 0);
	glEnableVertexArrayAttrib(m_ObjetoVertexArray, 1);

	glVertexArrayAttribFormat(m_ObjetoVertexArray, 0, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(float));
	glVertexArrayAttribFormat(m_ObjetoVertexArray, 1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	
	glVertexArrayAttribBinding(m_ObjetoVertexArray, 0, 0);
	glVertexArrayAttribBinding(m_ObjetoVertexArray, 1, 0);
	
}

Game::~Game()
{
	glDeleteVertexArrays(1, &m_ObjetoVertexArray);
	glDeleteBuffers(1, &m_ObjetoVertexBuffer);

	LimpiarShader();
}

void Game::Run()
{
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	while (m_Window->Corriendo())
	{
		ManejarEntradaDeUsuario();

		Actualizar();

		Renderizar();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->RecibirEventos();

	//si aplasto arriba, subir x

}

void Game::Actualizar()
{
	//poner coordenada = x
}

void Game::Renderizar()
{
	static float an = 0.0f;

	float r = glm::sin(glm::radians(an)) * 0.5f + 0.5f;
	float g = glm::sin(2 * glm::radians(an)) * 0.5f + 0.5f;
	float b = glm::cos(glm::radians(an)) * 0.5f + 0.5f;

	m_Renderizador->LimpiarPantalla(glm::vec4( r, g, b, 1.0f ));

	//////////////////////
	glUseProgram(m_ObjetoProgramaShader);
	glBindVertexArray(m_ObjetoVertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	////////////////////

	m_Window->Cambiar();

	an += 180.0f / 360.0f;
}

void Game::CrearShader()
{
	const char* vertexShader =
		"#version 450 core\n"
		"layout (location = 0) in vec2 vPosition;\n"
		"layout (location = 1) in vec3 vColor;\n"
		"out vec3 iColor;\n"
		"void main(){\n"
		"	gl_Position = vec4(vPosition, 1.0f, 1.0f);\n"
		"	iColor = vColor;\n"
		"}\n\0";

	const char* fragmentShader =
		"#version 450 core\n"
		"in vec3 iColor;\n"
		"out vec4 fColor;\n"
		"void main(){\n"
		"	fColor = vec4(iColor, 1.0f);\n"
		"}\n\0";

	//Crear Objetos Shader de OpenGL
	m_ObjetoVertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_ObjetoFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Subir string al objeto
	glShaderSource(m_ObjetoVertexShader, 1, &vertexShader, nullptr);
	glShaderSource(m_ObjetoFragmentShader, 1, &fragmentShader, nullptr);

	//Compilar programa
	glCompileShader(m_ObjetoVertexShader);
	glCompileShader(m_ObjetoFragmentShader);

	//Crear un objeto programa de opengl
	m_ObjetoProgramaShader = glCreateProgram();

	//Enviar Archivos compilados al programa
	glAttachShader(m_ObjetoProgramaShader, m_ObjetoVertexShader);
	glAttachShader(m_ObjetoProgramaShader, m_ObjetoFragmentShader);

	//Link (Union de Archivos compilados)
	glLinkProgram(m_ObjetoProgramaShader);
}

void Game::LimpiarShader()
{
	glDeleteProgram(m_ObjetoProgramaShader);
	glDeleteShader(m_ObjetoVertexShader);
	glDeleteShader(m_ObjetoFragmentShader);
}
