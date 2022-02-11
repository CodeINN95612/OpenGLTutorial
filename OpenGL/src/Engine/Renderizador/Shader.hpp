#pragma once

#include <cstdint>
#include <memory>

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

	private:
		uint32_t m_VertexShader;
		uint32_t m_FragmentShader;
		uint32_t m_Programa;

	};
}
