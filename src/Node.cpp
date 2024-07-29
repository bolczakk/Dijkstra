#include "Node.h"

Node::Node(sf::Vector2f pos, char label_, float radius) : label{ label_ } {
	this->setFillColor(sf::Color::Red);
	this->setPosition(pos);
	this->setRadius(radius);
	this->setOrigin(radius, radius);
}

bool Node::contains(sf::Vector2f mousePos) {
	if (this->getGlobalBounds().contains(mousePos) && this->clicked==false) {
		this->setFillColor(getRandomColor());
		return true;
	}
	return false;
}

sf::Color Node::getRandomColor() {
	static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> distribution(0, 255);

	int red = distribution(generator);
	int green = distribution(generator);
	int blue = distribution(generator);

	return sf::Color(red, green, blue);
}
