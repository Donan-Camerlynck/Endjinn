#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

dae::InputManager::~InputManager() = default;


void dae::InputManager::Initialize()
{
	m_KeyStatesSDL.resize(SDL_NUM_SCANCODES, false);
}

void dae::InputManager::AddCommand(GamepadKey key, InputEventType type, std::unique_ptr<ICommand> command, unsigned int controllerID)
{
	if (m_GamePads.size() <= controllerID)
	{
		m_GamePads.push_back(std::make_unique<GamePad>(controllerID));
	}
	m_GamePadBindings.push_back({ key, controllerID, type, std::move(command) });
}

void dae::InputManager::AddCommand(SDL_Scancode key, InputEventType type, std::unique_ptr<ICommand> command)
{
	m_KeyboardBindings.push_back({ key, type, std::move(command), false });
}

void dae::InputManager::AddCommand(GamepadAxis2D axis, std::unique_ptr<AxisCommand> command, unsigned int controllerID, bool diagonalAllowed)
{
	if (m_GamePads.size() <= controllerID)
	{
		m_GamePads.push_back(std::make_unique<GamePad>(controllerID));
	}
	m_GamePadAxisBindings.push_back({ axis, controllerID, std::move(command), 0.1f ,diagonalAllowed });
}

bool dae::InputManager::ProcessKeyboardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeyStatesSDL[e.key.keysym.scancode] = true;
			if (e.key.repeat == 0)
			{
				for (auto& binding : m_KeyboardBindings)
				{
					if (binding.key == e.key.keysym.scancode && (binding.type == InputEventType::Down || binding.type == InputEventType::Pressed))
					{
						binding.shouldExecute = true;
					}
				}
			}
		}
		if (e.type == SDL_KEYUP) {
			m_KeyStatesSDL[e.key.keysym.scancode] = true;
			if (e.key.repeat == 0)
			{
				for (auto& binding : m_KeyboardBindings)
				{
					if (binding.key == e.key.keysym.scancode && binding.type == InputEventType::Up)
					{
						binding.shouldExecute = true;
					}	
					if (binding.key == e.key.keysym.scancode && binding.type == InputEventType::Pressed && binding.previousShouldExecute)
					{
						binding.shouldExecute = false;
					}
				}
			}
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::ProcessGamePadActions()
{
	for (auto& binding : m_GamePadBindings)
	{
		if (const auto gamePad = m_GamePads[binding.controllerID].get())
		{
			bool bShouldExecute = false;
			switch (binding.type)
			{
			case InputEventType::Down:
				bShouldExecute = gamePad->IsDown(static_cast<unsigned int>(binding.key));
				break;
			case InputEventType::Up:
				bShouldExecute = gamePad->IsUp(static_cast<unsigned int>(binding.key));
				break;
			case InputEventType::Pressed:
				bShouldExecute = gamePad->IsPressed(static_cast<unsigned int>(binding.key));
				break;
			}
			if (bShouldExecute)
			{
				binding.command->Execute();
			}
		}		
	}
}

void dae::InputManager::ProcessGamePadAxis()
{
	for (auto& binding : m_GamePadAxisBindings)
	{
		if (const auto gamePad = m_GamePads[binding.controllerID].get())
		{
			bool bShouldExecute = false;
			glm::vec2 axisValue{0.f, 0.f};
			switch (binding.axis)
			{
			case GamepadAxis2D::LThumbStick:
				axisValue = gamePad->GetThumbL2D();
				bShouldExecute = true;
				break;
			case GamepadAxis2D::RThumbStick:
				axisValue = gamePad->GetThumbR2D();
				bShouldExecute = true;
				break;
			}
			if (bShouldExecute)
			{
				if (std::abs(axisValue.x) > binding.deadZone || std::abs(axisValue.y) > binding.deadZone)
				{
					if (binding.diagonalAllowed)
					{
						binding.command->SetDirection(axisValue);
					}
					else
					{
						if (std::abs(axisValue.x) >= std::abs(axisValue.y))
						{
							binding.command->SetDirection({ axisValue.x, 0.f });
						}
						else
						{
							binding.command->SetDirection({ 0.f, axisValue.y });
						}
					}

					binding.command->Execute();
				}				
			}
		}
	}
}

void dae::InputManager::ProcessKeyboardActions()
{
	for (auto& binding : m_KeyboardBindings)
	{
		if (binding.shouldExecute)
		{
			binding.command->Execute();
			if (binding.type == InputEventType::Down || binding.type == InputEventType::Up)
			{
				binding.previousShouldExecute = binding.shouldExecute;
				binding.shouldExecute = false;
			}
			else if (binding.type == InputEventType::Pressed)
			{
				binding.previousShouldExecute = binding.shouldExecute;
				binding.shouldExecute = true;
			}
		}
	}
}

bool dae::InputManager::ProcessInput()
{
	for (const auto& gamePad : m_GamePads)
	{
		gamePad->Update();
	}
	if (!ProcessKeyboardInput()) return false;
	ProcessKeyboardActions();
	ProcessGamePadActions();
	ProcessGamePadAxis();

	return true;

}
