#pragma comment(lib, "XInput.lib") 
#include "GamePad.h"
#include <windows.h>
#include <Xinput.h>


class dae::GamePad::Impl
{
public:
	Impl(unsigned int id) : m_Id{ id } {}
	bool GetButtonState(int button) const {
		if (button == 0)
		{
			return false;
		}
		return true;
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(m_Id, &m_CurrentState);

		if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
		{
			m_IsConnected = false;
			return;
		}
		m_IsConnected = true;

		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
	bool IsDownThisFrame(unsigned int button) const
	{
		return buttonsPressedThisFrame & button;
	}
	bool IsUpThisFrame(unsigned int button) const
	{
		return buttonsReleasedThisFrame & button;
	}
	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
	bool IsStateChanged() const
	{
		return m_CurrentState.dwPacketNumber != m_PreviousState.dwPacketNumber;
	}
	glm::vec2 GetThumbL2D() const
	{
		const float deadzoneThreshold = m_DeadZone * 32767;

		const float x = std::abs(m_CurrentState.Gamepad.sThumbLX) < deadzoneThreshold ? 0.0f : m_CurrentState.Gamepad.sThumbLX / 32767.0f;
		const float y = std::abs(m_CurrentState.Gamepad.sThumbLY) < deadzoneThreshold ? 0.0f : m_CurrentState.Gamepad.sThumbLY / 32767.0f;

		return glm::vec2{ x, -1.f * y };
	}
	glm::vec2 GetThumbR2D() const
	{
		const float deadzoneThreshold = m_DeadZone * 32767;

		const float x = std::abs(m_CurrentState.Gamepad.sThumbRX) < deadzoneThreshold ? 0.0f : m_CurrentState.Gamepad.sThumbRX / 32767.0f;
		const float y = std::abs(m_CurrentState.Gamepad.sThumbRY) < deadzoneThreshold ? 0.0f : m_CurrentState.Gamepad.sThumbRY / 32767.0f;

		return glm::vec2{ x,-1.f * y };
	}
	glm::vec2 GetDPad2D() const
	{
		glm::vec2 axis{};
		if (IsPressed(static_cast<unsigned int>(dae::GamepadKey::DPad_Left))) axis.x = -1.f;
		else if (IsPressed(static_cast<unsigned int>(dae::GamepadKey::DPad_Right))) axis.x = 1.0f;

		if (IsPressed(static_cast<unsigned int>(dae::GamepadKey::DPad_Down))) axis.y = 1.f;
		else if (IsPressed(static_cast<unsigned int>(dae::GamepadKey::DPad_Up))) axis.y = -1.0f;

		return axis;
	}


	void SetDeadZone(float deadZone)
	{
		m_DeadZone = deadZone;
	}
private:
	unsigned int m_Id;
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int buttonsPressedThisFrame{};
	unsigned int buttonsReleasedThisFrame{};
	float m_DeadZone{ 0.5f };
	bool m_IsConnected{};
};

dae::GamePad::GamePad(unsigned int id)
	: m_Impl{ std::make_unique<Impl>(id) }
{
}

dae::GamePad::~GamePad() = default;

void dae::GamePad::Update()
{
	m_Impl->Update();
}



bool dae::GamePad::IsDown(unsigned int button) const
{
	return m_Impl->IsDownThisFrame(button);
}

bool dae::GamePad::IsUp(unsigned int button) const
{
	return m_Impl->IsUpThisFrame(button);
}

bool dae::GamePad::IsPressed(unsigned int button) const
{
	return m_Impl->IsPressed(button);
}

bool dae::GamePad::IsStateChanged() const
{
	return m_Impl->IsStateChanged();
}

void dae::GamePad::SetDeadZone(float deadZone)
{
	m_Impl->SetDeadZone(deadZone);
}

glm::vec2 dae::GamePad::GetThumbL2D() const
{
	return m_Impl->GetThumbL2D();
}

glm::vec2 dae::GamePad::GetThumbR2D() const
{
	return m_Impl->GetThumbR2D();
}

glm::vec2 dae::GamePad::GetDPad2D() const
{
	return m_Impl->GetDPad2D();
}

int dae::GamePad::GetMaxUsers()
{
	return XUSER_MAX_COUNT;
}

