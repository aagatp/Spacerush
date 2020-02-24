#include "asteroids.h"
#include "spaceship.h"
#include "bullet.h"
#include "pickup.h"
namespace Collision {
    //////
    /// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
    /// Supports scaling and rotation
    /// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
    /// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
    ///
    /// This functions creates bitmasks of the textures of the two sprites by
    /// downloading the textures from the graphics card to memory -> SLOW!
    /// You can avoid this by using the "CreateTextureAndBitmask" function
    //////
    bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr<Spaceship>& sp2, sf::Uint8 AlphaLimit = 0);
    bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr< Bullet>& b, sf::Uint8 AlphaLimit = 0);
    bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr<Asteroid>& as, sf::Uint8 AlphaLimit = 0);
    bool PixelPerfectTest(std::shared_ptr<Asteroid>& as, std::shared_ptr< Bullet>& b, sf::Uint8 AlphaLimit = 0);
    bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, sf::Sprite& p, sf::Uint8 AlphaLimit = 0);
}
