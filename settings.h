#pragma once
#include <SFML/Graphics.hpp>

const float WINDOW_WIDTH = 1200;
const float WINDOW_HEIGHT = 900;
const std::string WINDOW_TITLE = "SFML Asteroids P53122";
const float FPS = 60.f;

const std::string Player_File_Name = "images\\spaceShips.png";
const float PI = 3.14159265358;

const sf::Vector2f FonStartPos{ 0, 0 };
const std::string Fon_File_Name = "images\\Fon.jpg";
const float Fon_offset = 50.f;

const float Top_Border = -300.f;
const float Bottom_Border = 1200.f;
const float Left_Border = -300.f;
const float Right_Border = 1500.f;

const std::string Bullets_File_Name = "images\\spaceMissiles_006.png";
const float Bullet_speed = 15.f;

const int fire_cooldown = 200.f;
float Player_Max_Speed = 10.f;
float dv = 0.5;
const int Player_max_hp = 100;
const int CHAR_SIZE = 48;
const sf::Vector2f HP_text_pos(0.f, 0.f);
const sf::Vector2f Score_text_pos(0.f, 40.f);
const float FRAME_WIDTH = 150;
const float FRAME_HEIGHT = 20;
const sf::Vector2f Game_text_pos(500.f, 400.f);

const std::string KABOOM_FILE_NAME{ "images\\Kaboom.png" };
const std::string  MEDKIT_FILE_NAME{ "images\\MedKit.png" };
const std::string SPEED_BOOST_FILE_NAME{ "images\\Speed_boost.png" };

const int BONUS_RANGE = 10000;
const int BONUS_CHANCE = 500;
const int METEOR_TYPES_QTY = 8;
const size_t METEOR_QTY = 20;

const int bonus_oper_time{ 5000 };