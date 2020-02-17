#pragma once

#include "resourceidentifiers.h"
#include "resourceholder.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SceneManager;

class Scene
{
public:
    Scene(SceneManager& m_sceneManager, sf::RenderWindow& m_window)
        : sceneManager{ m_sceneManager }
        , window{ m_window } 
    {
        bgTextures.load(Textures::Space, "Assets/background.jpg");
        fontholder.load(Fonts::Game, "Assets/gamefont.ttf");
    }

    virtual ~Scene() {}

    virtual void processEvents() = 0;
    virtual void update(const sf::Time& dt) = 0;
    virtual void draw() = 0;
protected:
    SceneManager& sceneManager;
    sf::RenderWindow& window;
    FontHolder fontholder;
    TextureHolder bgTextures;
};