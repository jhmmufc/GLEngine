#ifndef AUDIO_ENGINE_GAME_CONTEXT_HPP
#define AUDIO_ENGINE_GAME_CONTEXT_HPP

#include "ResourceManager.hpp"
#include "InputManager.hpp"
//#include "AudioManager.hpp"

namespace GameEngine
{
	class GameContext
	{
	public:
		GameContext() = default;

		Input::InputManager& GetInputManager();
		ResourceManagement::ResourceManager& GetResourceManager();
		//Audio::AudioManager& GetAudioManager();
	private:
		Input::InputManager m_inputManager;
		ResourceManagement::ResourceManager m_resourceManager;
		//Audio::AudioManager m_audioManager;
	};
}

#endif