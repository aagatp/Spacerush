#pragma once
#include <SFML/Audio.hpp>
#include "resourceidentifiers.h"
#include "resourceholder.h"

class Audio
{
private:
	Audio& operator=(Audio) = delete;
	Audio(Audio&) = delete;

	bool playBgMusic = true;
	sf::Music bgMusic;
	SoundBufferHolder soundBuffers;
	sf::Sound* sounds;
	int soundCount = 0;
	int maxSoundCount = 100;
	float volume = 5.f;

public:
	//Create a audio object wherever needed
	Audio(int);
	~Audio();
	//Loading takes time so use accoringly
	//Maybe write different functions for different screens
	//so we can load audios separately
	void load();
	void loadMenu();
	void setBgMusicStatus(bool);
	sf::Sound& playSound(SoundEffect::ID);
};