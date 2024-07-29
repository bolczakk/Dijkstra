#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Node : public sf::CircleShape {
public:
	Node(sf::Vector2f pos, char label_, float radius = 10.0f);
	std::vector<Node*> neighbours;
	bool contains(sf::Vector2f mousePos);
	sf::Color getRandomColor();
	bool clicked = false;
private:
	char label;
};