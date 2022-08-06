#include "CamaraOrtografica.hpp"
#include "Engine/Plataforma/Input.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	static float map(float value,
		float istart,
		float istop,
		float ostart,
		float ostop) {
		return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
	}

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

	glm::vec2 CamaraOrtografica::MapearCoordenadas(glm::vec2 coords)
	{
		glm::vec2 result;
		result.x = map(coords.x, 0, m_Ancho, -(m_Ancho / 2.0f), (m_Ancho / 2.0f));
		result.y = map(coords.y, 0, m_Alto, (m_Alto / 2.0f), -(m_Alto / 2.0f));
		return result;
	}

	void CamaraOrtografica::ActualizarVista()
	{
		m_Centro = m_Posicion + glm::vec3{ 0.0f, 0.0f, 1.0f };
		m_MatrizVista = glm::lookAt(m_Posicion, m_Centro, m_Arriba);
	}

	void CamaraOrtografica::ActualizarProyeccion()
	{
		m_MatrizProyeccion = glm::ortho((m_Ancho / 2.0f), -(m_Ancho / 2.0f), (m_Alto / 2.0f), -(m_Alto / 2.0f), -1.0f, 100.0f);
	}

	void CamaraOrtografica::ActualizarMatrices()
	{
		ActualizarProyeccion();
		ActualizarVista();
	}
}