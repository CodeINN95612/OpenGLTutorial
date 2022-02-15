#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <memory>

namespace GL
{
	class VertexArray
	{
	public:
		enum class TipoAtributo
		{
			Float,
			Float2,
			Float3,
			Float4
		};

		struct Atributo
		{
			uint32_t location;
			TipoAtributo tipo;
		};

	public:
		VertexArray(const Atributo* atributos, uint32_t cantidad);
		virtual ~VertexArray();

		VertexArray(const VertexArray& other) = delete;
		VertexArray& operator==(const VertexArray& other) = delete;

		inline const Atributo* GetVertices() const { return m_Atributos; }
		inline uint32_t getCantidad() const { return m_Cantidad; }

		inline uint32_t GetObjeto() const { return m_Objeto; }
		uint32_t GetDrawCount() const;
		bool IsElement() const { return (bool)m_IndexBuffer; }

		void SetDataBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);

		inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		void Bind();

	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer{};
		std::shared_ptr<IndexBuffer> m_IndexBuffer{};

		Atributo* m_Atributos = nullptr;
		uint32_t m_Cantidad = 0;

		uint32_t m_Objeto = 0;

	private:
		uint32_t CalcularStrideAtributos() const;
		uint32_t CalcularSizeAtributo(const Atributo& atributo) const;
		uint32_t CalcularCantidadAtributo(const Atributo& atributo) const;
	};
}
