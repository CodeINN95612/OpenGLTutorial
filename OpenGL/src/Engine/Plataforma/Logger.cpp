#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace GL
{

	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;

	void Logger::Inicializar()
	{
		spdlog::set_pattern("%^[%T] [%n-%l]: %v%$");

		s_ClientLogger = spdlog::stdout_color_mt("CLIENTE");
		s_EngineLogger = spdlog::stdout_color_mt("MOTOR");

		s_ClientLogger->set_level(spdlog::level::level_enum::trace);
		s_EngineLogger->set_level(spdlog::level::level_enum::trace);
	}

	void Logger::Finalizar()
	{
		//TODO: Escribir a archivo
	}
}