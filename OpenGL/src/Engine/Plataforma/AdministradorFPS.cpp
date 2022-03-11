#include "AdministradorFPS.hpp"

#include <SDL/SDL.h>

namespace GL
{
	AdministradorFPS::AdministradorFPS(float fpsRequeridos) :
		m_FpsRequeridos(fpsRequeridos), m_FrameEmpieza(0.0f), m_TiempoFrame(0.0f)
	{
		m_EspacioFrame = double(ValorMilisegundos / m_FpsRequeridos);
	}

	AdministradorFPS::~AdministradorFPS()
	{
	}

	void AdministradorFPS::EmpezarFrame()
	{
		m_FrameEmpieza = double(SDL_GetTicks64());
	}

	double AdministradorFPS::TerminarFrame()
	{
		m_TiempoFrame = double(SDL_GetTicks64()) - m_FrameEmpieza;

		if (m_TiempoFrame < m_EspacioFrame)
		{
			SDL_Delay(uint32_t(m_EspacioFrame - m_TiempoFrame));
			m_TiempoFrame = m_EspacioFrame;
		}

		return double(ValorMilisegundos / m_TiempoFrame);
	}
}