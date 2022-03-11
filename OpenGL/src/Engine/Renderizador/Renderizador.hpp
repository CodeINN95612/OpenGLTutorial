#pragma once
#include "Engine/Renderizador/VertexArray.hpp"
#include "Engine/Game/CamaraOrtografica.hpp"
#include "Shader.hpp"
#include "Textura.hpp"
#include "Color.hpp"

#include "Engine/Game/Componentes.hpp"

#include <glm/glm.hpp>

namespace GL
{
	class Renderizador
	{
	public:
		Renderizador();
		virtual ~Renderizador();

		Renderizador(const Renderizador& other) = delete;
		Renderizador& operator==(const Renderizador& other) = delete;

		//Comandos
		void Viewport(uint32_t x, uint32_t y, uint32_t ancho, uint32_t alto);
		void LimpiarPantalla(const glm::vec4& color);

		void Dibujar(const VertexArray* vertexArray);

		void Empezar(CamaraOrtografica& camara);
		void Terminar();

		//Metodos
		void Cuad(ComponenteTransform2D& transform, ComponenteSprite& sprite);

	private:
		std::unique_ptr<VertexArray> m_CuadVertexArray{};

		glm::mat4 m_MatrizVistaProyeccion{ 1.0f };
	};
}
