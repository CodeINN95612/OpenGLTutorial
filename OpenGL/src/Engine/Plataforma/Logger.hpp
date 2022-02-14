#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace GL
{
	class Logger
	{

	public:
		virtual ~Logger() = default;

		Logger(const Logger& other) = delete;
		Logger& operator==(const Logger& other) = delete;

		static void Inicializar();
		static void Finalizar();

		static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

#define GL_LOG_ENGINE_TRAZO(...) ::GL::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define GL_LOG_ENGINE_INFO(...) ::GL::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define GL_LOG_ENGINE_ADVERTENCIA(...) ::GL::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define GL_LOG_ENGINE_CRITICAL(...) ::GL::Logger::GetEngineLogger()->critical(__VA_ARGS__)

#define GL_LOG_TRAZO(...) ::GL::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define GL_LOG_INFO(...) ::GL::Logger::GetClientLogger()->info(__VA_ARGS__)
#define GL_LOG_ADVERTENCIA(...) ::GL::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define GL_LOG_CRITICAL(...) ::GL::Logger::GetClientLogger()->critical(__VA_ARGS__)
}
