#pragma once

#include "ManejadorEventosJuego.hpp"

#include <Engine/Engine.hpp>
#include <memory>

class Game
{
	friend class ManejadorEventosJuego;
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
	ManejadorEventosJuego m_ManejadorDeEventos;

	std::unique_ptr<GL::Renderizador> m_Renderizador{};

	GL::CamaraOrtografica m_Camara{ Ancho / 3.0f, Alto / 3.0f, {0.0f, 0.0f, -10.0f} };
	glm::vec4 ColorLimpieza{ 0.1f, 0.1f, 0.1f, 1.0f};

	glm::vec2 posCuad{ 0.0f, 0.0f };
	glm::vec2 sclCuad{ 1.0f, 1.0f };
	glm::vec4 colCuad = GL::Color::Vec::Blanco;


	glm::vec2 posCuad2{ 0.0f, 0.0f };
	glm::vec2 sclCuad2{ 1.0f, 1.0f };
	glm::vec4 colCuad2 = GL::Color::Vec::Gris50;

private:
	void ManejarEntradaDeUsuario();
	void Actualizar();
	void Renderizar();
	void RenderizarGui();
};