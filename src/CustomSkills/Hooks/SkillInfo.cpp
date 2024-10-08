#include "SkillInfo.h"

#include "CustomSkills/CustomSkillsManager.h"
#include "RE/Offset.h"

#include <xbyak/xbyak.h>

namespace CustomSkills
{
	void SkillInfo::WriteHooks()
	{
		SkillNamePatch();
		SkillColorPatch();
		PerkSkillNamePatch();
		SkillDescriptionPatch();
	}

	void SkillInfo::SkillNamePatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::UpdateSkillList, 0x1EE);				// VERIFIED
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		using GetSkillName_t = const char*(std::uint32_t);
		static REL::Relocation<GetSkillName_t> _GetSkillName;

		auto GetSkillName = +[](std::uint32_t a_skill) -> const char*
		{
			if (CustomSkillsManager::IsOurMenuMode()) {
				if (!CustomSkillsManager::_menuSkill->Name.empty()) {
					return CustomSkillsManager::_menuSkill->Name.c_str();
				}
			}
			return _GetSkillName(a_skill);
		};

		auto& trampoline = SKSE::GetTrampoline();
		_GetSkillName = trampoline.write_call<5>(hook.address(), GetSkillName);
	}

void SkillInfo::SkillColorPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::UpdateSkillList, 0x2F1);				// VERIFIED
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		using GetSkillColor_t = const char*(std::uint32_t);
		static REL::Relocation<GetSkillColor_t> _GetSkillColor;

		auto GetSkillColor = +[](std::uint32_t a_skill) -> const char*
		{
			if (CustomSkillsManager::IsOurMenuMode()) {
					if (CustomSkillsManager::_menuSkill->UpdateColor()) {
						return CustomSkillsManager::_menuSkill->ColorStr.c_str();
					}
					else {
						return CustomSkillsManager::_colorOfSkillNormal.c_str();
					}
				}

			return _GetSkillColor(a_skill);
		};

		auto& trampoline = SKSE::GetTrampoline();
		_GetSkillColor = trampoline.write_call<5>(hook.address(), GetSkillColor);
	}

	void SkillInfo::PerkSkillNamePatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::SetSkillInfo, 0x10D1);				// VERIFIED
		REL::make_pattern<"48 8D 4E 20 FF 50 28">().match_or_fail(hook.address());

		static auto GetSkillName = +[](RE::TESFullName* a_name) -> const char*
		{
			if (CustomSkillsManager::IsOurMenuMode()) {
				return CustomSkillsManager::_menuSkill->Name.c_str();
			}

			return a_name->GetFullName();
		};

		struct Patch : Xbyak::CodeGenerator
		{
			Patch(std::uintptr_t a_hookAddr)
			{
				lea(rcx, ptr[rsi + 0x20]);
				mov(rax, reinterpret_cast<std::uintptr_t>(GetSkillName));
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

	void SkillInfo::SkillDescriptionPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::StatsMenu::SetSkillInfo, 0x148F);				// VERIFIED
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		using GetDescription_t = void(RE::BSString&, RE::ActorValue);
		static REL::Relocation<GetDescription_t> _GetDescription;

		auto GetDescription = +[](RE::BSString& a_description, RE::ActorValue a_actorValue)
		{
			if (CustomSkillsManager::IsOurMenuMode()) {
				a_description = CustomSkillsManager::_menuSkill->Description;
			}
			else {
				_GetDescription(a_description, a_actorValue);
			}
		};

		auto& trampoline = SKSE::GetTrampoline();
		_GetDescription = trampoline.write_call<5>(hook.address(), GetDescription);
	}
}
