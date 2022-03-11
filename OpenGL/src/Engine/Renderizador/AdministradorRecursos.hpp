#pragma once
#include "Shader.hpp"
#include "Textura.hpp"

#include <string>
#include <map>

namespace GL
{
	class AdministradorRecursos
	{
	public:
		virtual ~AdministradorRecursos() = default;

		static bool TieneShader(std::string nombre);
		static std::shared_ptr<Shader>& CargarShader(std::string nombre, std::shared_ptr<Shader> shader);
		static std::shared_ptr<Shader>& ObtenerShader(std::string nombre);
		
		static bool TieneTextura(std::string nombre);
		static std::shared_ptr<Textura>& CargarTextura(std::string nombre, std::shared_ptr<Textura> textura);
		static std::shared_ptr<Textura>& ObtenerTextura(std::string nombre);

	private:
		static std::map<const std::string, std::shared_ptr<Shader>> s_Shaders;
		static std::map<const std::string, std::shared_ptr<Textura>> s_Texturas;
	};
}
