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
	inline static constexpr const uint32_t Ancho = 1000;
	inline static constexpr const uint32_t Alto = 720;

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
	glm::vec4 ColorLimpieza{ 0.2f, 0.2f, 0.2f, 1.0f};

	std::vector<std::shared_ptr<GL::ObjetoJuego>> m_Objetos{};
	std::shared_ptr<GL::ObjetoJuego> m_Jugador = GL::ObjetoJuego::Crear("Jugador1");
	float velH = 15.0f;
	float velV = 0.0f;
	float g = 3.0f;
	bool salto = false;
	bool enSuelo = false;

	float m_FPS = 60.0f;

private:
	void ManejarEntradaDeUsuario();
	void Actualizar();
	void Renderizar();
	void RenderizarGui();
};