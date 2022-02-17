#include "ManejadorEventosJuego.hpp"

#include "Game.hpp"
#include "Engine/Plataforma/Logger.hpp"

void ManejadorEventosJuego::EventoPantallaCerrar() const
{
	m_Juego.m_Window->Cerrar();
}

void ManejadorEventosJuego::EventoPantallaMover(int32_t x, int32_t y) const
{
}

void ManejadorEventosJuego::EventoPantallaCambiarDimension(int32_t ancho, int32_t alto) const
{
	if (ancho != 0 && alto != 0)
	{
		m_Juego.m_Renderizador->Viewport(0, 0, ancho, alto);
		m_Juego.m_Camara.CambioDimensiones(ancho/3.0f, alto/3.0f);
	}
}

void ManejadorEventosJuego::EventoMouseMover(int32_t x, int32_t y) const
{
}

void ManejadorEventosJuego::EventoMousePresionarBoton(int32_t x, int32_t y, uint8_t clicks, GL::MouseBoton boton) const
{
}

void ManejadorEventosJuego::EventoMouseLiberarBoton(int32_t x, int32_t y, GL::MouseBoton boton) const
{
}

void ManejadorEventosJuego::EventoMouseMoverRueda(int32_t xOffset, int32_t yOffset) const
{
}

void ManejadorEventosJuego::EventoTecladoPresionarTecla(GL::TecladoTecla tecla, bool repetido) const
{
}

void ManejadorEventosJuego::EventoTecladoLiberarTecla(GL::TecladoTecla tecla) const
{
}

void ManejadorEventosJuego::EventoTecladoEscribir(char* caracter) const
{

}
