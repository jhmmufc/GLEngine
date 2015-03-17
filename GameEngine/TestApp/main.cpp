#include <GameEngine/GameEngine.hpp>

#include <iostream>

int main()
{
	// This try catch block should only be enabled when debugging
	// For full release code the code should be exception free and it can be removed.
	try
	{
		// Function that initialises all the functionality of our engine
		GameEngine::Initialise();

		// Initialise an instance of the audio manager
		GameEngine::Audio::AudioManager audioManager;

		// Pass in a song name
		const std::string& song = "Audio/test.ogg";

		// Play a 2d sound
		audioManager.Play2DSound(song);

		// Prints the information regarding the current song
		std::cout << audioManager.PrintCurrentSoundInfo() << std::endl;

		// Keep the application open until the song is finished
		while (audioManager.IsPlayingSong(song));
	}
	catch (const std::exception& e)
	{
		// Indicate an error in our program
		std::cerr << e.what() << std::endl;
		return -1;
	}

	// Indicate that we have successfully finished
	return 0;
}