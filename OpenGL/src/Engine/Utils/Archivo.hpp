#pragma once
#include <string>

namespace GL
{
	class Archivo
	{
	public:
		Archivo(const Archivo& other) = delete;
		Archivo& operator==(const Archivo& other) = delete;

		static std::string Leer(const char* archivo);
	};
}
