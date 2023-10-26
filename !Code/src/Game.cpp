#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window), player1(game_window), player2(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
}

bool Game::init()
{
  gameState = GameState::MAINMENU;

  // initialise ball vector
  ball_vector.x_direction = 1;
  ball_vector.y_direction = 1;
  ball_vector.normalise();

  // initialise background
  if (!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background.setTexture(background_texture);
  background.setScale(2,2);

  // initialise ball sprite
  if (!ball_texture.loadFromFile("Data/Images/ball.png"))
  {
    std::cout << "ball texture did not load \n";
  }
  ball.setTexture(ball_texture);
  ball.setPosition(515, 333);
  ball.setScale(0.4,0.4);

  // initialise text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  // initialise paddles
  player1.init(true, sf::Keyboard::W, sf::Keyboard::S);
  player2.init(false, sf::Keyboard::Up, sf::Keyboard::Down);

  // initialise menu
  title_text.setString("- PONG DELUXE -");
  title_text.setFont(font);
  title_text.setCharacterSize(125);
  title_text.setFillColor(sf::Color(117, 60, 139, 255));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    window.getSize().y / 5.5 - title_text.getGlobalBounds().height / 2);
  menu_text.setString("Use the arrow keys to select a game mode\n"
                      "                     Press Enter to start!");
  menu_text.setFont(font);
  menu_text.setCharacterSize(40);
  menu_text.setFillColor(sf::Color(255, 255, 255, 255));
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 1.15 - menu_text.getGlobalBounds().height / 2);
  playergame_option.setString("> 2 Players <");
  playergame_option.setFont(font);
  playergame_option.setCharacterSize(60);
  playergame_option.setFillColor(sf::Color(80, 175, 60, 255));
  playergame_option.setPosition(
    window.getSize().x / 4 - playergame_option.getGlobalBounds().width / 2,
    window.getSize().y / 1.75 - playergame_option.getGlobalBounds().height / 2);
  aigame_option.setString("1 Player vs AI");
  aigame_option.setFont(font);
  aigame_option.setCharacterSize(60);
  aigame_option.setFillColor(sf::Color(255, 255, 255, 255));
  aigame_option.setPosition(
    window.getSize().x / 1.5 - aigame_option.getGlobalBounds().width / 2,
    window.getSize().y / 1.75 - aigame_option.getGlobalBounds().height / 2);

  // initialise text
  game_text.setString("Press Space to launch the ball!");
  game_text.setFont(font);
  game_text.setCharacterSize(40);
  game_text.setFillColor(sf::Color(0,0,0,255));
  game_text.setPosition(
    window.getSize().x / 2 - game_text.getGlobalBounds().width / 2,
    window.getSize().y / 1.5 - game_text.getGlobalBounds().height / 2);
  p1_instructions.setString("W: Move up\n"
                            "S: Move down");
  p1_instructions.setFont(font);
  p1_instructions.setCharacterSize(25);
  p1_instructions.setFillColor(sf::Color(0,0,0,255));
  p1_instructions.setPosition(
    window.getSize().x / 3 - p1_instructions.getGlobalBounds().width / 2,
    window.getSize().y / 10 - p1_instructions.getGlobalBounds().height / 2);
  p2_instructions.setString("Up: Move up\n"
                            "Down: Move down");
  p2_instructions.setFont(font);
  p2_instructions.setCharacterSize(25);
  p2_instructions.setFillColor(sf::Color(0,0,0,255));
  p2_instructions.setPosition(
    window.getSize().x / 1.5 - p2_instructions.getGlobalBounds().width / 2,
    window.getSize().y / 10 - p2_instructions.getGlobalBounds().height / 2);
  ai_name.setString("Doktor Ponguss PhD");
  ai_name.setFont(font);
  ai_name.setCharacterSize(35);
  ai_name.setFillColor(sf::Color(0,0,0,255));
  ai_name.setPosition(
    window.getSize().x / 1.45 - ai_name.getGlobalBounds().width / 2,
    window.getSize().y / 10 - ai_name.getGlobalBounds().height / 2);
  exit_instructions.setString("Press Escape to quit the game");
  exit_instructions.setFont(font);
  exit_instructions.setCharacterSize(30);
  exit_instructions.setFillColor(sf::Color(0,0,0,255));
  exit_instructions.setPosition(
    window.getSize().x / 2 - exit_instructions.getGlobalBounds().width / 2,
    window.getSize().y / 1.2 - exit_instructions.getGlobalBounds().height / 2);
  win_instructions.setString("Get to 5 points to win!");
  win_instructions.setFont(font);
  win_instructions.setCharacterSize(30);
  win_instructions.setFillColor(sf::Color(0,0,0,255));
  win_instructions.setPosition(
    window.getSize().x / 2 - win_instructions.getGlobalBounds().width / 2,
    window.getSize().y / 1.3 - win_instructions.getGlobalBounds().height / 2);

  // initialise story text
  story_title.setString("STORY");
  story_title.setFont(font);
  story_title.setCharacterSize(100);
  story_title.setFillColor(sf::Color(117, 60, 139,255));
  story_title.setPosition(window.getSize().x / 2 - story_title.getGlobalBounds().width / 2,
                          window.getSize().y / 8 - story_title.getGlobalBounds().height / 2);
  story_text.setString("War has enveloped the land of Pong. The two mighty clans of\n"
                       "Pong, the Blue Barons and the Red Regals, have both been\n"
                       "brought to ruin by the evil                                      , a madman\n"
                       "from the Red Regals. Doktor Ponguss PhD (he's very proud of\n"
                       "his doctorate) now stands as the mightiest warrior in all\n"
                       "the land, ready to destroy it with a single bounce of a ball,\n"
                       "but the legendary Blue Bastion stands in his way to end\n"
                       "the war once and for all. Go forth, Bastion, and defeat\n"
                       "Doktor Ponguss PhD to save the world of Pong from evil!");
  story_text.setFont(font);
  story_text.setCharacterSize(30);
  story_text.setFillColor(sf::Color(255, 255, 255,255));
  story_text.setPosition(window.getSize().x / 2 - story_text.getGlobalBounds().width / 2,
                         window.getSize().y / 1.75 - story_text.getGlobalBounds().height / 2);
  doktor_ponguss_phd.setString("Doktor Ponguss PhD");
  doktor_ponguss_phd.setFont(font);
  doktor_ponguss_phd.setCharacterSize(30);
  doktor_ponguss_phd.setFillColor(sf::Color(117, 60, 139,255));
  doktor_ponguss_phd.setPosition(window.getSize().x / 1.7225 - doktor_ponguss_phd.getGlobalBounds().width / 2,
                             window.getSize().y / 2.181 - doktor_ponguss_phd.getGlobalBounds().height / 2);
  story_exit_instructions.setString("Press Enter to begin the fight!");
  story_exit_instructions.setFont(font);
  story_exit_instructions.setCharacterSize(40);
  story_exit_instructions.setFillColor(sf::Color(255, 255, 255,255));
  story_exit_instructions.setPosition(window.getSize().x / 2 - story_exit_instructions.getGlobalBounds().width / 2,
                                      window.getSize().y / 1.1 - story_exit_instructions.getGlobalBounds().height / 2);

  // initialise scores
  player1_scoreboard.setString(player1_score_string);
  player1_scoreboard.setFont(font);
  player1_scoreboard.setCharacterSize(100);
  player1_scoreboard.setFillColor(sf::Color(75, 188, 243, 255));
  player1_scoreboard.setPosition(
      window.getSize().x / 3 - player1_scoreboard.getGlobalBounds().width / 2,
      window.getSize().y / 5 - player1_scoreboard.getGlobalBounds().height / 2);
  player2_scoreboard.setString(player2_score_string);
  player2_scoreboard.setFont(font);
  player2_scoreboard.setCharacterSize(100);
  player2_scoreboard.setFillColor(sf::Color(243,52,52,255));
  player2_scoreboard.setPosition(
    window.getSize().x / 1.5 - player2_scoreboard.getGlobalBounds().width / 2,
    window.getSize().y / 5 - player2_scoreboard.getGlobalBounds().height / 2);

  // initialise victory screens
  p1_victory.setString("Player 1 wins!");
  p1_victory.setFont(font);
  p1_victory.setCharacterSize(100);
  p1_victory.setFillColor(sf::Color(75,188,243,255));
  p1_victory.setPosition(window.getSize().x / 2 - p1_victory.getGlobalBounds().width / 2,
                         window.getSize().y / 3.5 - p1_victory.getGlobalBounds().height / 2);
  p2_victory.setString("Player 2 wins!");
  p2_victory.setFont(font);
  p2_victory.setCharacterSize(100);
  p2_victory.setFillColor(sf::Color(243,52,52,255));
  p2_victory.setPosition(window.getSize().x / 2 - p2_victory.getGlobalBounds().width / 2,
                         window.getSize().y / 3.5 - p2_victory.getGlobalBounds().height / 2);
  player_victory.setString("YOU WIN!!!");
  player_victory.setFont(font);
  player_victory.setCharacterSize(150);
  player_victory.setFillColor(sf::Color(80, 175, 60,255));
  player_victory.setPosition(window.getSize().x / 2 - player_victory.getGlobalBounds().width / 2,
                             window.getSize().y / 3.5 - player_victory.getGlobalBounds().height / 2);
  story_player_victory.setString("You've saved the land of Pong, congratulations!");
  story_player_victory.setFont(font);
  story_player_victory.setCharacterSize(40);
  story_player_victory.setFillColor(sf::Color(255,255,255,255));
  story_player_victory.setPosition(window.getSize().x / 2 - story_player_victory.getGlobalBounds().width / 2,
                                   window.getSize().y / 1.75 - story_player_victory.getGlobalBounds().height / 2);
  ai_victory.setString("You lose...");
  ai_victory.setFont(font);
  ai_victory.setCharacterSize(100);
  ai_victory.setFillColor(sf::Color(255, 255, 255,255));
  ai_victory.setPosition(window.getSize().x / 2 - ai_victory.getGlobalBounds().width / 2,
                         window.getSize().y / 3.5 - ai_victory.getGlobalBounds().height / 2);
  story_ai_victory.setString(" 'Mwahahaha! You can never defeat me!\n"
                             "I have a PhD in Pong Science, by the way!'");
  story_ai_victory.setFont(font);
  story_ai_victory.setCharacterSize(40);
  story_ai_victory.setFillColor(sf::Color(117, 60, 139,255));
  story_ai_victory.setPosition(window.getSize().x / 2 - story_ai_victory.getGlobalBounds().width / 2,
                               window.getSize().y / 1.75 - story_ai_victory.getGlobalBounds().height / 2);
  victory_text.setString("Press Enter to return to the main menu");
  victory_text.setFont(font);
  victory_text.setCharacterSize(40);
  victory_text.setFillColor(sf::Color(255,255,255,255));
  victory_text.setPosition(window.getSize().x / 2 - victory_text.getGlobalBounds().width / 2,
                           window.getSize().y / 1.25 - victory_text.getGlobalBounds().height / 2);

  collision_clock.restart();
  return true;
}

