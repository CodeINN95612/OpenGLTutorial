#pragma once

#include <glm/glm.hpp>

namespace GL
{
	class CamaraOrtografica
	{
	public:
		CamaraOrtografica(float ancho, float alto, glm::vec3 posicion);
		virtual ~CamaraOrtografica();

		CamaraOrtografica(const CamaraOrtografica& other) = delete;
		CamaraOrtografica& operator==(const CamaraOrtografica& other) = delete;

		void Actualizar();
		void CambioDimensiones(float ancho, float alto);
		glm::vec2 MapearCoordenadas(glm::vec2 coords);

		inline glm::mat4 GetMatrixVistaProyeccion() const { return m_MatrizProyeccion * m_MatrizVista; }

	private:
		glm::mat4 m_MatrizVista{ 1.0f };
		glm::mat4 m_MatrizProyeccion{ 1.0f };

		float m_Ancho{};
		float m_Alto{};
		glm::vec3 m_Arriba{};
		glm::vec3 m_Posicion{};
		glm::vec3 m_Centro{};

		glm::vec3 m_Offset{};

	private:
		void ActualizarVista();
		void ActualizarProyeccion();
		void ActualizarMatrices();
	};
}
