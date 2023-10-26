#include "Paddle.h"

Paddle::Paddle(sf::RenderWindow& game_window) : window(game_window)
{
}

bool Paddle::init(bool player_num, sf::Keyboard::Key _up, sf::Keyboard::Key _down)
{
  up_key = _up;
  down_key = _down;
  movement.x_direction = 0;
  movement.y_direction = 0;
  paddle_speed = 700;

  if (player_num)
  {
    if (!paddle_texture.loadFromFile("Data/Images/paddleBlue.png"))
    {
      std::cout << "P1 texture did not load \n";
      return false;
    }
    player.setTexture(paddle_texture);
    player.setPosition(100,333);
  }
  else
  {
    if (!paddle_texture.loadFromFile("Data/Images/paddleRed.png"))
    {
      std::cout << "P2 texture did not load \n";
    }
    player.setTexture(paddle_texture);
    player.setPosition(window.getSize().x - 100 - player.getGlobalBounds().width,333);
  }

  player.setScale(1, 1);
  return true;
}

const sf::Sprite& Paddle::getPlayer() const
{
  return player;
}

void Paddle::update(float dt)
{
  if (sf::Keyboard::isKeyPressed(up_key))
  {
    movement.y_direction = -1;
  }
  else if (sf::Keyboard::isKeyPressed(down_key))
  {
    movement.y_direction = 1;
  }
  else
  {
    movement.y_direction = 0;
  }

  player.move(0, paddle_speed * movement.y_direction * dt);
  if (player.getPosition().y < 0)
  {
    player.setPosition(player.getPosition().x, 0);
  }
  if (player.getPosition().y > window.getSize().y - player.getGlobalBounds().height)
  {
    player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
  }
}

void Paddle::aimovement(sf::Sprite ball, float dt)
{
  float ball_position = ball.getPosition().y + ball.getGlobalBounds().height / 2;
  float ai_position = player.getPosition().y + player.getGlobalBounds().height / 2;

  if (ai_position - ball_position < 5 && ai_position - ball_position > -5)
  {
    player.setPosition(player.getPosition().x, ball_position - player.getGlobalBounds().height / 2);
  }
  else
  {
    if (ai_position > ball_position)
    {
      movement.y_direction = -1;
      player.move(0,(paddle_speed - 200) * movement.y_direction * dt);
    }
    else
    {
      movement.y_direction = 1;
      player.move(0,(paddle_speed - 200) * movement.y_direction * dt);
    }
  }

  if (player.getPosition().y < 0)
  {
    player.setPosition(player.getPosition().x, 0);
  }
  if (player.getPosition().y > window.getSize().y - player.getGlobalBounds().height)
  {
    player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
  }
}