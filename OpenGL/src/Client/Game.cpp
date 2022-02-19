#include "Game.hpp"

#include <glm/glm.hpp>

/*TODO:

--Camaras
--Entradas de Usuario
--Color
--Renderizador
--Objetos de Juego (GameObjetcs)


Sistemas
Escenas
etc....

*/


Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	for (int i = 0; i < 10; i++)
	{
		GL::ObjetoJuego nuevo = GL::ObjetoJuego::Crear();
		nuevo.etiqueta.etiqueta = "Objeto No. " + std::to_string(i);

		nuevo.tranform.posicion = { i * 15, i * 15 };
		nuevo.tranform.escala = { (i + 1.0f) / 10.0f, (i + 1.0f) / 10.0f };
		nuevo.tranform.anguloRotacion = i * 36.0f;

		nuevo.sprite.color = glm::vec4(i * 0.1f, 0.5f, 0.5f, 1.0f);
		m_Objetos.push_back(nuevo);
	}
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
	m_Renderizador->Empezar(m_Camara);

	for (GL::ObjetoJuego objeto : m_Objetos)
	{
		m_Renderizador->Cuad(objeto.tranform, objeto.sprite);
	}

	m_Renderizador->Terminar();
}

void Game::RenderizarGui()
{
	ImGui::Begin("Fondo");
	ImGui::ColorEdit3("Color Fondo", glm::value_ptr(ColorLimpieza));
	ImGui::End();

	ImGui::Begin("Objetos");
	for (GL::ObjetoJuego& objeto : m_Objetos)
	{
		ImGui::Text("Objeto %i:, %s", objeto.uuid, objeto.etiqueta.etiqueta.c_str());
	}
	ImGui::End();
}
