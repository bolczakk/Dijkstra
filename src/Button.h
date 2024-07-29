#pragma once
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button {
private:
	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, std::string text);
	void render(sf::RenderTarget* window) const;
	void update(const sf::Vector2f mousePos);
	const bool isPressed() const;
};

