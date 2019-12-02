#include "menu_state.hpp"
#include <iostream>
#include "play_state.hpp"
#include "texturemanager.hpp"

MenuState::MenuState(Game* game) {
  this->game = game;
  sf::View view_(sf::FloatRect(0, 0, this->game->window.getSize().x,
                               this->game->window.getSize().y));
  background_.setTexture(texture_manager.GetTexture("sprites/background.png"));
  background_.setScale(float(this->game->window.getSize().x) /
                           float(background_.getTexture()->getSize().x),
                       float(this->game->window.getSize().y) /
                           float(background_.getTexture()->getSize().y));

  if (!font_.loadFromFile("sprites/Arial.ttf")) {
    std::cout << "Failed to load font";
  }

  sf::Vector2f window_size = sf::Vector2f(this->game->window.getSize());

  buttons_.emplace("Play",
                   Button("Test", font_,
                          sf::Vector2f(window_size.x / 2, window_size.y / 2)));
}

void MenuState::Draw() {
  this->game->window.setView(view_);
  this->game->window.draw(background_);
  for (auto& button : buttons_) {
    this->game->window.draw(button.second);
  }
}

void MenuState::HandleInput() {
  sf::Event event;

  sf::Vector2f mouse_position = this->game->window.mapPixelToCoords(
      sf::Mouse::getPosition(this->game->window), view_);
  while (this->game->window.pollEvent(event)) {
    switch (event.type) {
      /* Close the window */
      case sf::Event::Closed: {
        game->window.close();
        break;
      }
      /* Resize the window */
      case sf::Event::Resized: {
        // view_.setSize(event.size.width, event.size.height);
        view_.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
        game->window.setView(view_);

        background_.setPosition(
            this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), view_));
        background_.setScale(float(event.size.width) /
                                 float(background_.getTexture()->getSize().x),
                             float(event.size.height) /
                                 float(background_.getTexture()->getSize().y));
        buttons_.at("Play").SetPosition(
            sf::Vector2f(event.size.width / 2, event.size.height / 2));

        break;
      }
      case sf::Event::MouseButtonPressed: {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (buttons_.at("Play").Contains(mouse_position)) {
            this->game->PushState(new PlayState(this->game));
          }
        }
        break;
      }
      case sf::Event::KeyPressed: {
        if (event.key.code == sf::Keyboard::Escape)
          this->game->PushState(new PlayState(this->game));
        break;
      }
      default:
        break;
    }
  }
}
