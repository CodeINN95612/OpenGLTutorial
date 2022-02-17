#include "Input.hpp"

#include <map>

namespace GL
{
	static std::map <uint8_t, bool> s_EstadosMouse{};
	static std::map <uint32_t, bool> s_EstadosTeclado{};

	/*void Input::Inicializar()
	{
	}*/

	void Input::SetEstadoMouse(uint8_t btn, bool presionado)
	{
		s_EstadosMouse[btn] = presionado;
	}

	void Input::SetEstadoTeclado(uint32_t tecla, bool presionado)
	{
		s_EstadosTeclado[tecla] = presionado;
	}

	bool Input::GetEstadoMouse(MouseBoton btn)
	{
		if (s_EstadosMouse.find((uint8_t)btn) == s_EstadosMouse.end())
			return false;

		return s_EstadosMouse[(uint8_t)btn];
	}

	bool Input::GetEstadoTeclado(TecladoTecla btn)
	{
		if (s_EstadosTeclado.find((uint32_t)btn) == s_EstadosTeclado.end())
			return false;

		return s_EstadosTeclado[(uint32_t)btn];
	}

}