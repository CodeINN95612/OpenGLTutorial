#include "Game.hpp"

void Game::Run()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

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
	//dibujar triangulo
}
