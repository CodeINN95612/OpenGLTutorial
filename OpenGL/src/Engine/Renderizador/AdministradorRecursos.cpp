#include "AdministradorRecursos.hpp"
#include "Engine/Plataforma/Assert.hpp"

namespace GL
{
	std::map<const std::string, std::shared_ptr<Shader>> AdministradorRecursos::s_Shaders{};
	std::map<const std::string, std::shared_ptr<Textura>> AdministradorRecursos::s_Texturas{};

	bool AdministradorRecursos::TieneShader(std::string nombre)
	{
		return s_Shaders.find(nombre) != s_Shaders.end();
	}

	std::shared_ptr<Shader>& AdministradorRecursos::CargarShader(std::string nombre, std::shared_ptr<Shader> shader)
	{
		GL_ASSERT(!TieneShader(nombre), "Administrador de recursos ya tiene el shader");
		s_Shaders[nombre] = shader;
		return shader;
	}

	std::shared_ptr<Shader>& AdministradorRecursos::ObtenerShader(std::string nombre)
	{
		GL_ASSERT(TieneShader(nombre), "Administrador de recursos no tiene el shader");
		return s_Shaders[nombre];
	}

	bool AdministradorRecursos::TieneTextura(std::string nombre)
	{
		return s_Texturas.find(nombre) != s_Texturas.end();
	}

	std::shared_ptr<Textura>& AdministradorRecursos::CargarTextura(std::string nombre, std::shared_ptr<Textura> textura)
	{
		GL_ASSERT(!TieneTextura(nombre), "Administrador de recursos ya tiene la textura");
		s_Texturas[nombre] = textura;
		return textura;
	}

	std::shared_ptr<Textura>& AdministradorRecursos::ObtenerTextura(std::string nombre)
	{
		GL_ASSERT(TieneTextura(nombre), "Administrador de recursos no tiene la textura");
		return s_Texturas[nombre];
	}
}