#include "Game.hpp"

#include <glm/glm.hpp>

#include <glad/glad.h>


Game::Game()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();

	CrearShader();

	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

		 0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
	};

	uint8_t indices[] = {
		0, 1, 2, 
		0, 2, 3
	};

	GL::VertexArray::Atributo atributos[] =
	{
		{0, GL::VertexArray::TipoAtributo::Float2},
		{1, GL::VertexArray::TipoAtributo::Float3},
	};

	std::shared_ptr<GL::VertexBuffer> vertexBuffer = std::make_shared<GL::VertexBuffer>(sizeof(vertices) / sizeof(vertices[0]), vertices);
	std::shared_ptr<GL::IndexBuffer> indexBuffer = std::make_shared<GL::IndexBuffer>(sizeof(indices) / sizeof(indices[0]), indices);

	m_VertexArray = std::make_unique<GL::VertexArray>(atributos, sizeof(atributos) / sizeof(atributos[0]));
	m_VertexArray->SetDataBuffer(vertexBuffer, indexBuffer);
}

Game::~Game()
{
	LimpiarShader();
}

void Game::Run()
{
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
	m_Renderizador->LimpiarPantalla(glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ));

	//////////////////////
	glUseProgram(m_ObjetoProgramaShader);
	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetDrawCount(), GL_UNSIGNED_BYTE, nullptr);
	////////////////////

	m_Window->Cambiar();
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
