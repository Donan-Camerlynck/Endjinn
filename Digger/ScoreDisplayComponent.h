#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Observer.h"
namespace dae
{

	class ScoreDisplayComponent : public BaseComponent, public IObserver
	{
	public:
		ScoreDisplayComponent(GameObject* owner, GameObject* characterToDisplay);
		void Initialize() override;
		void Update() override;
		virtual ~ScoreDisplayComponent() = default;
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		void Notify() override;
	private:
		TextComponent* m_pTextComp{ nullptr };
		GameObject* m_pCharacterToDisplay{ nullptr };
		bool m_NeedsUpdate{ false };
	};

}

