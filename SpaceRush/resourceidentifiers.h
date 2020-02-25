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
		Space,
		BlueSpaceship,
		RedSpaceship,
		BlueBullet,
		RedBullet,
		BlueMissile,
		RedMissile,
		Explosion,
		Asteroids,
		CollectPickup,
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
		PlayerFire,
		Explosion,
		PlayerMissile,
		MissilePickUp,
		Button,
		PickUp,
		Select,
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