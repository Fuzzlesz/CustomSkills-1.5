#pragma once

namespace RE
{
	class ConstellationPicture
	{
	public:
		enum class CONSTELLATION_FADE_STATE
		{
			Resting = 0,
			Entering = 1,
			Exiting = 2,
		};

		static std::uint32_t CurrentTime()
		{
			static REL::Relocation<std::uint32_t*> currentTime{ REL::ID(523662) };				// 142f6b950
			return *currentTime;
		}

		bool IsActive()
		{
			return state != CONSTELLATION_FADE_STATE::Resting || shader && shader->QMaterialAlpha() > 0.0f;
		}

		void SetShader(RE::BSShaderProperty* a_shader)
		{
			shader = a_shader;
			shader->SetMaterial(a_shader->material, true);
			shader->SetMaterialAlpha(0.0f);
		}

		void Enter()
		{
			stateChangeTime = CurrentTime();
			state = CONSTELLATION_FADE_STATE::Entering;
		}

		void Exit()
		{
			if (IsActive()) {
				stateChangeTime = CurrentTime();
				state = CONSTELLATION_FADE_STATE::Exiting;
			}
		}

		void Update()
		{
			if (!shader || state == CONSTELLATION_FADE_STATE::Resting)
				return;

			if (CurrentTime() - stateChangeTime <= 500) {
				float alpha = (CurrentTime() - stateChangeTime) / 500.0f;
				if (state != CONSTELLATION_FADE_STATE::Entering) {
					alpha = 1.0f - alpha;
				}

				shader->SetMaterialAlpha(alpha);
			}
			else {
				float alpha = state == CONSTELLATION_FADE_STATE::Entering ? 1.0f : 0.0f;
				shader->SetMaterialAlpha(alpha);

				state = CONSTELLATION_FADE_STATE::Resting;
			}
		}

		RE::BSShaderProperty* shader = nullptr;
		SKSE::stl::enumeration<CONSTELLATION_FADE_STATE, std::uint32_t> state = CONSTELLATION_FADE_STATE::Resting;
		std::uint32_t stateChangeTime;
	};
	static_assert(sizeof(ConstellationPicture) == 0x10);
}
