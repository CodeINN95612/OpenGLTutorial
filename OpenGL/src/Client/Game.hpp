#pragma once

#include "Window.hpp"
#include "Renderizador/VertexArray.hpp"
#include "Renderizador/Shader.hpp"
#include "Renderizador/Textura.hpp"

#include <memory>

class Game
{
public:
	inline static constexpr const char* Nombre = "Juego de Prueba";
	inline static constexpr const uint32_t Ancho = 800;
	inline static constexpr const uint32_t Alto = 600;

public:
	Game();
	virtual ~Game();

	Game(const Game& other) = delete;
	Game& operator==(const Game& other) = delete;

	void Run();

private:
	std::unique_ptr<GL::Window> m_Window{};
	std::unique_ptr<GL::Renderizador> m_Renderizador{};

	std::shared_ptr<GL::Textura> m_Textura;
	std::shared_ptr<GL::Textura> m_TexturaVentana;
	std::shared_ptr<GL::Shader> m_Shader;
	std::unique_ptr<GL::VertexArray> m_VertexArray;

private:
	void ManejarEntradaDeUsuario();
	void Actualizar();
	void Renderizar();
};