#include "VertexBuffer.hpp"

#include <glad/glad.h>

namespace GL
{
	VertexBuffer::VertexBuffer(size_t cantidad, float* data) :
		m_Cantidad(cantidad)
	{
		glCreateBuffers(1, &m_Objeto);
		glNamedBufferStorage(m_Objeto, cantidad * sizeof(float), data, GL_MAP_WRITE_BIT /* GL_DYNAMIC_STORAGE_BIT*/);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Objeto);
	}
}