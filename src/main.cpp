#include "Engine.h"

int main() {
    Engine dijkstra;
    std::cout << "Katalog roboczy: "
        << std::filesystem::current_path()
        << std::endl;
    dijkstra.main_loop();
    return 0;
}