#include "Line.h"

Line::Line(const sf::Vector2f pos1, const sf::Vector2f pos2, sf::Color clr) {
    this->line[0].position = pos1;
    this->line[0].color = clr;

    this->line[1].position = pos2;
    this->line[1].color = clr;

    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    this->distance = std::sqrt(dx * dx + dy * dy);
}

void Line::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(line, states);
}
