#pragma once
#include <memory>
#include <string>
#include "Singleton.h"

namespace dae
{
    class SoundSystem : public Singleton<SoundSystem>
    {
    public:

        void playSound(const std::string& file, int channel = -1);
        void Mute();

        ~SoundSystem();
        SoundSystem();
    private:

        
        class Impl;
        std::unique_ptr<Impl> pImpl;

    };
}