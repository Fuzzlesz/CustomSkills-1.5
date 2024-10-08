#include "SkillProgress.h"

#include "CustomSkills/CustomSkillsManager.h"
#include "CustomSkills/Game.h"
#include "RE/Offset.h"

#include <xbyak/xbyak.h>

namespace CustomSkills
{
	void SkillProgress::WriteHooks()
	{
		CurrentPerkPointsPatch();
		SelectPerkPatch();
		SkillProgressPatch();
		SkillLevelPatch();
		SkillLevelPatch2();
		PerkViewSkillLevelPatch();
		RequirementsTextPatch();
	}

	void SkillProgress::CurrentPerkPointsPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::GetPerkCount, 0x10F);		// VERIFIED
		REL::make_pattern<"0F B6 80">().match_or_fail(hook.address());

		struct Patch : Xbyak::CodeGenerator
		{
			Patch(std::uintptr_t a_hookAddr)
			{
				mov(rax,
					reinterpret_cast<std::uintptr_t>(&CustomSkillsManager::GetCurrentPerkPoints));
				call(rax);
				jmp(ptr[rip]);
				dq(a_hookAddr + 0x7);
			}
		};

		auto patch = new Patch(hook.address());
		patch->ready();

		auto& trampoline = SKSE::GetTrampoline();
		trampoline.write_branch<6>(hook.address(), patch->getCode());
	}

	void SkillProgress::SelectPerkPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::SelectPerk, 0x1DA);			// VERIFIED
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		auto& trampoline = SKSE::GetTrampoline();
		_ModifyPerkCount = trampoline.write_call<5>(hook.address(), &ModifyPerkCount);
	}

	void SkillProgress::SkillProgressPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::PlayerSkills::GetSkillProgress);

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(rax, reinterpret_cast<std::uintptr_t>(&GetSkillProgress));
				jmp(rax);
			}
		};

		Patch patch{};
		patch.ready();

		REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
	}

	void SkillProgress::SkillLevelPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::UpdateSkillList, 0x108);		// VERIFIED

		REL::make_pattern<
			"48 8B 0D ?? ?? ?? ?? "
			"48 81 C1 ?? 00 00 00 "
			"48 8B 01 "
			"8B D6 "
			"FF 50 08">()
			.match_or_fail(hook.address());

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(ecx, esi);
				mov(rax, reinterpret_cast<std::uintptr_t>(&CustomSkillsManager::GetSkillLevel));
				call(rax);
				nop(0x8);
			}
		};

		Patch patch{};
		patch.ready();
		assert(patch.getSize() == 0x16);

		REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
	}

	void SkillProgress::SkillLevelPatch2()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::SetSkillInfo, 0x1621);		// VERIFIED

	REL::make_pattern<
			"48 8B 0D ?? ?? ?? ?? "
			"48 81 C1 ?? 00 00 00 "
			"48 8B 01 "
			"8B D6 "
			"FF 50 08">()
			.match_or_fail(hook.address());

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(ecx, esi);
				mov(rax, reinterpret_cast<std::uintptr_t>(&CustomSkillsManager::GetSkillLevel));
				call(rax);
				nop(0x8);
			}
		};

		Patch patch{};
		patch.ready();
		assert(patch.getSize() == 0x16);

		REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
	}

	void SkillProgress::PerkViewSkillLevelPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::SetSkillInfo, 0x10BD);		// VERIFIED

	REL::make_pattern<"8B 95 70 05 00 00 FF 50 18">().match_or_fail(hook.address());

		struct Patch : Xbyak::CodeGenerator
		{
			Patch(std::uintptr_t a_hookAddr)
			{
				mov(ecx, ptr[rbp + 0x570]);
				mov(rax,
					reinterpret_cast<std::uintptr_t>(&CustomSkillsManager::GetBaseSkillLevel));
				call(rax);
				jmp(ptr[rip]);
				dq(a_hookAddr + 0x9);
			}
		};

		auto patch = new Patch(hook.address());
		patch->ready();

		auto& trampoline = SKSE::GetTrampoline();
		trampoline.write_branch<6>(hook.address(), patch->getCode());
	}

	void SkillProgress::RequirementsTextPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::BGSPerk::GetRequirementsText);

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(rax, reinterpret_cast<std::uintptr_t>(&GetRequirementsText));
				jmp(rax);
			}
		};

		Patch patch{};
		patch.ready();

		REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
	}

	void SkillProgress::ModifyPerkCount(RE::StatsMenu* a_statsMenu, std::int32_t a_countDelta)
	{
		if (CustomSkillsManager::IsOurMenuMode()) {
			if (a_countDelta > 0) {
				if (const auto player = RE::PlayerCharacter::GetSingleton()) {
					std::int32_t oldCount = player->perkCount;
					std::int32_t newCount = oldCount + a_countDelta;
					if (newCount > oldCount && oldCount != 255) {
						player->perkCount = static_cast<std::uint8_t>((std::min)(255, newCount));
					}
				}
			}
			else {
				std::int32_t oldCount = CustomSkillsManager::GetCurrentPerkPoints();
				std::int32_t newCount = oldCount + a_countDelta;

				if (newCount < 0) {
					newCount = 0;
				}
				else if (newCount > 255) {
					newCount = 255;
				}
				CustomSkillsManager::SetCurrentPerkPoints(static_cast<std::uint8_t>(newCount));
			}
		}
		else {
			_ModifyPerkCount(a_statsMenu, a_countDelta);
		}
	}

	void SkillProgress::GetSkillProgress(
		RE::PlayerCharacter::PlayerSkills* a_playerSkills,
		RE::ActorValue a_skill,
		float* a_level,
		float* a_xp,
		float* a_levelThreshold,
		std::uint32_t* a_legendary)
	{
		if (CustomSkillsManager::IsOurMenuMode()) {
			if (CustomSkillsManager::_menuSkill->Level) {
				*a_level = CustomSkillsManager::_menuSkill->Level->value;
			}
			else {
				*a_level = 1.0f;
			}

			if (CustomSkillsManager::_menuSkill->Ratio) {
				*a_xp = CustomSkillsManager::_menuSkill->Ratio->value;
			}
			else {
				*a_xp = 0.0f;
			}

			*a_levelThreshold = 1.0f;

			if (a_legendary) {
				if (CustomSkillsManager::_menuSkill->Legendary) {
					*a_legendary = static_cast<std::uint32_t>(
						CustomSkillsManager::_menuSkill->Legendary->value);
				}
				else {
					*a_legendary = 0;
				}
			}
			}
			else {
			std::size_t idx = util::to_underlying(a_skill) - 6;
			auto& data = a_playerSkills->data->skills[idx];
			*a_level = data.level;
			*a_xp = data.xp;
			*a_levelThreshold = data.levelThreshold;
			if (a_legendary) {
				*a_legendary = a_playerSkills->data->legendaryLevels[idx];
			}
		}
	}

	void SkillProgress::GetRequirementsText(
		RE::BGSPerk* a_perk,
		char* a_buf,
		std::int32_t a_bufLen,
		const char* a_prefix,
		const char* a_suffix)
	{
		*a_buf = '\0';

		std::ostringstream ss;
		bool firstReq = true;

		for (const auto* item = a_perk->perkConditions.head; item; item = item->next) {
			std::string token;

			auto& functionData = item->data.functionData;
			switch (functionData.function.get()) {
			case RE::FUNCTION_DATA::FunctionID::kGetBaseActorValue:
			{
				auto param = static_cast<RE::ActorValue>(
					std::bit_cast<std::uint64_t>(functionData.params[0]));
				auto name = Game::GetActorValueName(param);
				if (!name) {
					break;
				}

				token = fmt::format(
					"{}{}{}",
					a_prefix,
					static_cast<std::int32_t>(item->data.comparisonValue.f),
					a_suffix);
			} break;
			case RE::FUNCTION_DATA::FunctionID::kGetGlobalValue:
			{
				auto param = std::bit_cast<RE::TESGlobal*>(functionData.params[0]);
				if (!param) {
					break;
				}

				auto sk = CustomSkillsManager::FindSkillFromGlobalLevel(param);
				if (!sk) {
					break;
				}

				token = fmt::format(
					"{}{}{}",
					a_prefix,
					static_cast<std::int32_t>(item->data.comparisonValue.f),
					a_suffix);
			} break;
			}

			if (token.empty()) {
				continue;
			}

			static auto sRequirementsText = RE::GameSettingCollection::GetSingleton()->GetSetting(
				"sRequirementsText");
			if (firstReq) {
				ss << sRequirementsText->GetString();
			}
			else {
				ss << ",";
				firstReq = false;
			}

			ss << " ";

			std::size_t pos = ss.tellp();
			auto newSize = pos + token.size();
			if (newSize + 6 < a_bufLen) {
				ss << token;
			}
			else {
				ss << "...";
				break;
			}
		}

		auto str = ss.str();
		assert(str.size() < a_bufLen);
		std::copy_n(str.data(), str.size() + 1, a_buf);
	}
}
