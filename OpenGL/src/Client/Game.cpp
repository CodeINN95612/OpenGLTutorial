#include "Game.hpp"

#include <glm/glm.hpp>

/*TODO:

-----1.1. Manejador de Eventos 
-----1.2. Manejador de Eventos
-----1.3 Probar
-----2. Logeo => Mensajes a la consola
-----3. Manejar Errores (crear propio assert) (opciones de debug)
-----4. Solucionar Problemas, Errores, Bugs (--Archivo, --Estructura, --Warnings de compilacion, --Renderizador funciones, --Licencias, --Macros debug logger--)
-----5. Interfaz Grafica (50%)

-----------------------------------------------------
Objetos de Juego (GameObjetcs)
Escenas
Sistemas
etc....

*/


Game::Game() :
	m_ManejadorDeEventos(*this)
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);

	m_Renderizador = m_Window->CrearRenderizador();

	m_Textura = GL::Textura::DesdeArchivo("./assets/img/peloNaranja16x16.png");
	m_TexturaVentana = GL::Textura::DesdeArchivo("./assets/img/ventana16x16.png");

	m_Shader = GL::Shader::DesdeArchivo("./assets/shaders/Basic.vert", "./assets/shaders/Basic.frag");
	m_Shader->UniformTextura("uTextura", 0);

	float vertices[] = {
		-0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
	};

	uint8_t indices[] = {
		0, 1, 2, 
		0, 2, 3
	};

	GL::VertexArray::Atributo atributos[] =
	{
		{0, GL::VertexArray::TipoAtributo::Float2},
		{1, GL::VertexArray::TipoAtributo::Float2},
	};

	std::shared_ptr<GL::VertexBuffer> vertexBuffer = std::make_shared<GL::VertexBuffer>((uint32_t)(sizeof(vertices) / sizeof(vertices[0])), vertices);
	std::shared_ptr<GL::IndexBuffer> indexBuffer = std::make_shared<GL::IndexBuffer>((uint32_t)(sizeof(indices) / sizeof(indices[0])), indices);

	m_VertexArray = std::make_unique<GL::VertexArray>(atributos, (uint32_t)(sizeof(atributos) / sizeof(atributos[0])));
	m_VertexArray->SetDataBuffer(vertexBuffer, indexBuffer);
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
		m_Renderizador->LimpiarPantalla(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

		ManejarEntradaDeUsuario();

		Actualizar();

		Renderizar();

		m_Window->GuiEjemplo();

		m_Window->Cambiar();
	}
}

void Game::ManejarEntradaDeUsuario()
{
	m_Window->ManejarEventos(m_ManejadorDeEventos);

	//si aplasto arriba, subir x

}

void Game::Actualizar()
{
	//poner coordenada = x
}

void Game::Renderizar()
{

	//////////////////////
	m_Textura->Bind(0);
	m_Shader->Bind();
	m_VertexArray->Bind();
	m_Renderizador->Dibujar(m_VertexArray.get());

	m_TexturaVentana->Bind(0);
	m_Renderizador->Dibujar(m_VertexArray.get());
	////////////////////

}