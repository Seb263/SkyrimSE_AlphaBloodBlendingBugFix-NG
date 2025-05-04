#pragma once

class SettingsIni
{
public:
	// General
	static inline int  iVerboseMode = 1;
	static inline bool bProcessDynamicTextureSets = false;
	static inline std::string sGlowMapTexture = "Black.dds";

	static bool ReadSettings()
	{
		constexpr auto path = L"Data/SKSE/Plugins/AlphaBloodBlendingBug-Fix-NG.ini";

		if (!std::filesystem::exists(path)) return false;

		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error rc = ini.LoadFile(path);

		if (rc < 0) return false;

		// General
		iVerboseMode = ini.GetLongValue("General", "iVerboseMode", 1);
		bProcessDynamicTextureSets = ini.GetBoolValue("General", "bProcessDynamicTextureSets", false);
		sGlowMapTexture = ini.GetValue("General", "sGlowMapTexture", "Black.dds");

		return true;
	}
};
