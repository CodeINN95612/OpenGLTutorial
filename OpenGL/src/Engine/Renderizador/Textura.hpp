#pragma once

#include "Imagen.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace GL
{
	class Textura
	{
	public:
		Textura(const std::shared_ptr<Imagen>& imagen, glm::vec2 pos, glm::vec2 dim);
		virtual ~Textura();

		Textura(const Textura& other) = delete;
		Textura& operator==(const Textura& other) = delete;

		static std::shared_ptr<Textura> DesdeArchivo(const char* archivo, glm::vec2 pos = { 0.0f, 0.0f }, glm::vec2 dim = { 0.0f, 0.0f });

		void Bind(uint32_t espacio);

	private:
		uint32_t m_Objeto = 0;

	private:
		static uint32_t ObtenerFormatoInterno(Imagen::Canal canal);
		static uint32_t ObtenerFormato(Imagen::Canal canal);
	};
}
