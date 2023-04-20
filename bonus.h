#pragma once
#include "settings.h"
#include "Player.h"
class Bonus {
public:
	enum BonusType { KABOOM, MEDKIT, SPEED_BOOST, MAX_BONUS_TYPE };
	Bonus(sf::Vector2f meteorPos,size_t bonustype);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	void update();
	void setDel();
	bool isToDel();
	void draw(sf::RenderWindow& window);
	bool offScreen();
	void act(Player& player);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	BonusType type;
	sf::Clock timer;
	bool del = false;
};

Bonus::Bonus(sf::Vector2f meteorPos,size_t bonusType) {
	type = (BonusType)bonusType;
	switch (type) {
	case KABOOM:
		this->type = type;
		texture.loadFromFile(KABOOM_FILE_NAME);
		break;

	case MEDKIT:
		this->type = type;
		texture.loadFromFile(MEDKIT_FILE_NAME);
		break;

	case  SPEED_BOOST:
		this->type = type;
		texture.loadFromFile(SPEED_BOOST_FILE_NAME);
		break;
	}
	sprite.setTexture(texture);
	sprite.setPosition(meteorPos);
	timer.restart();
}

void Bonus::update() {
	int now = timer.getElapsedTime().asMilliseconds();
	if (now > 5000) {
		del = true;
	}
}

void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }

sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }

bool Bonus::offScreen() {
	if (sprite.getPosition().y > WINDOW_HEIGHT) return true;
	return false;
}
bool Bonus::isToDel() { return del; }

void Bonus::setDel() { del = true; }

void Bonus::act(Player& player) {
	switch (type) {
	case  KABOOM:
		
		break;
	case MEDKIT:
		player.HP_UP(50);
		break;
	case SPEED_BOOST:
		player.Speed_Boost();
		break;
	}
}
