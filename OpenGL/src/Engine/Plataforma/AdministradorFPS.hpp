#pragma once
#include <cstdint>

namespace GL
{
	class AdministradorFPS
	{
	public:
		static constexpr const float ValorMilisegundos = 1000.0f; //Mil milisegundos = 1 segundo
	public:
		AdministradorFPS(float fpsRequeridos);
		virtual ~AdministradorFPS();

		AdministradorFPS(const AdministradorFPS& other) = delete;
		AdministradorFPS& operator==(const AdministradorFPS& other) = delete;

		void EmpezarFrame();

		double TerminarFrame();

	private:
		float m_FpsRequeridos;
		double m_EspacioFrame;

		double m_FrameEmpieza;
		double m_TiempoFrame;
	};
}
