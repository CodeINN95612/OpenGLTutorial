#pragma once

#include "Renderizador/Renderizador.hpp"
#include "Eventos/IManejadorDeEventos.hpp"

#include "Plataforma/MouseBotones.hpp"

#include <cstdint>
#include <memory>

namespace GL
{
	class Window
	{
	public:
		Window(const char* nombre, uint32_t width, uint32_t height);
		virtual ~Window();

		Window(const Window& other) = delete;
		Window& operator==(const Window& other) = delete;

		inline bool Corriendo() const { return m_Corriendo; }
		inline void Cerrar() { m_Corriendo = false; }

		void ManejarEventos(const IManejadorDeEventos& manejadorEventos);
		void Cambiar();

		std::unique_ptr<Renderizador> CrearRenderizador();

	private:
		void* m_WindowHandle = nullptr;
		void* m_OpenGLContext = nullptr;
		bool m_Corriendo = true;
	};
}
