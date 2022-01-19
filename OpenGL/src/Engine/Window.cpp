#include "Window.h"

#include <SDL/SDL.h>

#include <assert.h>

namespace GL
{
	Window::Window(const char* nombre, uint32_t width, uint32_t height)
	{
		assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "No se pudo inicializar SDL"); //TODO: assert deberia ser un error

		m_WindowHandle = SDL_CreateWindow(nombre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		assert(m_WindowHandle && "No se creo la ventana SDL");
	}

	Window::~Window()
	{
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
}