#include "audio.h"

Audio::Audio(int maxSoundCount = 100):maxSoundCount(maxSoundCount)
{
	sounds = new sf::Sound[maxSoundCount];
}

void Audio::load()
{
	bgMusic.openFromFile("Assets/Audio/music.ogg");
	bgMusic.setLoop(true);
	if (playBgMusic) bgMusic.play();

	soundBuffers.load(SoundEffect::PlayerFire, "Assets/Audio/fire.wav");
	soundBuffers.load(SoundEffect::Explosion, "Assets/Audio/explosion.wav");
	soundBuffers.load(SoundEffect::PickUp, "Assets/Audio/pickup.wav");
}

void Audio::loadMenu()
{
	bgMusic.openFromFile("Assets/Audio/music.ogg");
	bgMusic.setLoop(true);
	if (playBgMusic) bgMusic.play();

	soundBuffers.load(SoundEffect::Select, "Assets/Audio/select.wav");
	
}



void Audio::playSound(SoundEffect::ID id)
{
	if (soundCount >= maxSoundCount)
		soundCount = 0;
	sounds[soundCount].setBuffer(soundBuffers.get(id));
	sounds[soundCount].play();
	soundCount++;
}

void Audio::setBgMusicStatus(bool _playBgMusic)
{
	playBgMusic = _playBgMusic;
}

