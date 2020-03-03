#include <SFML/Graphics.hpp>
#include <map>
#include "BitmaskManager.h"
namespace Collision
{
	static BitmaskManager Bitmasks;

	template <typename T1, typename T2>
	bool PixelPerfectTest(std::shared_ptr<T1>& sp1, std::shared_ptr<T2>& sp2, sf::Uint8 AlphaLimit)
	{
		sf::FloatRect Intersection;
		if (sp1->getBounds().intersects(sp2->getBounds(), Intersection)) {
			sf::IntRect O1SubRect = sp1->getTextureRect();
			sf::IntRect O2SubRect = sp2->getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(sp1->getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(sp2->getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = sp1->getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = sp2->getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's sub rect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, sp1->getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit&&
							Bitmasks.GetPixel(mask2, sp2->getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
						{
							return true;
						}

					}
				}
			}
		}
		return false;
	}


}