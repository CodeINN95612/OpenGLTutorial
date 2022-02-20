#include "Window.hpp"
#include "Engine/Plataforma/Assert.hpp"
#include "Logger.hpp"
#include "Engine/Gui/Gui.hpp"
#include "Input.hpp"

#include <glad/glad.h>
#include <SDL/SDL.h>

namespace GL
{
	static void GestinarEvento(SDL_Event& e, const IManejadorDeEventos& manejadorEventos, bool bloqueaMouseTeclado);

	Window::Window(const char* nombre, uint32_t width, uint32_t height)
	{
		Logger::Inicializar();
		GL_ASSERT(SDL_Init(SDL_INIT_EVERYTHING) == 0, "No se pudo inicializar SDL"); //TODO: assert deberia ser un error

		m_WindowHandle = SDL_CreateWindow(nombre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		GL_ASSERT(m_WindowHandle, "No se creo la ventana SDL");

		m_OpenGLContext = SDL_GL_CreateContext((SDL_Window*)m_WindowHandle);

		GL_ASSERT(m_OpenGLContext, "No se creo el contexto de OpenGL");

		//SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		GL_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) != 0, "No fue posible inicializar GLAD");

		Gui::Inicializar(m_WindowHandle, m_OpenGLContext);
	}

	Window::~Window()
	{
		Gui::Finalizar();

		SDL_GL_DeleteContext(m_OpenGLContext);

		SDL_DestroyWindow((SDL_Window*)m_WindowHandle);
		SDL_Quit();
		Logger::Finalizar();
	}

	void Window::ManejarEventos(const IManejadorDeEventos& manejadorEventos)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			bool bloqueo = Gui::ManejarEventos(&e);
			GestinarEvento(e, manejadorEventos, bloqueo);
		}
	}

	void Window::Cambiar()
	{
		SDL_GL_SwapWindow((SDL_Window*)m_WindowHandle);
	}

	std::unique_ptr<Renderizador> Window::CrearRenderizador()
	{
		return std::make_unique<Renderizador>();
	}

	//Eventos
	void GestinarEvento(SDL_Event& e, const IManejadorDeEventos& manejadorEventos, bool bloqueaMouseTeclado)
	{
		switch (e.type)
		{
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_TEXTINPUT:
				if (bloqueaMouseTeclado) return;
		}

		switch (e.type)
		{
			//Ventana
			case SDL_QUIT:
				manejadorEventos.EventoPantallaCerrar();
				break;
			case SDL_WINDOWEVENT:

				switch (e.window.event)
				{
					case SDL_WINDOWEVENT_MOVED:
						manejadorEventos.EventoPantallaMover(e.window.data1, e.window.data2);
						break;

					case SDL_WINDOWEVENT_RESIZED:
						manejadorEventos.EventoPantallaCambiarDimension(e.window.data1, e.window.data2);
						break;

					case SDL_WINDOWEVENT_MINIMIZED:
						manejadorEventos.EventoPantallaCambiarDimension(0, 0);
						break;

					case SDL_WINDOWEVENT_MAXIMIZED:
						manejadorEventos.EventoPantallaCambiarDimension(e.window.data1, e.window.data2);
						break;

				}
				break;

			//Mouse
			case SDL_MOUSEMOTION:
				manejadorEventos.EventoMouseMover(e.motion.x, e.motion.y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				Input::SetEstadoMouse(e.button.button, true);
				manejadorEventos.EventoMousePresionarBoton(e.button.x, e.button.y, e.button.clicks, (MouseBoton)e.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				Input::SetEstadoMouse(e.button.button, false);
				manejadorEventos.EventoMouseLiberarBoton(e.button.x, e.button.y, (MouseBoton)e.button.button);
				break;

			case SDL_MOUSEWHEEL:
				manejadorEventos.EventoMouseMoverRueda(e.wheel.x, e.wheel.y);
				break;

			//Teclado
			case SDL_KEYDOWN :
				Input::SetEstadoTeclado(e.key.keysym.sym, true);
				manejadorEventos.EventoTecladoPresionarTecla((TecladoTecla)e.key.keysym.sym, e.key.repeat);
				break;

			case SDL_KEYUP :
				Input::SetEstadoTeclado(e.key.keysym.sym, false);
				manejadorEventos.EventoTecladoLiberarTecla((TecladoTecla)e.key.keysym.sym);
				break;

			case SDL_TEXTINPUT:
				manejadorEventos.EventoTecladoEscribir(e.text.text);
				break;
		}
	}
}
