#pragma once

namespace RE
{
	namespace Offset
	{
		namespace BGSPerk
		{
			inline constexpr auto GetRequirementsText = REL::ID(23356);  // done
		}

		namespace BGSSkillPerkTreeNode
		{
			inline constexpr auto RefundPerks = REL::ID(51694);  // done
		}

		namespace BSTArrayBase
		{
			inline constexpr auto ListAlloc = REL::ID(66908);  // done
		}

		namespace LegendarySkillResetConfirmCallback
		{
			inline constexpr auto Run = REL::ID(51714);  // done
		}

		namespace Main
		{
			inline constexpr auto Update = REL::ID(35565);  // done
		}

		namespace PlayerSkills
		{
			inline constexpr auto GetSkillProgress = REL::ID(40552);  // done
		}

		namespace StatsMenu
		{
			inline constexpr auto Create = REL::ID(51738);             // done
			inline constexpr auto CreateStars = REL::ID(51667);        // done
			inline constexpr auto Ctor = REL::ID(51636);               // done
			inline constexpr auto DtorImpl = REL::ID(51637);           // done
			inline constexpr auto GetPerkCount = REL::ID(51664);       // done
			inline constexpr auto ModifyPerkCount = REL::ID(51665);    // done
			inline constexpr auto Navigate = REL::ID(51659);           // done
			inline constexpr auto ProcessButton = REL::ID(51647);      // done
			inline constexpr auto ProcessMessage = REL::ID(51638);     // done
			inline constexpr auto Rotate = REL::ID(51661);             // done
			inline constexpr auto SelectPerk = REL::ID(51648);         // done
			inline constexpr auto SelectStar = REL::ID(51669);         // done
			inline constexpr auto SetBeastSkillInfo = REL::ID(51673);  // done
			inline constexpr auto SetCameraTarget = REL::ID(51657);    // done
			inline constexpr auto SetSelectedTree = REL::ID(51666);    // done
			inline constexpr auto SetSkillInfo = REL::ID(51654);       // done
			inline constexpr auto UpdateSkillList = REL::ID(51652);    // done
		}

		inline constexpr auto DebugMessageBox = REL::ID(54737);                 // done
		inline constexpr auto FadeOutGame = REL::ID(52847);                     // need to do
		inline constexpr auto GetActorValueInfo = REL::ID(26569);               // done
		inline constexpr auto GetActorValueName = REL::ID(26561);               // done
		inline constexpr auto GetComparisonValue = REL::ID(29088);              // done
		inline constexpr auto IsBeastMode = REL::ID(519908);                    // done
		inline constexpr auto IsInMenuMode = REL::ID(403435);                   // need to do
		inline constexpr auto IsLegendaryDifficultyAvailable = REL::ID(15642);  // done
		inline constexpr auto LastChosenMenuIndex = REL::ID(510243);            // done
		inline constexpr auto OpenStatsMenu = REL::ID(51643);                   // done
		inline constexpr auto ShowHUDMessage = REL::ID(50751);                  // done
	}
}
