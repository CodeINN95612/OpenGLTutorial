#include "Archivo.hpp"

#include <sstream>
#include <fstream>

namespace GL
{
	std::string Archivo::Leer(const char* archivo)
	{
		std::ifstream file(archivo);
		if (!file.is_open())
			return "";

		std::ostringstream sstr;
		sstr << file.rdbuf();

		file.close();

		return sstr.str();
	}
}