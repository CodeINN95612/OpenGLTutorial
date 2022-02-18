#pragma once

#include <glm/glm.hpp>

namespace GL::Color
{
	struct Vec
	{
		inline static constexpr const glm::vec4 Rojo{ 1.0f, 0.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Verde{ 0.0f, 1.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Azul{ 0.0f, 0.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Amarillo{ 1.0f, 1.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Negro{ 0.0f, 0.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Blanco{ 1.0f, 1.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Gris25{ 0.75f, 0.75f, 0.75f, 1.0f };
		inline static constexpr const glm::vec4 Gris50{ 0.5f, 0.5f, 0.5f, 1.0f };
		inline static constexpr const glm::vec4 Gris75{ 0.25f, 0.25f, 0.25f, 1.0f };
	};

	struct Hex
	{
		inline static constexpr const uint32_t Rojo = 0xff0000ff;
		inline static constexpr const uint32_t Verde = 0xff00ff00;
		inline static constexpr const uint32_t Azul = 0xffff0000;
		inline static constexpr const uint32_t Amarillo = 0xff00ffff;
		inline static constexpr const uint32_t Magenta = 0xffff00ff;
		inline static constexpr const uint32_t Cyan = 0xffffff00;
		inline static constexpr const uint32_t Negro = 0xff000000;
		inline static constexpr const uint32_t Blanco = 0xffffffff;
		inline static constexpr const uint32_t Gris25 = 0xffbfbfbf;
		inline static constexpr const uint32_t Gris50 = 0xff7f7f7f;
		inline static constexpr const uint32_t Gris75 = 0xff444444;
	};
}
