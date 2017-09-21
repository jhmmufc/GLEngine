//#include "AudioManager.hpp"
//
//#include <irrKlang/irrKlang.h>
//
//#include <string>
//
//namespace GameEngine
//{
//	namespace Audio
//	{
//		void AudioManager::Play2DSound(const std::string& name, bool looped, bool startPaused)
//		{
//			m_engine.Play2DSound(name, looped, startPaused);
//		}
//
//		void AudioManager::Stop2DSound()
//		{
//			m_engine.Stop2DSound();
//		}
//
//		void AudioManager::PlaySoundEffect(const std::string& name)
//		{
//			m_engine.PlaySoundEffect(name);
//		}
//
//		bool AudioManager::IsPlayingSong(const std::string& name)
//		{
//			return m_engine.IsPlayingSong(name);
//		}
//
//		void AudioManager::StopAllSounds()
//		{
//			m_engine.StopAllSounds();
//		}
//
//		std::string AudioManager::PrintCurrentSoundInfo() const
//		{
//			return m_engine.PrintCurrentSoundInfo();
//		}
//	}
//}