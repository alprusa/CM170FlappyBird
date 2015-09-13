#include "CollisionDetection.h"

bool collisionCheck(sf::Sprite s1, int s1Width, int s1Height, sf::Sprite s2, int s2Width, int s2Height){
	return (s1.getPosition().x < (s2.getPosition().x + s2Width) && (s1.getPosition().x + s1Width) > s2.getPosition().x &&
		s1.getPosition().y < (s2.getPosition().y + s2Height) && (s1.getPosition().y + s1Height) > s2.getPosition().y);
}
