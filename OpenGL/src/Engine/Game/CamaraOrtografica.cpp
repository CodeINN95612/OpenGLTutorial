#include "CamaraOrtografica.hpp"
#include "Engine/Plataforma/Input.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	CamaraOrtografica::CamaraOrtografica(float ancho, float alto, glm::vec3 posicion) :
		m_Ancho(ancho), m_Alto(alto), m_Posicion(posicion), m_Arriba(0.0f, 1.0f, 0.0f), m_Offset(0.0f, 0.0f, 1.0f)
	{ 
		ActualizarMatrices();
	}

	CamaraOrtografica::~CamaraOrtografica()
	{
	}

	void CamaraOrtografica::Actualizar()
	{
		if(Input::GetEstadoTeclado(TecladoTecla::Derecha))
			m_Posicion.x+=5;
		if (Input::GetEstadoTeclado(TecladoTecla::Izquierda))
			m_Posicion.x-= 5;
		if (Input::GetEstadoTeclado(TecladoTecla::Arriba))
			m_Posicion.y+= 5;
		if (Input::GetEstadoTeclado(TecladoTecla::Abajo))
			m_Posicion.y-= 5;
		
		ActualizarVista();
	}

	void CamaraOrtografica::CambioDimensiones(float ancho, float alto)
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