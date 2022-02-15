#pragma once

#include <cstdint>

namespace GL
{
	class Excepcion
	{
	public:
		Excepcion(const char* archivo, uint32_t linea, const char* mensaje);
		Excepcion(const char* mensaje);

		virtual ~Excepcion() = default;

		void Log() const;

	private:
		const char* m_Archivo;
		uint32_t m_Linea;
		const char* m_Mensaje;
	};
}
