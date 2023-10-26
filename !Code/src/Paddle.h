#ifndef PONGSFML_PADDLE_H
#define PONGSFML_PADDLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector.h"


class Paddle
{
 public:
  Paddle(sf::RenderWindow& window);

  bool init(bool player_num, sf::Keyboard::Key _up, sf::Keyboard::Key _down);

  // void movePaddle(sf::Event event);
  // void stopPaddle(sf::Event event);      made redundant, movement handled in update in Paddles.cpp
  const sf::Sprite& getPlayer() const;
  void update(float dt);
  void aimovement(sf::Sprite ball, float dt);

 private:
  sf::Sprite player;
  int paddle_speed;
  sf::Texture paddle_texture;
  sf::Keyboard::Key up_key;
  sf::Keyboard::Key down_key;

  Vector movement;

  sf::RenderWindow& window;
};

#endif // PONGSFML_PADDLE_H
