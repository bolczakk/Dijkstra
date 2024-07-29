#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Line.h"
#include "Button.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <random>

class Engine {
private:
    enum states { MENU = 0, MAPPING, ALGORITHM, END };

    sf::RenderWindow window;
    std::vector<Node*> nodes;
    std::vector<Line*> lines;

    Button* btn;
    Button* btn2;
    sf::Font font;

    short unsigned state = MENU;

    Node* PTR1 = nullptr;
    Node* PTR2 = nullptr;
    std::vector<Node*> end_path;

    sf::Text topText;
    sf::Text menuText;
    sf::Text endText;

    float TIME_ELAPSED;
    char label = 'A';
    unsigned int count = 0;
    bool found=true;
public:
    Engine();

    void main_loop();

    void init_fonts();

    void init_texts();

    void display();

    float calculateDistance(Node* vertex, Node* neighbour);

    std::vector<Node*> dijkstra();

    void change_vertex_color();

    void change_line_color();

    void make_start_and_finish(sf::Vector2f mousePositionF, float elapsed);

    void mapping(float elapsed, sf::Vector2f mousePositionF);

    void menu(sf::Vector2f mousePositionF);

    bool one_on_one(Node* one);

    ~Engine();
};

