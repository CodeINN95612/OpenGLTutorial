#pragma once
#include "Defines.hpp"
#include "Plataforma/Logger.hpp"

#if ENGINE_DEBUG
	#define GL_ASSERT(x, ...) { \
			if(!(x)) \
			{ \
				GL_LOG_ENGINE_CRITICAL(__VA_ARGS__); \
				abort(); \
			} \
		}

#else
	#define GL_ASSERT(x, ...) x
#endif

