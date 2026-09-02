#pragma once

#include "SettingsIni.hpp"

class ModUtils
{
public:

	static void ApplyTextureSetsFixes()
	{
		std::unordered_set<RE::BGSTextureSet*> processedTextures;

		for (RE::BGSImpactData* impactData : RE::TESDataHandler::GetSingleton()->GetFormArray<RE::BGSImpactData>()) {
			if (!impactData) continue;

			RE::BGSTextureSet* texture = impactData->decalTextureSet;
			if (!texture || processedTextures.contains(texture)) continue;
			if (!SettingsIni::bProcessDynamicTextureSets && texture->IsDynamicForm()) continue;

			const auto& glowTexturePath = texture->textures[RE::BSTextureSet::Textures::kGlowMap].textureName;
			if (!glowTexturePath.empty()) continue;

			if (SettingsIni::iVerboseMode > 1) logger::info("Tweaking Texture Set: {:08X}", texture->formID);
			texture->textures[RE::BSTextureSet::Textures::kGlowMap].textureName = SettingsIni::sGlowMapTexture;

			processedTextures.insert(texture);
		}
	}
};
