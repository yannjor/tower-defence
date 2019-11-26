#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../enemy/enemy.hpp"
#include "../map/map.hpp"
#include "../tower/tower.hpp"

class Game {
 public:
  Game();
  void Run();
  void DrawAll();
  void DrawMap();
  void DrawEnemies();
  void DrawTowers();
  void Tick();
  void FindEnemies();
  int GetTileSize() const;

 private:
  Map map_;
  sf::RenderWindow window_;
  sf::View view_;
  std::map<const std::string, sf::Texture> textures_;
  std::vector<Enemy> enemies_;
  std::vector<Tower> towers_;
  sf::Clock clock_;
};