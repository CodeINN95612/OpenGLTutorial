#include "Archivo.hpp"

#include <string>
#include <sstream>
#include <fstream>

namespace GL
{
	bool Archivo::Leer(const char* archivo, char** destino)
	{
		std::ifstream file(archivo);
		if (!file.is_open())
			return false;

		std::ostringstream sstr;
		sstr << file.rdbuf();

		file.close();

		auto str = sstr.str();
		auto cstr = str.c_str();

		size_t size = strlen(cstr)+1;

		*destino = new char[size];
		memcpy_s(*destino, size, cstr, size);

		return true;
	}
	void Archivo::Liberar(char* data)
	{
		delete[] data;
	}
}