#include "Game.hpp"

#include <glm/glm.hpp>

/*TODO:

--Camaras
--Entradas de Usuario
--Color
--Renderizador
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

	if(GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_d))
		posCuad2.x++;
	if (GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_a))
		posCuad2.x--;

}

void Game::Renderizar()
{
	m_Renderizador->Empezar(m_Camara);

	m_Renderizador->Cuad(posCuad, sclCuad, colCuad);
	m_Renderizador->Cuad(posCuad2, sclCuad2, colCuad2);

	m_Renderizador->Terminar();
}

void Game::RenderizarGui()
{
	ImGui::Begin("Fondo");
	ImGui::ColorEdit3("Color Fondo", glm::value_ptr(ColorLimpieza));
	ImGui::End();

	ImGui::Begin("Cuad");
	ImGui::Separator();
	ImGui::DragFloat2("Pos", glm::value_ptr(posCuad), 1.0f, -500.0f, 500.0f);
	ImGui::DragFloat2("Escala", glm::value_ptr(sclCuad), 0.1f, 0.5f, 3.0f);
	ImGui::ColorEdit4("Color", glm::value_ptr(colCuad));
	ImGui::End();
}
