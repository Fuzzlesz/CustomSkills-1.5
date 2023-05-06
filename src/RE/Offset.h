#pragma once

namespace RE
{
	namespace Offset
	{
		namespace BGSPerk
		{
			inline constexpr auto GetRequirementsText = REL::ID(23356);  //1403388a0
		}

		namespace BGSSkillPerkTreeNode
		{
			inline constexpr auto RefundPerks = REL::ID(51694);
		}

		namespace BSTArrayBase
		{
			inline constexpr auto ListAlloc = REL::ID(66908);
		}

		namespace LegendarySkillResetConfirmCallback
		{
			inline constexpr auto Run = REL::ID(51714); 
		}

		namespace Main
		{
			inline constexpr auto Update = REL::ID(35565); 
		}

		namespace PlayerSkills
		{
			inline constexpr auto GetSkillProgress = REL::ID(40552);
		}

		namespace StatsMenu
		{
			inline constexpr auto Create = REL::ID(51738);        
			inline constexpr auto CreateStars = REL::ID(51667);   
			inline constexpr auto Ctor = REL::ID(51636);          
			inline constexpr auto DtorImpl = REL::ID(51637);         
			inline constexpr auto GetPerkCount = REL::ID(51664);   
			inline constexpr auto ModifyPerkCount = REL::ID(51665);   
			inline constexpr auto Navigate = REL::ID(51659);        
			inline constexpr auto ProcessButton = REL::ID(51647);     
			inline constexpr auto ProcessMessage = REL::ID(51638);   
			inline constexpr auto Rotate = REL::ID(51661);        
			inline constexpr auto SelectPerk = REL::ID(51648);        
			inline constexpr auto SelectStar = REL::ID(51669);     
			inline constexpr auto SetBeastSkillInfo = REL::ID(51673);  
			inline constexpr auto SetCameraTarget = REL::ID(51657);   
			inline constexpr auto SetSelectedTree = REL::ID(51666);    
			inline constexpr auto SetSkillInfo = REL::ID(51654);       
			inline constexpr auto UpdateSkillList = REL::ID(51652);    
		}

		inline constexpr auto DebugMessageBox = REL::ID(54737);                 
		inline constexpr auto FadeOutGame = REL::ID(51967);                     
		inline constexpr auto GetActorValueInfo = REL::ID(26569);               
		inline constexpr auto GetActorValueName = REL::ID(26561);               
		inline constexpr auto GetComparisonValue = REL::ID(29088);              
		inline constexpr auto IsBeastMode = REL::ID(519908);                    
		inline constexpr auto IsInMenuMode = REL::ID(516933);                   
		inline constexpr auto IsLegendaryDifficultyAvailable = REL::ID(15642);  
		inline constexpr auto LastChosenMenuIndex = REL::ID(510243);            
		inline constexpr auto OpenStatsMenu = REL::ID(51643);                   
		inline constexpr auto ShowHUDMessage = REL::ID(50751);                  
	}
}
