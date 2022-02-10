#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace GL
{
	IndexBuffer::IndexBuffer(uint32_t cantidad, uint8_t* data):
		m_Cantidad(cantidad)
	{
		glCreateBuffers(1, &m_Objeto);
		glNamedBufferStorage(m_Objeto, cantidad * sizeof(float), data, GL_MAP_WRITE_BIT /* GL_DYNAMIC_STORAGE_BIT*/);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_Objeto);
	}
}