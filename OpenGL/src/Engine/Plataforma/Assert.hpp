#pragma once
#include "Defines.hpp"

#if ENGINE_DEBUG
#include "Plataforma/Logger.hpp"
	#define GL_ASSERT(x, msg) { \
			if(!(x)) \
			{ \
				GL_LOG_ENGINE_CRITICAL("Asercion fallida. Archivo: [{}]. Linea: [{}].  Mensaje: {}", __FILE__, __LINE__, msg); \
				abort(); \
			} \
		}

#else
#include "Excepciones/Excepcion.hpp"
	#define GL_ASSERT(x, msg) { \
				if(!(x)) \
				{ \
					throw ::GL::Excepcion(__FILE__, __LINE__, msg); \
				} \
			}
#endif

