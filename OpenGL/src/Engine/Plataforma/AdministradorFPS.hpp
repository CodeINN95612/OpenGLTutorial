#pragma once
#include <cstdint>

namespace GL
{
	class AdministradorFPS
	{
	public:
		static constexpr const uint32_t ValorMilisegundos = 1000; //Mil milisegundos = 1 segundo
	public:
		AdministradorFPS(uint8_t fpsRequeridos);
		virtual ~AdministradorFPS();

		AdministradorFPS(const AdministradorFPS& other) = delete;
		AdministradorFPS& operator==(const AdministradorFPS& other) = delete;

		void EmpezarFrame();

		void TerminarFrame();

	private:
		uint8_t m_FpsRequeridos;
		uint32_t m_EspacioFrame;

		uint64_t m_FrameEmpieza;
		uint32_t m_TiempoFrame;
	};
}
