#pragma once

namespace GL
{
	class Archivo
	{
	public:
		virtual ~Archivo() = default;

		Archivo(const Archivo& other) = delete;
		Archivo& operator==(const Archivo& other) = delete;

		static bool Leer(const char* archivo, char** destino);

		static void Liberar(char* data);
	};
}
