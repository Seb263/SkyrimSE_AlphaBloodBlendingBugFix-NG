#include "SettingsIni.hpp"
#include "Utils/ModUtils.hpp"

static inline const std::string_view MOD_NAME = "Alpha Blood Blending Bug Fix - NG";

static void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		{
			ModUtils::ApplyTextureSetsFixes();
		}
		break;
	}
}

static void InitializeLog(std::string_view pluginName, spdlog::level::level_enum a_level = spdlog::level::info)
{
	auto path = logger::log_directory();
	if (!path) {
		util::report_and_fail("Failed to find standard logging directory"sv);
	}

	*path /= std::format("{}.log", pluginName);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

	const auto level = a_level;

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
	log->set_level(level);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	if (level == spdlog::level::trace) spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] [%s:%#] %v");
	else spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
	const auto name{ plugin->GetName() };
	const auto version{ plugin->GetVersion() };

	SKSE::Init(a_skse);

	if (!SettingsIni::ReadSettings()) {
		InitializeLog(name, spdlog::level::info);
		logger::warn("Failed to load settings file.");
	} else {
		if (SettingsIni::iVerboseMode <= 0) {
			InitializeLog(name, spdlog::level::err);
		} else if (SettingsIni::iVerboseMode >= 2) {
			InitializeLog(name, spdlog::level::trace);
		} else {
			InitializeLog(name, spdlog::level::info);
		}
	}

	logger::info("{} v{} by Seb263 & Yuril : Loaded - Game version : {}", MOD_NAME, version.string("."), REL::Module::get().version().string("."));

	auto g_message = SKSE::GetMessagingInterface();
	if (!g_message) util::report_and_fail("Messaging Interface not found.");
	else if (!g_message->RegisterListener(MessageHandler)) util::report_and_fail("Failed to register MessageHandler listener.");
	else logger::info("Successfully registered MessageHandler listener.");

	return true;
}
