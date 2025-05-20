#pragma once
#include "Singleton.h"
#include "Interfaces.h"
#include "GamePad.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "AxisCommand.h"

namespace dae
{
	enum class InputEventType
	{
		Down,
		Up,
		Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		void Initialize();
		void AddCommand(GamepadKey key, InputEventType type, std::unique_ptr<ICommand> command, unsigned int controllerID);
		void AddCommand(SDL_Scancode key, InputEventType type, std::unique_ptr<ICommand> command);
		void AddCommand(GamepadAxis2D axis, std::unique_ptr<AxisCommand> command, unsigned int controllerID);
	
		bool ProcessKeyboardInput();
		void ProcessGamePadActions();
		void ProcessGamePadAxis();
		void ProcessKeyboardActions();
	private:
		struct GamePadActionBinding
		{
			GamepadKey key;
			unsigned int controllerID;
			InputEventType type;
			std::unique_ptr<ICommand> command;
		};
		struct GamePadAxisBinding
		{
			GamepadAxis2D axis;
			unsigned int controllerID;
			std::unique_ptr<AxisCommand> command;
		};
		struct KeyboardActionBinding
		{
			SDL_Scancode key;
			InputEventType type;
			std::unique_ptr<ICommand> command;
			bool shouldExecute = false;
		};

		std::vector<std::unique_ptr<GamePad>> m_GamePads;
		std::vector<bool> m_KeyStatesSDL;
		std::vector<GamePadActionBinding> m_GamePadBindings;
		std::vector<KeyboardActionBinding> m_KeyboardBindings;
		std::vector<GamePadAxisBinding> m_GamePadAxisBindings;
	public:
		bool ProcessInput();


	};

}
