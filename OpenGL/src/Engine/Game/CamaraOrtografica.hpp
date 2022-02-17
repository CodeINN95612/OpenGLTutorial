#pragma once

#include <glm/glm.hpp>

namespace GL
{
	class CamaraOrtografica
	{
	public:
		CamaraOrtografica(uint32_t ancho, uint32_t alto, glm::vec3 posicion);
		virtual ~CamaraOrtografica();

		CamaraOrtografica(const CamaraOrtografica& other) = delete;
		CamaraOrtografica& operator==(const CamaraOrtografica& other) = delete;

		void Actualizar();
		void CambioDimensiones(uint32_t ancho, uint32_t alto);

		inline glm::mat4 GetMatrixVistaProyeccion() const { return m_MatrizProyeccion * m_MatrizVista; }

	private:
		glm::mat4 m_MatrizVista{ 1.0f };
		glm::mat4 m_MatrizProyeccion{ 1.0f };

		uint32_t m_Ancho{};
		uint32_t m_Alto{};
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
