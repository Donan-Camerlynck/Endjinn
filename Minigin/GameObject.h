#pragma once
#include <memory>
#include <vector>
#include <concepts>
#include <type_traits>
#include "Transform.h"
#include <string>
#include "BaseComponent.h"
#include "Scene.h"



namespace dae
{
	enum class RenderLayer
	{
		BackGround,
		ObjectBottom,
		ObjectMiddle,
		ObjectTop,
		UI,
		numLayers
	};

	template<typename CompType>
	concept CompCon = requires(CompType)
	{
		std::is_base_of<dae::BaseComponent, CompType>::value;
	};
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render() const;
		virtual void End();

		void SetPosition(float x, float y);
		Transform GetTransform() { return m_transform; }

		
		GameObject(Scene* pOwner, RenderLayer renderLayer);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Addcomponent template function
		template <CompCon CompType, typename... Args>
		void AddComponent(Args&&... args)
		{

			auto component = std::make_unique<CompType>(this, std::forward<Args>(args)...);
			bool componentAdded{ false };

			for (unsigned int compIdx = 0; compIdx < m_Components.size(); compIdx++)
			{
				if (m_Components[compIdx].get())
					continue;

				m_Components[compIdx] = std::move(component);
				componentAdded = true;
				break;
			}

			if (!componentAdded)
				m_Components.emplace_back(std::move(component));
		}

		//GetComponent template function
		template <CompCon CompType>
		CompType* const GetComponent()
		{
			//switch to using std::find_if
			for (unsigned int compIdx = 0; compIdx < m_Components.size(); compIdx++)
			{
				auto compPtr{ dynamic_cast<CompType*>(m_Components[compIdx].get()) };
				if (compPtr)
					return compPtr;
			}
			return nullptr;
		}
		template<CompCon CompType>
		void RemoveComponent()
		{
			//use stl lib
			auto compPtr{ GetComponent<CompType>() };

			for (unsigned int compIdx = 0; compIdx < m_Components.size(); compIdx++)
			{
				if (m_Components[compIdx].get() != compPtr)
					continue;

				m_Components[compIdx].reset();
				return;
			}
		}

		template <CompCon CompType>
		bool HasComponent()
		{
			//switch to using std::any_of
			for (int compIdx = 0; compIdx < m_Components.size(); compIdx++)
			{
				bool present{ dynamic_cast<CompType*>(m_Components[compIdx].get()) != nullptr };
				if (present)
					return true;
			}
			return false;
		}

		void SetLocalPos(glm::vec2 localPos);
		void SetWorldPos(glm::vec2 worldPos);
		glm::vec2 GetLocalPos() const { return m_LocalPos; };
		glm::vec2 GetWorldPos() const { return m_WorldPos; };

		bool IsChild(GameObject* parent);
		void SetParent(GameObject* parent, bool keepWorldPos);
		GameObject* GetChildAt(int idx);

		void SetPositionDirty();
		void UpdateWorldPos();

		RenderLayer GetRenderLayer() { return m_RenderLayer; }
		
	private:
		Transform m_transform{};

		std::vector<std::unique_ptr<BaseComponent>> m_Components;

		std::vector<std::unique_ptr<GameObject>> m_Children{};
		GameObject* m_pParent{};

		RenderLayer m_RenderLayer{ RenderLayer::ObjectMiddle };
		

		Scene* m_pScene;

		glm::vec2 m_WorldPos{};
		glm::vec2 m_LocalPos{};

		bool m_bPositionDirty{ false };
	};
}
