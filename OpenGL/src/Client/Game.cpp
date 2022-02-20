#include "Game.hpp"

#include <glm/glm.hpp>

/*TODO:

--Camaras
--Entradas de Usuario
--Color
--Renderizador
--Objetos de Juego (GameObjetcs)


Sistemas
Escenas
etc....

*/

glm::vec4 hsv2rgb(float inh, float ins, float inv)
{
	double      hh, p, q, t, ff;
	long        i;
	glm::vec4 out = {0.0f, 0.0f, 0.0f, 1.0f};

	if (ins <= 0.0) {
		out.r = inv;
		out.g = inv;
		out.b = inv;
		return out;
	}
	hh = inh;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = inv * (1.0 - ins);
	q = inv * (1.0 - (ins * ff));
	t = inv * (1.0 - (ins * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = inv;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = inv;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = inv;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = inv;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = inv;
		break;
	case 5:
	default:
		out.r = inv;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}


Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();
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

		m_AdministradorFps.TerminarFrame();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->ManejarEventos(m_ManejadorDeEventos);

	//si aplasto arriba, subir x

}

void Game::Actualizar()
{
	static int n = 0;
	static float c = 3.0f;

	m_Camara.Actualizar();
	
	if (n <= 360)
	{
		float an = n * 137.5f;
		float r = c * glm::sqrt(n);

		float x = r * glm::cos(an);
		float y = r * glm::sin(an);

		GL::ObjetoJuego obj = GL::ObjetoJuego::Crear();
		obj.etiqueta.etiqueta = "obj it. " + std::to_string(n);

		obj.tranform.posicion = { x, y };
		obj.tranform.escala = { 0.4f, 0.4f };
		obj.tranform.anguloRotacion = an;

		obj.sprite.color = hsv2rgb( glm::mod(an, 360.0f), glm::mod(x, 100.0f), glm::mod(y,	100.0f));

		m_Objetos.push_back(obj);
	}

	n++;
}

void Game::Renderizar()
{
	m_Renderizador->Empezar(m_Camara);

	for (GL::ObjetoJuego objeto : m_Objetos)
	{
		m_Renderizador->Cuad(objeto.tranform, objeto.sprite);
	}

	m_Renderizador->Terminar();
}

void Game::RenderizarGui()
{
	ImGui::Begin("Fondo");
	ImGui::ColorEdit3("Color Fondo", glm::value_ptr(ColorLimpieza));
	ImGui::End();

	/*ImGui::Begin("Objetos");
	for (GL::ObjetoJuego& objeto : m_Objetos)
	{
		ImGui::Text("Objeto %i:, %s", objeto.uuid, objeto.etiqueta.etiqueta.c_str());
	}
	ImGui::End();*/
}
