#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(1280, 720), "Dijkstra", sf::Style::Default), TIME_ELAPSED(0.0f) {
    init_fonts();
    init_texts();
    this->btn = new Button(sf::Vector2f(640.0f, 360.0f), sf::Vector2f(300.0f, 150.0f), &this->font, "Start");
}

void Engine::main_loop() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        if (state == MENU) {
            menu(mousePositionF);
        }
        else if (state == MAPPING) {
            float elapsed = clock.restart().asSeconds();
            mapping(elapsed, mousePositionF);
        }
        else if (state == ALGORITHM) {
            float elapsed = clock.restart().asSeconds();
            make_start_and_finish(mousePositionF, elapsed);
        }
        display();
    }
}

void Engine::init_fonts() {
    font.loadFromFile("res/arial.ttf");
}

void Engine::init_texts() {
    topText.setString("press R to finish then choose start and end by left click");
    topText.setFont(this->font);
    topText.setFillColor(sf::Color::White);
    topText.setCharacterSize(24);
    topText.setPosition(20.0f, 15.0f);

    menuText.setString("Left click to create Node and right click to connect nodes");
    menuText.setFont(this->font);
    menuText.setFillColor(sf::Color::White);
    menuText.setCharacterSize(24);
    menuText.setPosition(20.0f, 15.0f);

    endText.setString("Path not found!");
    endText.setFont(this->font);
    endText.setFillColor(sf::Color::White);
    endText.setCharacterSize(24);
    endText.setPosition(20.0f, 15.0f);
}

void Engine::display() {
    window.clear();
    if (state == MAPPING) {
        for (const auto& line : lines) {
            window.draw(*line);
        }
        for (const auto& node : nodes) {
            window.draw(*node);
        }
        window.draw(topText);
    }
    else if (state == ALGORITHM) {
        for (const auto& line : lines) {
            window.draw(*line);
        }
        for (const auto& node : nodes) {
            window.draw(*node);
        }
    }
    else if (state == MENU) {
        window.draw(menuText);
        btn->render(&window);
    }
    else if (state == END) {
        for (const auto& line : lines) {
            window.draw(*line);
        }
        for (const auto& node : nodes) {
            window.draw(*node);
        }
        if (!found) {
            window.draw(endText);
        }

    }
    window.display();
}

float Engine::calculateDistance(Node* vertex, Node* neighbour) {
    float dx = vertex->getPosition().x - neighbour->getPosition().x;
    float dy = vertex->getPosition().y - neighbour->getPosition().y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<Node*> Engine::dijkstra() {
    std::unordered_map<Node*, float> distances;
    std::unordered_map<Node*, Node*> previous;
    std::priority_queue<std::pair<float, Node*>, std::vector<std::pair<float, Node*>>, std::greater<>>pq;

    distances[PTR1] = 0;
    pq.emplace(0.0f, PTR1);

    while (!pq.empty()) {
        auto currentPair = pq.top();
        pq.pop();

        float currentDistance = currentPair.first;
        Node* current = currentPair.second;

        if (current == PTR2) {
            break;
        }
        for (auto& neighbour : current->neighbours) {
            float newDist = currentDistance + calculateDistance(current, neighbour);
            if (distances.find(neighbour) == distances.end() || newDist < distances[neighbour]) {
                distances[neighbour] = newDist;
                previous[neighbour] = current;
                pq.emplace(newDist, neighbour);
            }
        }
    }
    std::vector<Node*> path;
    for (Node* at = PTR2; at != nullptr; at = previous[at]) {
        path.push_back(at);
    }
    if (!path.empty() && path.back() == PTR1) {
        return path;
    }
    return {};
}

void Engine::change_vertex_color() {
    for (const auto& node : end_path) {
        node->setFillColor(sf::Color::Green);
    }
}

void Engine::change_line_color() {
    lines.clear();
    for (size_t i = 0; i < end_path.size()-1; i++) {
        lines.emplace_back(new Line(end_path[i]->getPosition(), end_path[i + 1]->getPosition(), sf::Color::Green));
    }
}

void Engine::make_start_and_finish(sf::Vector2f mousePositionF, float elapsed) {
    TIME_ELAPSED = TIME_ELAPSED + elapsed;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TIME_ELAPSED > 0.2f) {
        for (const auto& node : nodes) {
            if (node->contains(mousePositionF)) {
                node->setFillColor(sf::Color::White);
                count++;
                if (count == 1) {
                    PTR1 = node; //START NODE
                }
                else if (count == 2 && PTR1 != nullptr) {
                    PTR2 = node; // FINISH NODE
                    end_path = dijkstra();
                    if (!end_path.empty()) {
                        change_line_color();
                        change_vertex_color();
                    }
                    else if (end_path.empty()) {
                        found = false;
                    }
                    count = 0;
                    state = END;
                }
            }
        }
        TIME_ELAPSED = 0.0f;
    }
}

void Engine::mapping(float elapsed, sf::Vector2f mousePositionF) {
    TIME_ELAPSED = TIME_ELAPSED + elapsed;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TIME_ELAPSED > 0.2f) {
        Node* nd = new Node(mousePositionF, label, 12.0f);
        if (!one_on_one(nd)) {
            nodes.emplace_back(nd);
            label++;
        }
        TIME_ELAPSED = 0.0f;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && TIME_ELAPSED > 0.2f) {
        for (auto& node : nodes) {
            if (node->contains(mousePositionF)) {
                count++;
                if (count == 1 && node!=PTR1) {
                    PTR1 = node;
                    node->clicked=true;
                }
                else if (count == 2 && PTR1 != nullptr) {
                    node->clicked = true;
                    PTR2 = node;
                    lines.emplace_back(new Line(PTR1->getPosition(), PTR2->getPosition(), sf::Color::Red));
                    PTR1->neighbours.emplace_back(PTR2);
                    PTR2->neighbours.emplace_back(PTR1);
                    PTR1->clicked = false;
                    PTR2->clicked = false;
                    count = 0;
                    PTR1 = nullptr;
                    PTR2 = nullptr;
                }
            }
        }
        TIME_ELAPSED = 0.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        state = ALGORITHM;
        count = 0;
        for (const auto& node : nodes) {
            node->setFillColor(sf::Color::Red);
        }
    }
}

void Engine::menu(sf::Vector2f mousePositionF) {
    btn->update(mousePositionF);
    if (btn->isPressed()) {
        state = MAPPING;
        TIME_ELAPSED = 0.0f;
        sf::sleep(sf::seconds(0.2f));
    }
}

bool Engine::one_on_one(Node* one) {
    for (const auto& node : nodes) {
        if (node->getGlobalBounds().contains(one->getPosition())) {
            return true;
        }
    }
    return false;
}

Engine::~Engine() {
    delete btn;
    for (const auto& node : nodes) {
        delete node;
    }
    for (const auto& line : lines) {
        delete line;
    }
    for (const auto& node : end_path) {
        delete node;
    }
    delete PTR1;
    delete PTR2;
}
