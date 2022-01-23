#include "Window.hpp"

#include <glad/glad.h>
#include <SDL/SDL.h>

#include <assert.h>
#include "Window.hpp"

namespace GL
{
	Window::Window(const char* nombre, uint32_t width, uint32_t height)
	{
		assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "No se pudo inicializar SDL"); //TODO: assert deberia ser un error

		m_WindowHandle = SDL_CreateWindow(nombre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		assert(m_WindowHandle && "No se creo la ventana SDL");

		m_OpenGLContext = SDL_GL_CreateContext((SDL_Window*)m_WindowHandle);

		assert(m_OpenGLContext && "No se creo el contexto de OpenGL");

		SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		assert(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) != 0 && "No fue posible inicializar GLAD");

	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(m_OpenGLContext);

		SDL_DestroyWindow((SDL_Window*)m_WindowHandle);
		SDL_Quit();
	}

	void Window::RecibirEventos()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
				case SDL_QUIT:
					m_Corriendo = false;
					break;
			}
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
}