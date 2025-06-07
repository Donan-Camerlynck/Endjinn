#pragma once
#include "BaseComponent.h"
#include <memory>
#include "Subject.h"

namespace dae
{
    class ScoreComponent : public BaseComponent
    {
	public:
		explicit ScoreComponent(GameObject* owner, int initialScore = 0);
		void Update() override;
		void Initialize() override;

		int GetScore() const { return m_Score; }
		void AddScore(int score);
		void ResetScore();

		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		Subject* GetScoreChangedEvent() const { return m_ScoreChangedEvent.get(); }

	private:
		int m_Score{ 0 };

		std::unique_ptr<Subject> m_ScoreChangedEvent{ nullptr };
    };

}

