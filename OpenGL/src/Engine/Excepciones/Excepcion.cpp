#include "Excepcion.hpp"
#include "Plataforma/Logger.hpp"

namespace GL
{
	Excepcion::Excepcion(const char* archivo, uint32_t linea, const char* mensaje):
		m_Archivo(archivo), m_Linea(linea), m_Mensaje(mensaje)
	{

	}

	Excepcion::Excepcion(const char* mensaje) :
		m_Archivo("indefinido"), m_Linea(0), m_Mensaje(mensaje)
	{
	}

	void Excepcion::Log() const
	{
		GL_LOG_ENGINE_CRITICAL("Exepcion Generada. Archivo: [{}]. Linea: [{}], Mensaje: {}", m_Archivo, m_Linea, m_Mensaje);
	}
}