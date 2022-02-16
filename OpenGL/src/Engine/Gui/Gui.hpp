#pragma once

namespace GL
{
	class Gui
	{
	public:
		virtual ~Gui() = default;
		Gui(const Gui& other) = delete;
		Gui& operator==(const Gui& other) = delete;

		static void Inicializar(void* windowHandle, void* glContext);
		static void Finalizar();

		static void EmpezarFrame();
		static void TerminarFrame();

		static void ManejarEventos(void* sdlEvent);
	};
}
