#pragma once
#include <memory>
#include <glm.hpp>
namespace dae
{


	enum class GamepadKey
	{
		DPad_Up = 0x0001,
		DPad_Down = 0x0002,
		DPad_Left = 0x0004,
		DPad_Right = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LThumb = 0x0040,
		RThumb = 0x0080,
		LShoulder = 0x0100,
		RShoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000,
	};

	enum class GamepadAxis2D
	{
		LThumbStick,
		RThumbStick,
		DPad
	};

	class GamePad
	{
	public:
		explicit GamePad(unsigned int id);
		~GamePad();
		GamePad(const GamePad& other) = delete;
		GamePad(GamePad&& other) = delete;
		GamePad& operator=(const GamePad& other) = delete;
		GamePad& operator=(GamePad&& other) = delete;

		void Update();

		bool IsDown(unsigned int button) const;
		bool IsPressed(unsigned int button) const;
		bool IsUp(unsigned int button) const;
		bool IsStateChanged() const;

		void SetDeadZone(float deadZone);

		glm::vec2 GetThumbL2D() const;
		glm::vec2 GetThumbR2D() const;
		glm::vec2 GetDPad2D() const;

		static int GetMaxUsers();
	private:
		class Impl;
		std::unique_ptr<Impl> m_Impl;
	};
}