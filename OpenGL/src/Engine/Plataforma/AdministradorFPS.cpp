#include "AdministradorFPS.hpp"

#include <SDL/SDL.h>

namespace GL
{
	AdministradorFPS::AdministradorFPS(uint8_t fpsRequeridos) :
		m_FpsRequeridos(fpsRequeridos), m_FrameEmpieza(0), m_TiempoFrame(0)
	{
		m_EspacioFrame = ValorMilisegundos / m_FpsRequeridos;
	}

	AdministradorFPS::~AdministradorFPS()
	{
	}

	void AdministradorFPS::EmpezarFrame()
	{
		m_FrameEmpieza = SDL_GetTicks64();
	}

	void AdministradorFPS::TerminarFrame()
	{
		m_TiempoFrame = SDL_GetTicks64() - m_FrameEmpieza;

		if (m_TiempoFrame < m_EspacioFrame)
		{
			SDL_Delay(m_EspacioFrame - m_TiempoFrame);
		}
	}
}