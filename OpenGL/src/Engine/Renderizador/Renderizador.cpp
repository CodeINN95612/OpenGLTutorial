#include "Renderizador.hpp"
#include "Engine/Plataforma/Logger.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

static void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length,
	GLchar const* msg, void const* user_param);

static std::string FuenteComoString(GLenum fuente);
static std::string TipoComoString(GLenum tipo);

namespace GL
{

	Renderizador::Renderizador()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ManejadorDeErrores, nullptr);
		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//Datos
		m_CuadTextura = Textura::DesdeColor(GL::Color::Hex::Blanco);

		m_CuadShader = GL::Shader::DesdeArchivo("./assets/shaders/Basic.vert", "./assets/shaders/Basic.frag");
		m_CuadShader->UniformTextura("uTextura", 0);

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

		m_CuadVertexArray = std::make_unique<GL::VertexArray>(atributos, (uint32_t)(sizeof(atributos) / sizeof(atributos[0])));
		m_CuadVertexArray->SetDataBuffer(vertexBuffer, indexBuffer);
	}

	Renderizador::~Renderizador()
	{
	}

	void Renderizador::Viewport(uint32_t x, uint32_t y, uint32_t ancho, uint32_t alto)
	{
		glViewport(x, y, ancho, alto);
	}

	void Renderizador::LimpiarPantalla(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderizador::Dibujar(const VertexArray* vertexArray)
	{
		if (vertexArray->IsElement())
			glDrawElements(GL_TRIANGLES, vertexArray->GetDrawCount(), GL_UNSIGNED_BYTE, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetDrawCount());
	}

	void Renderizador::Empezar(CamaraOrtografica& camara)
	{
		m_MatrizVistaProyeccion = camara.GetMatrixVistaProyeccion();
	}

	void Renderizador::Terminar()
	{

	}

	void Renderizador::Cuad(glm::vec2 pos, glm::vec2 escala, glm::vec4 color)
	{
		glm::mat4 model{1.0f};
		model = glm::translate(model, { pos.x, pos.y, 0.0 });
		model = glm::scale(model, { escala.x, escala.y, 1.0 });

		m_CuadShader->Uniform4f("uColor", color);
		m_CuadShader->UniformMat4("uMVP", m_MatrizVistaProyeccion * model);

		m_CuadVertexArray->Bind();
		m_CuadTextura->Bind(0);
		Dibujar(m_CuadVertexArray.get());
	}
	void Renderizador::Cuad(ComponenteTransform2D& transform, ComponenteSprite& sprite)
	{
		m_CuadShader->Uniform4f("uColor", sprite.color);
		m_CuadShader->UniformMat4("uMVP", m_MatrizVistaProyeccion * transform.mat4());

		m_CuadVertexArray->Bind();
		m_CuadTextura->Bind(0);
		Dibujar(m_CuadVertexArray.get());
	}
}

void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* msg, void const* user_param)
{
	std::string fuente = FuenteComoString(src);
	std::string tipo = TipoComoString(type);

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			GL_LOG_ENGINE_TRAZO("Fuente: {}; Tipo: {}; Mensaje: {}\n", fuente, tipo, msg);
			break;

		case GL_DEBUG_SEVERITY_LOW:
			GL_LOG_ENGINE_INFO("Fuente: {}; Tipo: {}; Mensaje: {}\n", fuente, tipo, msg);
			assert(false);
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			GL_LOG_ENGINE_ADVERTENCIA("Fuente: {}; Tipo: {}; Mensaje: {}\n", fuente, tipo, msg);
			assert(false);
			break;

		case GL_DEBUG_SEVERITY_HIGH:
			GL_LOG_ENGINE_CRITICAL("Fuente: {}; Tipo: {}; Mensaje: {}\n", fuente, tipo, msg);
			assert(false);
			break;

	}
}

std::string FuenteComoString(GLenum fuente)
{
	switch (fuente)
	{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "VENTANA";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "EXTERNO";
		case GL_DEBUG_SOURCE_APPLICATION: return "APLICACION";
		case GL_DEBUG_SOURCE_OTHER: return "OTRO";
	}
	assert(false);
	return "";
}

std::string TipoComoString(GLenum tipo)
{
	switch (tipo)
	{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "COMPORTAMIENTO ANTIGUO (NO RECOMENDADO)";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "COMPORTAMIENTO INDEFINIDO";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILIDAD";
		case GL_DEBUG_TYPE_PERFORMANCE: return "RENDIMIENTO";
		case GL_DEBUG_TYPE_MARKER: return "MARCADOR";
		case GL_DEBUG_TYPE_OTHER: return "OTRO";
	}
	assert(false);
	return "";
}
