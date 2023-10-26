#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Paddle.h"


enum class GameState
{
  MAINMENU,
  PLAYERGAME,
  P1VICTORY,
  P2VICTORY,
  AIGAME,
  PLAYERVICTORY,
  AIVICTORY,
  STORYINFO
};

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  sf::RenderWindow& window;

  GameState gameState;

 private:
  sf::Sprite ball;
  sf::Texture ball_texture;
  float speed = 500;
  sf::Font font;

  Paddle player1;
  Paddle player2;
  Vector ball_vector;
  sf::Clock collision_clock;

  bool ball_stationary = true;
  bool ball_going_up = true;

  sf::Text title_text;
  sf::Text menu_text;
  sf::Text playergame_option;
  sf::Text aigame_option;
  bool game_choice = true;

  sf::Text game_text;
  sf::Text p1_instructions;
  sf::Text p2_instructions;
  sf::Text win_instructions;
  sf::Text exit_instructions;

  int player1_score = 0;
  int player2_score = 0;
  sf::Text player1_scoreboard;
  sf::Text player2_scoreboard;
  std::string player1_score_string = "0";
  std::string player2_score_string = "0";

  sf::Text p1_victory;
  sf::Text p2_victory;
  sf::Text ai_name;
  sf::Text victory_text;
  sf::Text player_victory;
  sf::Text ai_victory;

  sf::Text story_title;
  sf::Text story_text;
  sf::Text doktor_ponguss_phd;
  sf::Text story_exit_instructions;
  sf::Text story_player_victory;
  sf::Text story_ai_victory;

  sf::Sprite background;
  sf::Texture background_texture;
};

#endif // PONG_GAME_H
