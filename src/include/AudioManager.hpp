//#ifndef GAME_ENGINE_AUDIO_MANAGER_HPP
//#define GAME_ENGINE_AUDIO_MANAGER_HPP
//
//#include "AudioEngineWrapper.hpp"
//
//namespace GameEngine
//{
//	namespace Audio
//	{
//		class AudioManager
//		{
//		public:
//			AudioManager() = default;
//
//			void Play2DSound(const std::string& filename, bool looped = false, bool startPaused = false);
//			void Stop2DSound();
//
//			void PlaySoundEffect(const std::string& filename);
//
//			bool IsPlayingSong(const std::string& filename);
//			void StopAllSounds();
//
//			std::string PrintCurrentSoundInfo() const;
//		private:
//			Private::AudioEngineWrapper m_engine;
//		};
//	}
//}
//
//#endif