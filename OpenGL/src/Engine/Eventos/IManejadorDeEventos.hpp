#pragma once

#include <cstdint>
#include "Plataforma/MouseBotones.hpp"
#include "Plataforma/TecladoTecla.hpp"

namespace GL
{
	class IManejadorDeEventos
	{
	public:
		//Eventos de Pantalla
		virtual void EventoPantallaCerrar() const = 0;
		virtual void EventoPantallaMover(int32_t x, int32_t y) const = 0;
		virtual void EventoPantallaCambiarDimension(int32_t ancho, int32_t alto) const = 0;

		//Eventos de Mouse
		virtual void EventoMouseMover(int32_t x, int32_t y) const = 0;
		virtual void EventoMousePresionarBoton(int32_t x, int32_t y, uint8_t clicks, MouseBoton boton) const = 0;
		virtual void EventoMouseLiberarBoton(int32_t x, int32_t y, MouseBoton boton) const = 0;
		virtual void EventoMouseMoverRueda(int32_t xOffset, int32_t yOffset) const = 0;

		//Eventos de Teclado
		virtual void EventoTecladoPresionarTecla(TecladoTecla tecla, bool repetido) const = 0;
		virtual void EventoTecladoLiberarTecla(TecladoTecla tecla) const = 0;
		virtual void EventoTecladoEscribir(char* caracter) const = 0;
	};
}
