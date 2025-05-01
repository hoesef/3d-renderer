#include <fstream>
#include <string>

#include <iostream>

#include "../../include/objects/polymesh.h"

Polymesh::Polymesh(const char* filename, bool& success) {
    std::cout << filename << "\n";
    std::ifstream obj(filename);

    if (obj.fail()) {
        success = false;
        obj.close();
        return;
    }

    std::string line;

    while (std::getline(obj, line)) {
        // c = line[0];
        std::cout << line << "\n";
        switch (line[0]) {
            // Comments
            case '#':
                break;
            // Vertex [X]
            case 'v':
                switch (line[1]) {
                    // Vertex cord
                    case ' ':
                        std::cout << "Vertex cord\n";
                        break;
                    // Vertex normal
                    case 'n':
                        std::cout << "Vertex normal\n";
                        break;
                    // Vertex texture cord
                    case 't':
                        std::cout << "vertex texture cord\n";
                        break;
                    // Parameter space vertex (not supported)
                    case 'p':
                        std::cout << "VP is not supported in this renderer.\n ";
                        break;
                    default:
                        break;
                }
                break;
            // Face data
            case 'f':
                std::cout << "face\n";
                break;
            default:
                break;
        }
    }
}

Polymesh::~Polymesh() {
    // Object destructor
}