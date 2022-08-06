#pragma once

#include "Engine/Eventos/IManejadorDeEventos.hpp"

class Game;

class ManejadorEventosJuego : public GL::IManejadorDeEventos
{
public:
	ManejadorEventosJuego(Game* juego) : m_Juego(juego) {}
	virtual ~ManejadorEventosJuego() = default;

	ManejadorEventosJuego(const ManejadorEventosJuego& other) = delete;
	ManejadorEventosJuego& operator==(const ManejadorEventosJuego& other) = delete;

	//Eventos de Pantalla
	virtual void EventoPantallaCerrar() const override;
	virtual void EventoPantallaMover(int32_t x, int32_t y) const override;
	virtual void EventoPantallaCambiarDimension(int32_t ancho, int32_t alto) const override;

	//Eventos de Mouse
	virtual void EventoMouseMover(int32_t x, int32_t y) const override;
	virtual void EventoMousePresionarBoton(int32_t x, int32_t y, uint8_t clicks, GL::MouseBoton boton) const override;
	virtual void EventoMouseLiberarBoton(int32_t x, int32_t y, GL::MouseBoton boton) const override;
	virtual void EventoMouseMoverRueda(int32_t xOffset, int32_t yOffset) const override;

	//Eventos de Teclado
	virtual void EventoTecladoPresionarTecla(GL::TecladoTecla tecla, bool repetido) const override;
	virtual void EventoTecladoLiberarTecla(GL::TecladoTecla tecla) const override;
	virtual void EventoTecladoEscribir(char* caracter) const override;


private:
	Game* m_Juego;
};