#include "Soundsystem.h"
#include <queue>
#include <mutex>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>


namespace dae
{
    struct SoundRequest {
        std::string file;
        int channel;
    };

    class SoundSystem::Impl
    {
    public:
        Impl() : running(true) {
            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                std::cerr << "Mix_OpenAudio error: " << Mix_GetError() << "\n";
            }
            std::cout << "Num of channels: " << Mix_AllocateChannels(-1) << "\n";
            Mix_Volume(-1, MIX_MAX_VOLUME);
            worker = std::thread(&Impl::processQueue, this);
        }

        ~Impl() {
            running = false;
            if (worker.joinable()) worker.join();
            for (auto chunk : activeChunks)
            {
                Mix_FreeChunk(chunk);
            }
            Mix_CloseAudio();
            SDL_Quit();
        }

        void playSound(const std::string& file, int channel) 
        {
           
            std::lock_guard<std::mutex> lock(mtx);
            queue.push({ file, channel });
        }

    private:
        void processQueue() {
            while (running) {
                SoundRequest req;
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (!queue.empty()) {
                        req = queue.front();
                        queue.pop();
                    }
                }

                if (!req.file.empty()) {
                    Mix_Chunk* chunk = Mix_LoadWAV(req.file.c_str());
                    if (!chunk) {
                        std::cerr << "Mix_LoadWAV error: " << Mix_GetError() << "\n";
                        continue;
                    }

                    int channel = Mix_PlayChannel(req.channel, chunk, 0);
                    if (channel == -1) {
                        std::cerr << "Mix_PlayChannel error: " << Mix_GetError() << "\n";
                        Mix_FreeChunk(chunk);
                        continue;
                    }

                    std::lock_guard<std::mutex> lock(activeMtx);
                    activeChunks.push_back(chunk);
                }

                cleanFinishedChunks();
                SDL_Delay(5);
            }
        }

        void cleanFinishedChunks() {
            std::lock_guard<std::mutex> lock(activeMtx);
            for (auto it = activeChunks.begin(); it != activeChunks.end(); ) {
                // check if the chunk is still playing
                if (Mix_Playing(-1) == 0) { // no channels playing
                    Mix_FreeChunk(*it);
                    it = activeChunks.erase(it);
                }
                else ++it;
            }
        }

        std::thread worker;
        std::atomic<bool> running;

        std::mutex mtx;
        std::queue<SoundRequest> queue;

        std::mutex activeMtx;
        std::vector<Mix_Chunk*> activeChunks;
    
    };

	void SoundSystem::playSound(const std::string& file, int channel)
	{
		pImpl->playSound(file, channel);
	}
    SoundSystem::~SoundSystem() = default;

    SoundSystem::SoundSystem()
        :pImpl(std::make_unique<Impl>())
    {
    }
    
   
}

