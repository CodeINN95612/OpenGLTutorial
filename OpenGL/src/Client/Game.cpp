#include "Game.hpp"

#include <glm/glm.hpp>

/*TODO:

----Camaras
Entradas de Usuario
Renderizador
Objetos de Juego (GameObjetcs)
Escenas
Sistemas
etc....

*/


Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	m_Textura = GL::Textura::DesdeArchivo("./assets/img/peloNaranja16x16.png");
	//m_Textura = GL::Textura::DesdeColor(GL::Color::Hex::Magenta);
	m_TexturaVentana = GL::Textura::DesdeArchivo("./assets/img/ventana16x16.png");

	m_Shader = GL::Shader::DesdeArchivo("./assets/shaders/Basic.vert", "./assets/shaders/Basic.frag");
	m_Shader->UniformTextura("uTextura", 0);

	float vertices[] = {
		-0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
	};

	uint8_t indices[] = {
		0, 1, 2, 
		0, 2, 3
	};

	GL::VertexArray::Atributo atributos[] =
	{
		{0, GL::VertexArray::TipoAtributo::Float2},
		{1, GL::VertexArray::TipoAtributo::Float2},
	};

	std::shared_ptr<GL::VertexBuffer> vertexBuffer = std::make_shared<GL::VertexBuffer>((uint32_t)(sizeof(vertices) / sizeof(vertices[0])), vertices);
	std::shared_ptr<GL::IndexBuffer> indexBuffer = std::make_shared<GL::IndexBuffer>((uint32_t)(sizeof(indices) / sizeof(indices[0])), indices);

	m_VertexArray = std::make_unique<GL::VertexArray>(atributos, (uint32_t)(sizeof(atributos) / sizeof(atributos[0])));
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
		m_Renderizador->LimpiarPantalla(ColorLimpieza);

		ManejarEntradaDeUsuario();

		Actualizar();

		Renderizar();

		GL::Gui::EmpezarFrame();
		RenderizarGui();
		GL::Gui::TerminarFrame();

		m_Window->Cambiar();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->ManejarEventos(m_ManejadorDeEventos);

	//si aplasto arriba, subir x

}

void Game::Actualizar()
{
	m_Camara.Actualizar();
}

void Game::Renderizar()
{

	//////////////////////
	m_Shader->UniformMat4("uVistaProyeccion", m_Camara.GetMatrixVistaProyeccion());
	m_Shader->Uniform1f("uEscala", m_Escala);

	m_Textura->Bind(0);
	m_Shader->Bind();
	m_VertexArray->Bind();
	m_Renderizador->Dibujar(m_VertexArray.get());

	m_TexturaVentana->Bind(0);
	//m_Renderizador->Dibujar(m_VertexArray.get());
	////////////////////

}

void Game::RenderizarGui()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit3("Color Fondo", glm::value_ptr(ColorLimpieza));
	ImGui::Separator();
	ImGui::DragFloat("escala", &m_Escala, 5.0f, 1.0f, 500.0f);
	ImGui::End();
}
