#include "MuteCommand.h"
#include "Soundsystem.h"

void dae::MuteCommand::Execute()
{
	dae::SoundSystem::GetInstance().Mute();
}
