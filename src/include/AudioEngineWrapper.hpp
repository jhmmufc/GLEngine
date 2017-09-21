#ifndef AUDIO_ENGINE_WRAPPER_HPP
#define AUDIO_ENGINE_WRAPPER_HPP

#include <string>

namespace irrklang
{
	class ISoundEngine;
	class ISound;
}

namespace GameEngine
{
	namespace Private
	{
		class AudioEngineWrapper
		{
		public:
			AudioEngineWrapper();
			~AudioEngineWrapper();

			void Play2DSound(const std::string& filename, bool looped = false, bool startPaused = false);
			void Stop2DSound();

			void PlaySoundEffect(const std::string& filename);

			bool IsPlayingSong(const std::string& filename);
			void StopAllSounds();

			std::string PrintCurrentSoundInfo() const;
		private:
			irrklang::ISoundEngine* m_soundEngine = nullptr;
			irrklang::ISound* m_sound = nullptr;
			std::string m_currentSound;

			// Helper function to get the sound engine
			irrklang::ISoundEngine* SoundEngine()
			{
				if (m_soundEngine)
				{
					return m_soundEngine;
				}
				else
				{
					throw std::runtime_error("Sound Engine is nullptr");
				}
			}
		};
	}
}

#endif