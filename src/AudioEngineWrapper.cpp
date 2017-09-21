#include "AudioEngineWrapper.hpp"
#include "Utility.hpp"

#include <irrKlang\irrKlang.h>

#include <stdexcept>

namespace GameEngine
{
	namespace Private
	{
		AudioEngineWrapper::AudioEngineWrapper()
		{
			m_soundEngine = irrklang::createIrrKlangDevice();
		}

		AudioEngineWrapper::~AudioEngineWrapper()
		{
			Stop2DSound();

			if (m_soundEngine)
			{
				m_soundEngine->stopAllSounds();

				m_soundEngine->drop();

				m_soundEngine = nullptr;
			}
		}

		void AudioEngineWrapper::Play2DSound(const std::string& filename, bool looped, bool startPaused)
		{
			if (filename.empty())
			{
				throw std::runtime_error("Invalid file for audio manager");
			}

			if (IsPlayingSong(filename))
			{
				return;
			}

			if (m_sound)
			{
				Stop2DSound();
			}

			m_sound = SoundEngine()->play2D(filename.c_str(), looped, startPaused, true, irrklang::ESM_AUTO_DETECT, false);

			if (!m_sound)
			{
				throw std::runtime_error("Sound is nullptr");
			}

			m_currentSound = filename;
		}

		void AudioEngineWrapper::Stop2DSound()
		{
			if (m_sound)
			{
				m_sound->stop();

				m_sound->drop();

				m_sound = nullptr;
			}
		}

		void AudioEngineWrapper::PlaySoundEffect(const std::string& filename)
		{
			if (filename.empty())
			{
				throw std::runtime_error("Invalid sound effect for audio manager");
			}

			SoundEngine()->play2D(filename.c_str());
		}

		bool AudioEngineWrapper::IsPlayingSong(const std::string& filename)
		{
			return SoundEngine()->isCurrentlyPlaying(filename.c_str());
		}

		void AudioEngineWrapper::StopAllSounds()
		{
			SoundEngine()->stopAllSounds();
		}

		std::string AudioEngineWrapper::PrintCurrentSoundInfo() const
		{
			if (!m_sound)
			{
				return std::string("No current Sound Info");
			}

			std::string info;

			auto playLengthMS = m_sound->getPlayLength();

			int seconds = (int)(playLengthMS / 1000) % 60;
			int minutes = (int)((playLengthMS / (1000 * 60)) % 60);
			int hours = (int)((playLengthMS / (1000 * 60 * 60)) % 24);

			info = "FileName: " + m_currentSound + ", Track Length(h:m:s): " + std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);

			return info;
		}
	}
}