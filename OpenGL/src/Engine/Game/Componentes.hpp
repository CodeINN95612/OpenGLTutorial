#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Temporal
#include <string>

namespace GL
{
	struct Componente 
	{
		Componente() = default;
		virtual ~Componente() = default;
	};

	struct ComponenteTransform2D : public Componente
	{
		ComponenteTransform2D(glm::vec2 posicion) : posicion(posicion) {}
		virtual ~ComponenteTransform2D() = default;

		glm::vec2 posicion;
		glm::vec2 escala{1.0f, 1.0f};
		float anguloRotacion = 0.0f;

		inline glm::mat4 mat4()
		{
			glm::mat4 resultado{1.0f};

			// Traslacion
			resultado = glm::translate(resultado, { posicion.x, posicion.y, 0.0f});

			// Rotacion
			resultado = glm::rotate(resultado, glm::radians(anguloRotacion), { 0.0f, 0.0f, 1.0f });

			// Escala
			resultado = glm::scale(resultado, { escala.x, escala.y, 0.0f });

			return resultado;
		}
	};

	struct ComponenteEtiqueta : public Componente
	{
		ComponenteEtiqueta(const std::string& etiqueta) : etiqueta(etiqueta) {}
		virtual ~ComponenteEtiqueta() = default;

		std::string etiqueta;
	};

	struct ComponenteSprite : public Componente
	{
		ComponenteSprite() = default;
		virtual ~ComponenteSprite() = default;

		glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
		std::string nombreTextura{};
	};
}
