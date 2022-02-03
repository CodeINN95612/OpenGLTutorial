#include "Renderizador.hpp"

#include <glad/glad.h>

#include <string>
#include <stdio.h>

static void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length,
	GLchar const* msg, void const* user_param);

static std::string FuenteComoString(GLenum fuente);
static std::string TipoComoString(GLenum tipo);
static std::string SeveridadComoString(GLenum severity);

namespace GL
{

	Renderizador::Renderizador()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ManejadorDeErrores, nullptr);
		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
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
}

void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* msg, void const* user_param)
{
	std::string fuente = FuenteComoString(src);
	std::string tipo = TipoComoString(type);
	std::string severidad = SeveridadComoString(severity);

	printf("Severidad: %s; Fuente: %s; Tipo: %s; Mensaje: %s", severidad.c_str(), fuente.c_str(), tipo.c_str(), msg);

	assert(severity != GL_DEBUG_SEVERITY_HIGH && "Error critico Encontrado");
	assert(severity != GL_DEBUG_SEVERITY_MEDIUM && "Error de alto nivel Encontrado");
	assert(severity != GL_DEBUG_SEVERITY_LOW && "Error de bajo nivel Encontrado");
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

std::string SeveridadComoString(GLenum severity)
{
	switch (severity) 
	{
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICACION";
		case GL_DEBUG_SEVERITY_LOW: return "LIGERA";
		case GL_DEBUG_SEVERITY_MEDIUM: return "ALTA";
		case GL_DEBUG_SEVERITY_HIGH: return "CRITICA";
	}
	assert(false);
	return "";
}
