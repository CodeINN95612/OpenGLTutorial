#include "CamaraOrtografica.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	CamaraOrtografica::CamaraOrtografica(uint32_t ancho, uint32_t alto, glm::vec3 posicion) :
		m_Ancho(ancho), m_Alto(alto), m_Posicion(posicion), m_Arriba(0.0f, 1.0f, 0.0f), m_Offset(0.0f, 0.0f, 1.0f)
	{ 
		ActualizarMatrices();
	}

	CamaraOrtografica::~CamaraOrtografica()
	{
	}

	void CamaraOrtografica::Actualizar()
	{
		static float an = 0.0f;
		//m_Posicion.x = glm::sin(glm::radians(an)) * m_Ancho / 4.0f;
		//m_Posicion.y = glm::cos(glm::radians(an)) * m_Alto / 4.0f;
		
		ActualizarVista();
		an++;
	}

	void CamaraOrtografica::CambioDimensiones(uint32_t ancho, uint32_t alto)
	{
		m_Ancho = ancho;
		m_Alto = alto;
		ActualizarProyeccion();
	}

	void CamaraOrtografica::ActualizarVista()
	{
		m_Centro = m_Posicion + glm::vec3{ 0.0f, 0.0f, 1.0f };
		m_MatrizVista = glm::lookAt(m_Posicion, m_Centro, m_Arriba);
	}

	void CamaraOrtografica::ActualizarProyeccion()
	{
		m_MatrizProyeccion = glm::ortho((m_Ancho / 2.0f), -(m_Ancho / 2.0f), -(m_Alto / 2.0f), (m_Alto / 2.0f), -1.0f, 100.0f);
	}

	void CamaraOrtografica::ActualizarMatrices()
	{
		ActualizarProyeccion();
		ActualizarVista();
	}
}