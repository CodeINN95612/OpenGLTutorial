#pragma once

#include <cstdint>

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

		void RecibirEventos();

	private:
		void* m_WindowHandle = nullptr;
		bool m_Corriendo = true;
	};
}
