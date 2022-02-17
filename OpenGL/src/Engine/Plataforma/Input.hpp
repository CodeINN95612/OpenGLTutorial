#pragma once

#include "TecladoTecla.hpp"
#include "MouseBoton.hpp"

namespace GL
{
	class Input
	{
	public:
		virtual ~Input() = default;

		Input(const Input& other) = delete;
		Input& operator==(const Input& other) = delete;

		//static void Inicializar();

		static void SetEstadoMouse(uint8_t btn, bool presionado);
		static void SetEstadoTeclado(uint32_t tecla, bool presionado);

		static bool GetEstadoMouse(MouseBoton btn);
		static bool GetEstadoTeclado(TecladoTecla btn);
	};
}
