#include "Textura.hpp"

#include <glad/glad.h>

namespace GL
{
	Textura::Textura(const std::shared_ptr<Imagen>& imagen, glm::vec2 pos, glm::vec2 dim)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Objeto);

		glTextureStorage2D(m_Objeto, 1, ObtenerFormatoInterno(imagen->GetCanal()), imagen->GetAncho(), imagen->GetAlto());

		glTextureParameteri(m_Objeto, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_Objeto, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_Objeto, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTextureParameteri(m_Objeto, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		if (dim.x == 0 || dim.y == 0)
			dim = { imagen->GetAncho(), imagen->GetAlto() };

		glTextureSubImage2D(m_Objeto, 0, pos.x, pos.y, dim.x, dim.y, ObtenerFormato(imagen->GetCanal()), GL_UNSIGNED_BYTE, imagen->GetBuffer());
	}

	Textura::~Textura()
	{
		glDeleteTextures(1, &m_Objeto);
	}

	std::shared_ptr<Textura> Textura::DesdeArchivo(const char* archivo, glm::vec2 pos, glm::vec2 dim)
	{
		std::shared_ptr<Imagen> imagen = Imagen::DesdeArchivo(archivo);
		return std::make_shared<Textura>(imagen, pos, dim);
	}

	void Textura::Bind(uint32_t espacio)
	{
		glBindTextureUnit(espacio, m_Objeto);
	}

	uint32_t Textura::ObtenerFormatoInterno(Imagen::Canal canal)
	{
		switch (canal)
		{
			case Imagen::Canal::R:    return GL_R8;
			case Imagen::Canal::RG:   return GL_RG8;
			case Imagen::Canal::RGB:  return GL_RGB8;
			case Imagen::Canal::RGBA: return GL_RGBA8;
		}
		assert(false && "Error de enumeracion");
		return 0;
	}
	uint32_t Textura::ObtenerFormato(Imagen::Canal canal)
	{
		switch (canal)
		{
			case Imagen::Canal::R:    return GL_RED;
			case Imagen::Canal::RG:   return GL_RG;
			case Imagen::Canal::RGB:  return GL_RGB;
			case Imagen::Canal::RGBA: return GL_RGBA;
		}
		assert(false && "Error de enumeracion");
		return 0;
	}
}