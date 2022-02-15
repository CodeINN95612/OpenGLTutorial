#include "Imagen.hpp"
#include "Engine/Plataforma/Assert.hpp"
#include "Engine/Libs/stb_image/stb_image.h"


namespace GL
{
	Imagen::Imagen(uint32_t ancho, uint32_t alto, const void* buffer, uint32_t size, Canal canal) :
		m_Ancho(ancho), m_Alto(alto), m_Canal(canal)
	{
		m_Buffer = new uint8_t[m_Ancho * m_Alto * (uint8_t)m_Canal];
		memcpy_s(m_Buffer, m_Ancho * m_Alto * (uint8_t)m_Canal, buffer, size);
	}

	Imagen::~Imagen()
	{
		delete[] m_Buffer;
	}

	std::shared_ptr<Imagen> Imagen::DesdeArchivo(const char* archivo, bool flipY)
	{
		stbi_set_flip_vertically_on_load(!flipY);
		
		int32_t ancho, alto;
		int32_t canal;
		uint8_t* buffer;

		buffer = stbi_load(archivo, &ancho, &alto, &canal, 0);
		GL_ASSERT(buffer, "no se pudo cargar imagen de archivo");

		std::shared_ptr<Imagen> img = std::make_shared<Imagen>(ancho, alto, buffer, ancho * alto * canal, (Canal)canal);

		stbi_image_free(buffer);

		return img;
	}
}