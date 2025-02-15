#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:

		virtual void Initialize();
		virtual void Update();
		virtual void Render() const;

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		GameObject* GetOwner() const { return m_Owner; }

	protected:

		explicit BaseComponent(GameObject* owner) : m_Owner{ owner } {}

	private:
		GameObject* m_Owner;
		bool m_MarkedForRemoval;
	};

}

