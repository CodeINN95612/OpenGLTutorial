#include "Game.hpp"

#include <glm/glm.hpp>

#include "Paneles/PanelObjetos.hpp"

Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	GL::AdministradorRecursos::CargarTextura("PeloNaranja", GL::Textura::DesdeArchivo("./assets/img/peloNaranja16x16.png"));
	GL::AdministradorRecursos::CargarTextura("Suelo", GL::Textura::DesdeArchivo("./assets/img/ventana16x16.png"));

	m_Jugador->AgregarComponente<GL::ComponenteSprite>().nombreTextura = "PeloNaranja";
	m_Objetos.push_back(m_Jugador);

	for (int i = -10; i < 10; i++)
	{
		std::shared_ptr<GL::ObjetoJuego> obj = GL::ObjetoJuego::Crear("Objeto" + std::to_string(i), { i * 50.0f, -200.0f });
		obj->AgregarComponente<GL::ComponenteSprite>().nombreTextura = "Suelo";

		m_Objetos.push_back(obj);
	}
}

Game::~Game()
{
}

void Game::Run()
{
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (m_Window->Corriendo())
	{
		m_AdministradorFps.EmpezarFrame();

		m_Renderizador->LimpiarPantalla(ColorLimpieza);

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

	GL::ComponenteTransform2D& transform = m_Jugador->ObtenerComponente<GL::ComponenteTransform2D>();

	transform.posicion.y -= velV;
	if (transform.posicion.y < -150.0f)
	{
		velV = 0;
		transform.posicion.y = -150.0f;
	}
	else
	{
		velV += g;
	}

	if(transform.posicion.y > -150.0f)
		enSuelo = false;
	else
		enSuelo = true;

		

	if(GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_d))
		transform.posicion.x += velH;
	if (GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_a))
		transform.posicion.x -= velH;

	if (GL::Input::GetEstadoTeclado(GL::TecladoTecla::Letra_w))
	{
		if(!salto && enSuelo)
			velV = -25;
		salto = true;
	}
	else
		salto = false;


}

void Game::Renderizar()
{
	m_Renderizador->Empezar(m_Camara);

	m_Renderizador->Cuad(m_Jugador->ObtenerComponente<GL::ComponenteTransform2D>(), m_Jugador->ObtenerComponente<GL::ComponenteSprite>());

	for (std::shared_ptr<GL::ObjetoJuego>& objeto : m_Objetos)
	{
		m_Renderizador->Cuad(objeto->ObtenerComponente<GL::ComponenteTransform2D>(), objeto->ObtenerComponente<GL::ComponenteSprite>());
	}

	m_Renderizador->Terminar();
}

void Game::RenderizarGui()
{
	std::shared_ptr<GL::ObjetoJuego>& seleccionado = PanelObjetos::Render(m_Objetos);

	ImGui::Begin("Info");
	ImGui::Text("Objeto Seleccionado: %s", seleccionado ? seleccionado->Etiqueta().etiqueta.c_str() : "");
	ImGui::Text("Ejecutando a: %.2f fps", m_FPS);
	ImGui::End();
}
