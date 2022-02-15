#pragma once

#include <cstdint>

namespace GL
{
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t cantidad, float* data);
		virtual ~VertexBuffer();

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator==(const VertexBuffer& other) = delete;

		inline size_t GetCantidad() const { return m_Cantidad; }
		inline uint32_t GetObjeto() const { return m_Objeto; }

	private:
		uint32_t m_Cantidad = 0;
		uint32_t m_Objeto = 0;
	};
}
