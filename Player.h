#pragma once
#include "settings.h"
#include "cmath"
#include <list>
#include "Bullet.h"
#include "Textobj.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int angle;
	float speed, speedx, speedy;
	std::list<Bullet*> bullets;
	sf::Clock timer;
	int cd = fire_cooldown;
	int hp = Player_max_hp;
	int score = 0;
	std::string GameOver = "GAME  OVER";
	TextObj  score_text, GameOver_text;
	enum GameStatus { Play, Game_Over };
	GameStatus game = Play;
	int speed_bonus_act_time, previous_fire_time;
	bool speed_bonus_act = false;
public:
	Player() : score_text(std::to_string(score), Score_text_pos), GameOver_text(GameOver, Game_text_pos) {
		texture.loadFromFile(Player_File_Name);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		angle = 0;
		speed = 0.f;
		timer.restart();
		previous_fire_time = timer.getElapsedTime().asMilliseconds();
	}

	void update() {
		if (sprite.getPosition().x <= 0 + Fon_offset) {
			sprite.setPosition(0 + Fon_offset, sprite.getPosition().y);
		}
		if (sprite.getPosition().x >= WINDOW_WIDTH - Fon_offset) {
			sprite.setPosition(WINDOW_WIDTH - Fon_offset, sprite.getPosition().y);
		}
		if (sprite.getPosition().y <= 0 + Fon_offset) {
			sprite.setPosition(sprite.getPosition().x, 0 + Fon_offset);
		}
		if (sprite.getPosition().y >= WINDOW_HEIGHT - Fon_offset) {
			sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - Fon_offset);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 3;
		}
		sprite.setRotation(angle);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			speed += dv;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			speed -= dv / 2;
		}

		if (speed < 0) speed = 0.f;
		else if (speed > 2 * Player_Max_Speed) speed = 2 * Player_Max_Speed;

		speedx = speed * sin(angle * PI / 180);
		speedy = -speed * cos(angle * PI / 180);
		sprite.move(speedx, speedy);
		fire();
		for (auto bullet : bullets) {
			bullet->update();
		}
		score_text.update("score:" + std::to_string(score));
		int currTime = timer.getElapsedTime().asMilliseconds();
		if (currTime - speed_bonus_act_time > bonus_oper_time && speed_bonus_act) {
			speed_bonus_act = false;
			dv /= 2; Player_Max_Speed /= 2;
		}
	}

	void fire() {
		int currTime = timer.getElapsedTime().asMilliseconds();
		if (currTime - previous_fire_time > fire_cooldown) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				auto bullet = new Bullet(sprite.getPosition(), angle);
				bullets.push_back(bullet);
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		switch (game) {
		case Game_Over: {
			window.clear();
			GameOver_text.draw(window);
			break;
		}
		case Play: {
			window.draw(sprite);
			for (auto bullet : bullets) {
				window.draw(bullet->getSprite());
			}

			window.draw(sprite);
			score_text.draw(window);

			if (hp <= 0) {
				game = Game_Over;
			}
		}
		}
	}
	void Score(int Up) { score += Up; }

	void decreaseHp(int damage) { hp -= damage; }

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

	std::list<Bullet*>* getBullets() { return &bullets; }

	int getHp() { return hp; }

	void FIRE_UP();

	void HP_UP(int hp);

	void Speed_Boost();
};
void Player::HP_UP(int hp) { this->hp += hp; }
void Player::Speed_Boost() {
	speed_bonus_act = true;
	dv *= 2; Player_Max_Speed *= 2;
	speed_bonus_act_time = timer.getElapsedTime().asMilliseconds();
}