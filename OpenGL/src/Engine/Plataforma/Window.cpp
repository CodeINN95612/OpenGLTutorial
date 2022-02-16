#include "Window.hpp"
#include "Engine/Plataforma/Assert.hpp"
#include "Logger.hpp"

#include <glad/glad.h>
#include <SDL/SDL.h>

#include "Engine/Libs/imgui/imgui.h"
#include "Engine/Libs/imgui/imgui_impl_sdl.h"
#include "Engine/Libs/imgui/imgui_impl_opengl3.h"

namespace GL
{
	static void GestinarEvento(SDL_Event& e, const IManejadorDeEventos& manejadorEventos);

	Window::Window(const char* nombre, uint32_t width, uint32_t height)
	{
		Logger::Inicializar();
		GL_ASSERT(SDL_Init(SDL_INIT_EVERYTHING) == 0, "No se pudo inicializar SDL"); //TODO: assert deberia ser un error

		m_WindowHandle = SDL_CreateWindow(nombre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		GL_ASSERT(m_WindowHandle, "No se creo la ventana SDL");

		m_OpenGLContext = SDL_GL_CreateContext((SDL_Window*)m_WindowHandle);

		GL_ASSERT(m_OpenGLContext, "No se creo el contexto de OpenGL");

		SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		GL_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) != 0, "No fue posible inicializar GLAD");


		//////////////////////////////////////////////////////
		 // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)m_WindowHandle, m_OpenGLContext);
		ImGui_ImplOpenGL3_Init("#version 450 core");

	}

	Window::~Window()
	{
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
			ImGui_ImplSDL2_ProcessEvent(&e);
			GestinarEvento(e, manejadorEventos);
		}
	}

	void Window::Cambiar()
	{
		SDL_GL_SwapWindow((SDL_Window*)m_WindowHandle);
	}

	void Window::GuiEjemplo()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		//////

		ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar |*/ ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("Dockspace GL", nullptr, window_flags);

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::Begin("Ejemplo");
		static float arr[4] = {};
		ImGui::ColorPicker4("Colores", arr);
		ImGui::End();

		ImGui::End();

		/////

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}

	std::unique_ptr<Renderizador> Window::CrearRenderizador()
	{
		return std::make_unique<Renderizador>();
	}

	//Eventos
	void GestinarEvento(SDL_Event& e, const IManejadorDeEventos& manejadorEventos)
	{
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
				manejadorEventos.EventoMousePresionarBoton(e.button.x, e.button.y, e.button.clicks, (MouseBoton)e.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				manejadorEventos.EventoMouseLiberarBoton(e.button.x, e.button.y, (MouseBoton)e.button.button);
				break;

			case SDL_MOUSEWHEEL:
				manejadorEventos.EventoMouseMoverRueda(e.wheel.x, e.wheel.y);
				break;

			//Teclado
			case SDL_KEYDOWN :
				manejadorEventos.EventoTecladoPresionarTecla((TecladoTecla)e.key.keysym.sym, e.key.repeat);
				break;

			case SDL_KEYUP :
				manejadorEventos.EventoTecladoLiberarTecla((TecladoTecla)e.key.keysym.sym);
				break;

			case SDL_TEXTINPUT:
				manejadorEventos.EventoTecladoEscribir(e.text.text);
				break;
		}
	}
}
