#include "Game.hpp"

#include <glm/glm.hpp>

#include "Paneles/PanelObjetos.hpp"

Game::Game() :
	m_ManejadorDeEventos(this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	ImageBuffer = new uint32_t[Ancho * Alto];
	for (uint32_t i = 0; i < Ancho * Alto; i++)
	{
		ImageBuffer[i] = 0xff000000;
	}

	GL::AdministradorRecursos::CargarTextura("PeloNaranja", GL::Textura::DesdeArchivo("./assets/img/peloNaranja16x16.png"));
	GL::AdministradorRecursos::CargarTextura("Suelo", GL::Textura::DesdeArchivo("./assets/img/ventana16x16.png"));

}

Game::~Game()
{
	delete[] ImageBuffer;
}

void Game::Run()
{
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (m_Window->Corriendo())
	{
		m_AdministradorFps.EmpezarFrame();

		//m_Renderizador->LimpiarPantalla(ColorLimpieza);
		m_Renderizador->LimpiarPantalla({ 0.0f, 0.0f, 0.0f, 0.0f });

		ManejarEntradaDeUsuario();

		Actualizar();

		Renderizar();

		GL::Gui::EmpezarFrame();
		RenderizarGui();
		GL::Gui::TerminarFrame();

		m_Window->Cambiar();

		m_FPS = (float)m_AdministradorFps.TerminarFrame();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->ManejarEventos(m_ManejadorDeEventos);
}

void Game::Actualizar()
{
	m_Camara.Actualizar();
}

void Game::Renderizar()
{
	m_Renderizador->Empezar(m_Camara);

	/*for (std::shared_ptr<GL::ObjetoJuego>& objeto : m_Objetos)
	{
		if (!objeto->TieneComponente<GL::ComponenteSprite>())
		{
			GL::ComponenteSprite sprite{};
			m_Renderizador->Cuad(objeto->ObtenerComponente<GL::ComponenteTransform2D>(), sprite);
		}
		else
		{
			m_Renderizador->Cuad(objeto->ObtenerComponente<GL::ComponenteTransform2D>(), objeto->ObtenerComponente<GL::ComponenteSprite>());
		}
	}*/
	//m_Renderizador->MostarTextura("PeloNaranja");

	
	if (GL::Input::GetEstadoMouse(GL::MouseBoton::Izquierdo) )
	{
		glm::vec2 pos = GL::Input::GetPosMouse();
		pos = glm::clamp(pos, { 0.0f, 0.0f }, { Ancho-1, Alto-1 });
		int x = int(pos.x);
		int y = int(pos.y);
		int i = x + y * Ancho;
		ImageBuffer[i] = 0xffffff00;
	}

	std::shared_ptr<GL::Imagen> img = std::make_shared<GL::Imagen>(Ancho, Alto, ImageBuffer, Ancho * Alto * sizeof(uint32_t));
	GL::AdministradorRecursos::RecargarTextura("Fondo", img);

	GL::ComponenteTransform2D transform({ 0.0f, 0.0f });
	GL::ComponenteSprite sprite{};
	sprite.nombreTextura = "Fondo";
	m_Renderizador->Cuad(transform, sprite);

	m_Renderizador->Terminar();
}

void Game::RenderizarGui()
{
	//std::shared_ptr<GL::ObjetoJuego>& seleccionado = PanelObjetos::Render(m_Objetos);

	ImGui::Begin("Info");
	//ImGui::Text("Objeto Seleccionado: %s", seleccionado ? seleccionado->Etiqueta().etiqueta.c_str() : "");
	ImGui::Text("Ejecutando a: %.2f fps", m_FPS);
	ImGui::End();
}