void Game::update(float dt)
{
  if (gameState == GameState::PLAYERGAME || gameState == GameState::AIGAME)
  {
    player1.update(dt);

    if (gameState == GameState::PLAYERGAME)
    {
      player2.update(dt);
    }
    else
    {
      player2.aimovement(ball, dt);
    }

    if (ball_stationary == true)
      ball.setPosition(515, 333);
    else
    {
      // COLLISION CODE
      if (collision_clock.getElapsedTime().asMilliseconds() > 150)
      {
        if (
          player1.getPlayer().getPosition().x +
            player1.getPlayer().getGlobalBounds().width >=
          ball.getPosition().x)
        {
          if (
            ball.getPosition().x + ball.getGlobalBounds().width >=
            player1.getPlayer().getPosition().x)
          {
            if (
              player1.getPlayer().getPosition().y +
                player1.getPlayer().getGlobalBounds().height >=
              ball.getPosition().y)
            {
              if (
                ball.getPosition().y + ball.getGlobalBounds().height >=
                player1.getPlayer().getPosition().y)
              {
                collision_clock.restart();
                std::cout << "PING\n";
                ball_vector.x_direction = -ball_vector.x_direction;
                speed = speed * 1.1;
              }
            }
          }
        }
        if (
          player2.getPlayer().getPosition().x +
            player2.getPlayer().getGlobalBounds().width >=
          ball.getPosition().x)
        {
          if (
            ball.getPosition().x + ball.getGlobalBounds().width >=
            player2.getPlayer().getPosition().x)
          {
            if (
              player2.getPlayer().getPosition().y +
                player2.getPlayer().getGlobalBounds().height >=
              ball.getPosition().y)
            {
              if (
                ball.getPosition().y + ball.getGlobalBounds().height >=
                player2.getPlayer().getPosition().y)
              {
                collision_clock.restart();
                std::cout << "PONG\n";
                ball_vector.x_direction = -ball_vector.x_direction;
                speed = speed * 1.1;
              }
            }
          }
        }
      }

      if (ball_going_up)
      {
        ball.move(0 * speed * dt, 10.0f);
        ball.setTextureRect(sf::IntRect(
          0, 0, ball.getLocalBounds().width, ball.getLocalBounds().height));
      }
      else
      {
        ball.move(0 * speed * dt, -10.0f);
        ball.setTextureRect(sf::IntRect(
          0, 0, ball.getLocalBounds().width, ball.getLocalBounds().height));
      }

      ball.move(ball_vector.x_direction * speed * dt, ball_vector.y_direction);

      // checking window collision - scoring points and randomising vectors on ball respawn
      if (ball.getPosition().x >
          (window.getSize().x - ball.getGlobalBounds().width))
      {
        player1_score++;
        player1_score_string = std::to_string(player1_score);
        player1_scoreboard.setString(player1_score_string);
        speed = 500;

        ball.setPosition(515, 333);
        ball_stationary = true;
        ball_vector.x_direction = (rand() % 16) - 6;
        while (ball_vector.x_direction >= -3 && ball_vector.x_direction <= 3)
        {
          ball_vector.x_direction = (rand() % 16) - 6;
        }
        ball_vector.y_direction = (rand() % 16) - 6;
        while (ball_vector.y_direction >= -3 && ball_vector.y_direction <= 3)
        {
          ball_vector.y_direction = (rand() % 16) - 6;
        }
        ball_vector.normalise();
      }
      if (ball.getPosition().x < 0)
      {
        player2_score++;
        player2_score_string = std::to_string(player2_score);
        player2_scoreboard.setString(player2_score_string);
        speed = 500;

        ball.setPosition(515, 333);
        ball_stationary = true;
        ball_vector.x_direction = (rand() % 16) - 6;
        while (ball_vector.x_direction >= -3 && ball_vector.x_direction <= 3)
        {
          ball_vector.x_direction = (rand() % 16) - 6;
        }
        ball_vector.y_direction = (rand() % 16) - 6;
        while (ball_vector.y_direction >= -3 && ball_vector.y_direction <= 3)
        {
          ball_vector.y_direction = (rand() % 16) - 6;
        }
        ball_vector.normalise();
      }
      // checking window collision - reversing y vector when ball hits top and bottom
      if (ball.getPosition().y < 0) // top of screen
      {
        ball.setPosition(ball.getPosition().x, 0);
        ball_going_up = !ball_going_up;
      }
      if (ball.getPosition().y > window.getSize().y - ball.getGlobalBounds().height) // bottom of screen
      {
        ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getGlobalBounds().height);
        ball_going_up = !ball_going_up;
      }
    }

    // player scores
    if (gameState == GameState::PLAYERGAME)
    {
      if (player1_score == 5)
      {
        gameState = GameState::P1VICTORY;
      }
      if (player2_score == 5)
      {
        gameState = GameState::P2VICTORY;
      }
    }
    else
    {
      if (player1_score == 5)
      {
        gameState = GameState::PLAYERVICTORY;
      }
      if (player2_score == 5)
      {
        gameState = GameState::AIVICTORY;
      }
    }
  }
}

