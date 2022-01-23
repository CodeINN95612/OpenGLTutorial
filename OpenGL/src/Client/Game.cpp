#include "Game.hpp"

#include <glm/glm.hpp>

#include <glad/glad.h>

void Game::Run()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();

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

	m_Window->Cambiar();

	an += 180.0f / 360.0f;
}
