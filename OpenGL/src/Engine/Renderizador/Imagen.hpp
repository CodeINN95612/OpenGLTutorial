#pragma once

#include <cstdint>
#include <memory>

namespace GL
{
	class Imagen
	{
		enum class Canal : uint8_t
		{
			R = 1,
			RG = 2,
			RGB = 3,
			RGBA = 4
		};

	public:
		Imagen(uint32_t ancho, uint32_t alto, const void* buffer, uint32_t size, Canal canal = Canal::RGBA);
		virtual ~Imagen();

		Imagen(const Imagen& other) = delete;
		Imagen& operator==(const Imagen& other) = delete;

		static std::shared_ptr<Imagen> DesdeArchivo(const char* archivo, bool flipY = false);

		inline Canal GetCanal() const { return m_Canal; }
		inline uint32_t GetAlto() const { return m_Alto; }
		inline uint32_t GetAncho() const { return m_Ancho; }
		inline const uint8_t* GetBuffer() const { return m_Buffer; }

	private:
		Canal m_Canal = Canal::RGB;
		uint32_t m_Alto = 0;
		uint32_t m_Ancho = 0;
		uint8_t* m_Buffer = nullptr;
	};
}
