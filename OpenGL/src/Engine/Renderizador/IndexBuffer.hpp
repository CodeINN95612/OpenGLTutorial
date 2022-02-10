#pragma once

#include <cstdint>

namespace GL
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t cantidad, uint8_t* data);
		virtual ~IndexBuffer();

		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer& operator==(const IndexBuffer& other) = delete;

		inline uint32_t GetCantidad() const { return m_Cantidad; }
		inline uint32_t GetObjeto() const { return m_Objeto; }
		
	private:
		uint32_t m_Cantidad = 0;
		uint32_t m_Objeto = 0;
	};
}
