#pragma once

#include "ManejadorEventosJuego.hpp"

#include <Engine/Engine.hpp>
#include <memory>
#include <vector>

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

	GL::AdministradorFPS m_AdministradorFps{ 60 };

	std::unique_ptr<GL::Renderizador> m_Renderizador{};

	GL::CamaraOrtografica m_Camara{ float(Ancho), float(Alto), {0.0f, 0.0f, -10.0f} };
	glm::vec4 ColorLimpieza{ 0.0f, 0.0f, 0.0f, 1.0f};

	std::vector<GL::ObjetoJuego> m_Objetos{};

private:
	void ManejarEntradaDeUsuario();
	void Actualizar();
	void Renderizar();
	void RenderizarGui();
};