void Game::render()
{
  if (gameState == GameState::PLAYERGAME || gameState == GameState::AIGAME)
  {
    window.draw(background);
    window.draw(player1_scoreboard);
    window.draw(player2_scoreboard);
    window.draw(ball);
    window.draw(player1.getPlayer());
    window.draw(player2.getPlayer());
    if (ball_stationary == true)
    {
      window.draw(game_text);
      window.draw(p1_instructions);
      window.draw(exit_instructions);
      window.draw(win_instructions);
      if (gameState == GameState::PLAYERGAME)
      {
        window.draw(p2_instructions);
      }
      else if (gameState == GameState::AIGAME)
      {
        window.draw(ai_name);
      }
    }
  }
  else if (gameState == GameState::MAINMENU)
  {
    window.draw(title_text);
    window.draw(menu_text);
    window.draw(playergame_option);
    window.draw(aigame_option);
  }
  else if (gameState == GameState::P1VICTORY)
  {
    window.draw(p1_victory);
    window.draw(victory_text);
  }
  else if (gameState == GameState::P2VICTORY)
  {
    window.draw(p2_victory);
    window.draw(victory_text);
  }
  else if (gameState == GameState::PLAYERVICTORY)
  {
    window.draw(player_victory);
    window.draw(story_player_victory);
    window.draw(victory_text);
  }
  else if (gameState == GameState::AIVICTORY)
  {
    window.draw(ai_victory);
    window.draw(story_ai_victory);
    window.draw(victory_text);
  }
  else
  {
    window.draw(story_title);
    window.draw(story_text);
    window.draw(doktor_ponguss_phd);
    window.draw(story_exit_instructions);
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (gameState == GameState::MAINMENU)
  {
    if ((event.key.code == sf::Keyboard::Left) ||
        (event.key.code == sf::Keyboard::Right))
    {
      game_choice = !game_choice;
      if (game_choice)
      {
        playergame_option.setString("> 2 Players <");
        playergame_option.setFillColor(sf::Color(80, 175, 60, 255));
        playergame_option.setPosition(
          window.getSize().x / 4 - playergame_option.getGlobalBounds().width / 2,
          window.getSize().y / 1.75 - playergame_option.getGlobalBounds().height / 2);
        aigame_option.setString("1 Player vs AI");
        aigame_option.setFillColor(sf::Color(255, 255, 255, 255));
        aigame_option.setPosition(
          window.getSize().x / 1.5 - aigame_option.getGlobalBounds().width / 2,
          window.getSize().y / 1.75 - aigame_option.getGlobalBounds().height / 2);
      }
      else
      {
        playergame_option.setString("2 Players");
        playergame_option.setFillColor(sf::Color(255, 255, 255, 255));
        playergame_option.setPosition(
          window.getSize().x / 4 - playergame_option.getGlobalBounds().width / 2,
          window.getSize().y / 1.75 - playergame_option.getGlobalBounds().height / 2);
        aigame_option.setString("> 1 Player vs AI <");
        aigame_option.setFillColor(sf::Color(80, 175, 60, 255));
        aigame_option.setPosition(
          window.getSize().x / 1.5 - aigame_option.getGlobalBounds().width / 2,
          window.getSize().y / 1.75 - aigame_option.getGlobalBounds().height / 2);
      }
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (game_choice)
      {
        gameState = GameState::PLAYERGAME;
      }
      else
      {
        gameState = GameState::STORYINFO;
      }
    }
  }
  else if (gameState == GameState::STORYINFO)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      gameState = GameState::AIGAME;
    }
  }
  else if (gameState == GameState::PLAYERGAME || gameState == GameState::AIGAME)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      if (ball_stationary == true)
      {
        ball_stationary = false;
      }
    }
  }
  else
  {
  }

  if (gameState == GameState::P1VICTORY || gameState == GameState::P2VICTORY ||
      gameState == GameState::PLAYERVICTORY || gameState == GameState::AIVICTORY)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      gameState = GameState::MAINMENU;
      player1_score = 0;
      player1_score_string = std::to_string(player1_score);
      player1_scoreboard.setString(player1_score_string);
      player2_score = 0;
      player2_score_string = std::to_string(player2_score);
      player2_scoreboard.setString(player2_score_string);
      speed = 500;
    }
  }
}
