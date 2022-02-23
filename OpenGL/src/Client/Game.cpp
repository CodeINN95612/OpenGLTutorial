#include "Game.hpp"

#include <glm/glm.hpp>

Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	m_Jugador.etiqueta.etiqueta = "Jugador";
	m_Jugador.sprite.color = GL::Color::Vec::Rojo;
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
		m_AdministradorFps.EmpezarFrame();

		m_Renderizador->LimpiarPantalla(ColorLimpieza);

		ManejarEntradaDeUsuario();

		Actualizar();

		Renderizar();

		GL::Gui::EmpezarFrame();
		RenderizarGui();
		GL::Gui::TerminarFrame();

		m_Window->Cambiar();

		m_AdministradorFps.TerminarFrame();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->ManejarEventos(m_ManejadorDeEventos);
}

void Game::Actualizar()
{
	m_Camara.Actualizar();

	m_Jugador.tranform.posicion.y -= velV;
	if (m_Jugador.tranform.posicion.y < -150.0f)
	{
		velV = 0;
		m_Jugador.tranform.posicion.y = -150.0f;
	}
	else
	{
		velV += g;
	}

	if(m_Jugador.tranform.posicion.y > -150.0f)
		enSuelo = false;
	else
		enSuelo = true;

		

	if(GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_d))
		m_Jugador.tranform.posicion.x += velH;
	if (GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_a))
		m_Jugador.tranform.posicion.x -= velH;

	if (GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_w))
	{
		if(!salto && enSuelo)
			velV = -25;
		salto = true;
	}
	else
		salto = false;


}

void Game::Renderizar()
{
	m_Renderizador->Empezar(m_Camara);

	m_Renderizador->Cuad(m_Jugador.tranform, m_Jugador.sprite);

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

	/*ImGui::Begin("Objetos");
	for (GL::ObjetoJuego& objeto : m_Objetos)
	{
		ImGui::Text("Objeto %i:, %s", objeto.uuid, objeto.etiqueta.etiqueta.c_str());
	}
	ImGui::End();*/
}
