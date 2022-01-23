#pragma once

#include <glm/glm.hpp>

namespace GL
{
	class Renderizador
	{
	public:
		Renderizador();
		virtual ~Renderizador() = default;

		Renderizador(const Renderizador& other) = delete;
		Renderizador& operator==(const Renderizador& other) = delete;

		void Viewport(uint32_t x, uint32_t y, uint32_t ancho, uint32_t alto);
		void LimpiarPantalla(const glm::vec4& color);

	};
}
