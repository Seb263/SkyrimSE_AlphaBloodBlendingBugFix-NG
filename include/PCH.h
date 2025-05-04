#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMMNOSOUND

#include <unordered_set>

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#include <spdlog/sinks/basic_file_sink.h>

#include <ClibUtil/distribution.hpp>
#include <ClibUtil/editorID.hpp>
#include <ClibUtil/numeric.hpp>
#include <ClibUtil/rng.hpp>
#include <ClibUtil/simpleINI.hpp>

#include <SimpleMath.h>
#include <magic_enum.hpp>

namespace logger = SKSE::log;

using namespace std::literals;

namespace stl
{
	using namespace SKSE::stl;

	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		auto& trampoline = SKSE::GetTrampoline();
		SKSE::AllocTrampoline(14);

		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}

	template <class F, size_t offset, class T>
	void write_vfunc()
	{
		REL::Relocation<std::uintptr_t> vtbl{ F::VTABLE[offset] };
		T::func = vtbl.write_vfunc(T::idx, T::thunk);
	}

	template <class F, class T>
	void write_vfunc()
	{
		write_vfunc<F, 0, T>();
	}

	inline std::string as_string(std::string_view a_view)
	{
		return { a_view.data(), a_view.size() };
	}
}

namespace util
{
	[[noreturn]] inline static void report_and_fail(std::string_view a_msg, UINT msg_icon = MB_ICONERROR, std::source_location a_loc = std::source_location::current())
	{
		spdlog::log(
			spdlog::source_loc{ a_loc.file_name(), static_cast<int>(a_loc.line()), a_loc.function_name() },
			spdlog::level::critical, a_msg);

		const auto  plugin{ SKSE::PluginDeclaration::GetSingleton() };
		const auto  name{ plugin->GetName() };
		const char* msg_cstr = a_msg.data();

		REX::W32::MessageBoxA(nullptr, msg_cstr, name.data(), msg_icon);
		REX::W32::TerminateProcess(REX::W32::GetCurrentProcess(), EXIT_FAILURE);
	}
}
