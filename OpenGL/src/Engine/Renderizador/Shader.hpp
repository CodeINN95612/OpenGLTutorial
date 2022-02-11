#pragma once

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>

namespace GL
{
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		virtual ~Shader();

		static std::shared_ptr<Shader> DesdeArchivo(const char* archivoVertexShader, const char* archivoFragmentShader);

		Shader(const Shader& other) = delete;
		Shader& operator==(const Shader& other) = delete;

		void Bind();

		void Uniform4f(const char* nombre, const glm::vec4& valores);

	private:
		uint32_t m_VertexShader;
		uint32_t m_FragmentShader;
		uint32_t m_Programa;

	private:
		int32_t GetUniformLocation(const char* nombre);

	};
}
