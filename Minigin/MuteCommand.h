#pragma once
#include "ICommand.h"

namespace dae
{
	class GameObject;

	class MuteCommand : public ICommand
	{
	public:
		void Execute() override;


	};
}