#pragma once
#include <SFML/Graphics.hpp>
class Line : public sf::Drawable {
public:
	Line(const sf::Vector2f pos1, const sf::Vector2f pos2, const sf::Color clr);
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
	float distance = 0.0f;
private:
	sf::VertexArray line{ sf::LinesStrip, 2 };
};

