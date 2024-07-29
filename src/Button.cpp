#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, std::string text) : buttonState(BTN_IDLE) {
	this->shape.setSize(size);
	this->shape.setOrigin(size.x / 2.0f, size.y / 2.0f);
	this->shape.setPosition(pos);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(28);
	this->text.setPosition(this->shape.getPosition().x - this->text.getGlobalBounds().width/2.0f, this->shape.getPosition().y - this->text.getGlobalBounds().height/2.0f);

	this->idleColor = sf::Color(173, 255, 47);
	this->hoverColor = sf::Color::Green;
	this->activeColor = sf::Color(124,252,0);

	this->shape.setFillColor(this->idleColor);
}

void Button::render(sf::RenderTarget* window) const {
	window->draw(this->shape);
	window->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos) {
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
		}
	}
	switch (this->buttonState) {
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		break;
	}
}

const bool Button::isPressed() const {
	if (this->buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}
