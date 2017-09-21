#include "GameContext.hpp"

namespace GameEngine
{
	Input::InputManager& GameContext::GetInputManager()
	{
		return m_inputManager;
	}

	ResourceManagement::ResourceManager& GameContext::GetResourceManager()
	{
		return m_resourceManager;
	}

	//Audio::AudioManager& GameContext::GetAudioManager()
	//{
	//	return m_audioManager;
	//}
}