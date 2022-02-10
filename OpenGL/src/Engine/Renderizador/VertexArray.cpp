#include "VertexArray.hpp"

#include <glad/glad.h>
#include <assert.h>

namespace GL
{
	VertexArray::VertexArray(const Atributo* atributos, uint32_t cantidad):
		m_Cantidad(cantidad)
	{
		m_Atributos = new Atributo[cantidad];
		memcpy_s(m_Atributos, sizeof(Atributo) * cantidad, atributos, sizeof(Atributo) * cantidad);

		glCreateVertexArrays(1, &m_Objeto);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_Objeto);
		delete[] m_Atributos;
	}

	uint32_t VertexArray::GetDrawCount() const
	{
		if (m_IndexBuffer)
			return m_IndexBuffer->GetCantidad();
		
		uint32_t cantidad = 0;
		for (uint32_t i = 0; i < m_Cantidad; i++)
		{
			cantidad += CalcularCantidadAtributo(m_Atributos[i]);
		}

		uint32_t retorno = static_cast<uint32_t>(m_VertexBuffer->GetCantidad() / cantidad);
		return retorno;

	}

	void VertexArray::SetDataBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer)
	{
		assert(!m_VertexBuffer && "Solo se puede enviar la data 1 vez");
		assert(!m_IndexBuffer && "Solo se puede enviar la data 1 vez");

		m_VertexBuffer = vertexBuffer;
		m_IndexBuffer = indexBuffer;

		glVertexArrayVertexBuffer(m_Objeto, 0, m_VertexBuffer->GetObjeto(), 0, CalcularStrideAtributos());
		if(m_IndexBuffer)
			glVertexArrayElementBuffer(m_Objeto, m_IndexBuffer->GetObjeto());

		uint32_t offset = 0;
		for (uint32_t i = 0; i < m_Cantidad; i++)
		{
			Atributo& atrib = m_Atributos[i];

			glEnableVertexArrayAttrib(m_Objeto, atrib.location);
			glVertexArrayAttribFormat(m_Objeto, atrib.location, CalcularCantidadAtributo(atrib), GL_FLOAT, GL_FALSE, offset);
			glVertexArrayAttribBinding(m_Objeto, atrib.location, 0);

			offset += CalcularSizeAtributo(atrib);
		}
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_Objeto);
	}

	uint32_t VertexArray::CalcularStrideAtributos() const
	{
		uint32_t stride = 0;

		for (uint32_t i = 0; i < m_Cantidad; i++)
		{
			stride += CalcularSizeAtributo(m_Atributos[i]);
		}

		return stride;
	}

	uint32_t VertexArray::CalcularSizeAtributo(const Atributo& atributo) const
	{
		switch (atributo.tipo)
		{
			case TipoAtributo::Float:  return sizeof(float);
			case TipoAtributo::Float2: return sizeof(float) * 2;
			case TipoAtributo::Float3: return sizeof(float) * 3;
			case TipoAtributo::Float4: return sizeof(float) * 4;
		}
		
		assert(false && "Error de enumeracion");
		return 0;
	}
	uint32_t VertexArray::CalcularCantidadAtributo(const Atributo& atributo) const
	{
		switch (atributo.tipo)
		{
			case TipoAtributo::Float:  return 1;
			case TipoAtributo::Float2: return 2;
			case TipoAtributo::Float3: return 3;
			case TipoAtributo::Float4: return 4;
		}

		assert(false && "Error de enumeracion");
		return 0;
	}
}