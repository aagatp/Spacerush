#pragma once

namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Game,
		Entities,
		Space,
		Explosion,
		Particle,
		FinishLine,
	};
}

namespace Fonts
{
	enum ID
	{
		Game,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Player1Fire,
		Player2Fire,
		Explosion1,
		Explosion2,
		Player1Missile,
		Player2Missile,
		CollectPickup,
		Button,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;