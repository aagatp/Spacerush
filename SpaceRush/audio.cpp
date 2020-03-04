#include "audio.h"

Audio::Audio(int maxSoundCount = 100) :maxSoundCount(maxSoundCount)
{
	sounds = new sf::Sound[maxSoundCount];
}

Audio::~Audio()
{
	delete[] sounds;
}

void Audio::load()
{
	bgMusic.openFromFile("Assets/Audio/music.wav");
	bgMusic.setLoop(true);
	if (playBgMusic) bgMusic.play();
	bgMusic.setVolume(5.0f);

	soundBuffers.load(SoundEffect::Engine, "Assets/Audio/engine.wav");
	soundBuffers.load(SoundEffect::PlayerFire, "Assets/Audio/fire.wav");
	soundBuffers.load(SoundEffect::Explosion, "Assets/Audio/explosion.wav");
	soundBuffers.load(SoundEffect::PickUp, "Assets/Audio/pickup.wav");
	soundBuffers.load(SoundEffect::mineExplosion, "Assets/Audio/mineExplosion.wav");
}

void Audio::loadMenu()
{
	bgMusic.openFromFile("Assets/Audio/music.wav");
	bgMusic.setLoop(true);
	bgMusic.setVolume(5.0f);
	if (playBgMusic) bgMusic.play();

	soundBuffers.load(SoundEffect::Select, "Assets/Audio/select.wav");
}

sf::Sound& Audio::playSound(SoundEffect::ID id)
{
	if (soundCount >= maxSoundCount)
		soundCount = 0;
	sounds[soundCount].setBuffer(soundBuffers.get(id));
	sounds[soundCount].play();
	sounds[soundCount].setVolume(volume);
	return sounds[soundCount++];
}

void Audio::setBgMusicStatus(bool _playBgMusic)
{
	playBgMusic = _playBgMusic;
}