#pragma once

namespace RE
{
	namespace Offset
	{
		namespace BGSPerk
		{
			inline constexpr auto GetRequirementsText = REL::ID(23356);				// 1403388a0
		}

		namespace BGSSkillPerkTreeNode
		{
			inline constexpr auto RefundPerks = REL::ID(51716);						// 1408caf80
		}

		namespace BSTArrayBase
		{
			inline constexpr auto ListAlloc = REL::ID(66908);						// 140c04a20
		}

		namespace LegendarySkillResetConfirmCallback
		{
			inline constexpr auto Run = REL::ID(51714);								// 1408cac50
		}

		namespace Main
		{
			inline constexpr auto Update = REL::ID(35565);							//1405b2ff0
		}

		namespace PlayerSkills
		{
			inline constexpr auto GetSkillProgress = REL::ID(40552);				// 1406e6130
		}

		namespace StatsMenu
		{
			inline constexpr auto Create = REL::ID(51738);							//1408cc7b0	
			inline constexpr auto CreateStars = REL::ID(51667);						// 1408C7650	
			inline constexpr auto Ctor = REL::ID(51636);							// 1408be990
			inline constexpr auto DtorImpl = REL::ID(51637);						// 1408beeb0
			inline constexpr auto GetPerkCount = REL::ID(51664);					// 1408c6f20
			inline constexpr auto ModifyPerkCount = REL::ID(51665);					// 1408c7050
			inline constexpr auto Navigate = REL::ID(51659);						// 1408c51b0
			inline constexpr auto ProcessButton = REL::ID(51647);					// 1408c0d90
			inline constexpr auto ProcessMessage = REL::ID(51638);					// 1408bf360
			inline constexpr auto Rotate = REL::ID(51661);							// 1408c5b60
			inline constexpr auto SelectPerk = REL::ID(51648);                      // 1408c1970
			inline constexpr auto SelectStar = REL::ID(51669);						// 1408c7920
			inline constexpr auto SetBeastSkillInfo = REL::ID(51673);				// 1408c8350
			inline constexpr auto SetCameraTarget = REL::ID(51657);					// 1408c4530
			inline constexpr auto SetSelectedTree = REL::ID(51666);					// 1408c7110
			inline constexpr auto SetSkillInfo = REL::ID(51654);					// 1408c2ba0
			inline constexpr auto UpdateSkillList = REL::ID(51652);					// 1408c20c0
		}

		inline constexpr auto DebugMessageBox = REL::ID(54737);						// 14096dd60         
		inline constexpr auto FadeOutGame = REL::ID(51909);							// 1408945A0
		inline constexpr auto GetActorValueInfo = REL::ID(26569);					// 1403E1420           
		inline constexpr auto GetActorValueName = REL::ID(26561);					// 1403E1130       
		inline constexpr auto GetComparisonValue = REL::ID(29088);					// 1404453e0
		inline constexpr auto IsBeastMode = REL::ID(519908);						// 142F4E920   
		inline constexpr auto IsInMenuMode = REL::ID(516933);						//142f26b74
		inline constexpr auto IsLegendaryDifficultyAvailable = REL::ID(15642);		// 1401d14b0
		inline constexpr auto LastChosenMenuIndex = REL::ID(510243);				//141df4990  
		inline constexpr auto OpenStatsMenu = REL::ID(51643);						// 1408C0950 
		inline constexpr auto ShowHUDMessage = REL::ID(50751);						// 140880160     
	}
}
