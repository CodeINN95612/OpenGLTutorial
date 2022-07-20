#pragma once

#include "Componentes.hpp"

#include <cstdint>
#include <map>

namespace GL
{
	class ObjetoJuego
	{
	public:
		using UUID = uint64_t;

	public:
		//ObjetoJuego() {};
		ObjetoJuego(UUID uuid, const std::string& etiqueta, glm::vec2 posicion) : uuid(uuid) 
		{
			AgregarComponente<ComponenteEtiqueta>(etiqueta);
			AgregarComponente<ComponenteTransform2D>(posicion);
		};

		~ObjetoJuego()
		{
			for (auto&[nombre, componente] : m_Componentes)
				delete componente;
			m_Componentes.clear();
		};

		ObjetoJuego(const ObjetoJuego& other) = delete;
		ObjetoJuego& operator==(const ObjetoJuego& other) = delete;

		static std::shared_ptr<ObjetoJuego> Crear(const std::string& etiqueta, glm::vec2 posicion = { 0.0f, 0.0f })
		{
			static UUID globalUUID = 1;
			return std::make_shared<ObjetoJuego>(globalUUID++, etiqueta, posicion);
		}

		template<typename T>
		bool TieneComponente()
		{
			static_assert(std::is_convertible<T, Componente>(), "T debe derivar de Componente");
			return m_Componentes.find(typeid(T).name()) != m_Componentes.end();
		}

		template<typename T, typename ... Args>
		T& AgregarComponente(Args&& ... args)
		{
			static_assert(std::is_convertible<T, Componente>(), "T debe derivar de Componente");
			GL_ASSERT(!TieneComponente<T>(), "Objeto ya tiene componente");

			m_Componentes.insert({ typeid(T).name(), new T(std::forward<Args>(args)...) });
			return *static_cast<T*>(m_Componentes.at(typeid(T).name()));
		}

		template<typename T>
		T& ObtenerComponente()
		{
			static_assert(std::is_convertible<T, Componente>(), "T debe derivar de Componente");
			GL_ASSERT(TieneComponente<T>(), "Objeto no tiene componente");

			return *static_cast<T*>(m_Componentes.at(typeid(T).name()));
		}

		template<typename T>
		void EliminarComponente()
		{
			static_assert(std::is_convertible<T, Componente>(), "T debe derivar de Componente");
			GL_ASSERT(TieneComponente<T>(), "Objeto no tiene componente");

			T* componente = static_cast<T*>(m_Componentes.at(typeid(T).name()));
			m_Componentes.erase(typeid(T).name());
			delete componente;
		}

		
		ComponenteTransform2D& Transform()
		{
			return ObtenerComponente<ComponenteTransform2D>();
		}

		ComponenteEtiqueta& Etiqueta()
		{
			return ObtenerComponente<ComponenteEtiqueta>();
		}

	private:
		UUID uuid;
		std::map<std::string, Componente*> m_Componentes;
	};
}
