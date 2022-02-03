#pragma once

#include "Window.hpp"

#include <memory>

class Game
{
public:
	inline static constexpr const char* Nombre = "Juego de Prueba";
	inline static constexpr const uint32_t Ancho = 800;
	inline static constexpr const uint32_t Alto = 600;

public:
	Game();
	virtual ~Game() = default;

	Game(const Game& other) = delete;
	Game& operator==(const Game& other) = delete;

	void Run();

private:
	std::unique_ptr<GL::Window> m_Window{};
	std::unique_ptr<GL::Renderizador> m_Renderizador{};

	uint32_t m_ObjetoProgramaShader;

private:
	void ManejarEntradaDeUsuario();
	void Actualizar();
	void Renderizar();
};