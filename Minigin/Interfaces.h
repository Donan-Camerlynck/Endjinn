#pragma once


namespace dae
{
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void Execute() = 0;
	};
}