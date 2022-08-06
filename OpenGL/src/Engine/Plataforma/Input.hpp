#pragma once

#include <glm/glm.hpp>

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
		static void SetPosMouse(glm::vec2 pos);

		static bool GetEstadoMouse(MouseBoton btn);
		static glm::vec2 GetPosMouse();
		static bool GetEstadoTeclado(TecladoTecla btn);
	};
}
