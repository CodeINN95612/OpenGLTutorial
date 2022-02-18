#pragma once

#include "Componentes.hpp"

#include <cstdint>

namespace GL
{
	class ObjetoJuego
	{
	public:
		using UUID = uint64_t;

	public:
		UUID uuid;
		TransformComponent2D tranform{};

	public:
		ObjetoJuego(UUID uuid) : uuid(uuid) {};
		virtual ~ObjetoJuego() = default;

		static ObjetoJuego Crear()
		{
			static UUID globalUUID = 1;
			return ObjetoJuego(globalUUID++);
		}
	};
}
