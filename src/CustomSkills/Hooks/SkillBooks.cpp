#include "SkillBooks.h"

#include "CustomSkills/CustomSkillBookReadRegSet.h"
#include "CustomSkills/CustomSkillsManager.h"
#include "RE/Offset.h"

#include <xbyak/xbyak.h>

namespace CustomSkills
{
	void SkillBooks::WriteHooks()
	{
		CustomSkillPatch();
	}

	static bool ReadSkillBook(RE::TESObjectBOOK* a_book)
	{
		if (a_book->IsRead())
			return false;

		for (const RE::BGSKeyword* const keyword :
			 std::span(a_book->keywords, a_book->numKeywords)) {

			if (!keyword)
				continue;

			const auto str = std::string_view(keyword->formEditorID);
			static constexpr auto prefix = "CustomSkillBook_"sv;
			if (str.size() <= prefix.size() ||
				::_strnicmp(str.data(), prefix.data(), prefix.size()) != 0) {
				continue;
			}

			const auto skill = CustomSkillsManager::FindSkill(str.substr(prefix.size()));
			if (!skill)
				continue;

			const auto player = RE::PlayerCharacter::GetSingleton();
			float count = 1.0f;
			RE::BGSEntryPoint::HandleEntryPoint(
				RE::BGSEntryPoint::ENTRY_POINT::kAdjustBookSkillPoints,
				player,
				&count);

			CustomSkillBookReadRegSet::Get()
				->SendEvent(skill->ID, static_cast<std::int32_t>(count));
			return true;
		}

		return false;
	}

	void SkillBooks::CustomSkillPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::TESObjectBOOK::Read, 0x4A);
		REL::make_pattern<"0F 84 81 00 00 00">().match_or_fail(hook.address());

		struct Patch : Xbyak::CodeGenerator
		{
			Patch(std::uintptr_t a_hookAddr, std::uintptr_t a_funcAddr)
			{
				Xbyak::Label noHook;
				Xbyak::Label funcLbl;
				Xbyak::Label learnedSkill;

				jnz(noHook);

				mov(rcx, rdi);
				call(ptr[rip + funcLbl]);
				test(al, al);
				jne(learnedSkill);
				
				movzx(ecx, byte[rdi + 0x110]);
				jmp(ptr[rip]);
				dq(a_hookAddr + 0x87);
				
				L(learnedSkill);
				jmp(ptr[rip]);
				dq(a_hookAddr + 0xF4);

				L(noHook);
				jmp(ptr[rip]);
				dq(a_hookAddr + 0x6);

				L(funcLbl);
				dq(a_funcAddr);
			}
		};

		auto patch = new Patch(hook.address(), reinterpret_cast<std::uintptr_t>(&ReadSkillBook));
		patch->ready();

		auto& trampoline = SKSE::GetTrampoline();
		trampoline.write_branch<6>(hook.address(), patch->getCode());
	}
}
