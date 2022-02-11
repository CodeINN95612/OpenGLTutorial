#include "Game.hpp"

#include <glm/glm.hpp>

#include <glad/glad.h>

#include "Utils/Archivo.hpp"


Game::Game()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();

	m_Shader = GL::Shader::DesdeArchivo("./assets/shaders/Basic.vert", "./assets/shaders/Basic.frag");

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
	m_Shader->Bind();
	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetDrawCount(), GL_UNSIGNED_BYTE, nullptr);
	////////////////////

	m_Window->Cambiar();
}