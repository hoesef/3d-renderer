#include <fstream>
#include <string>

#include <iostream>

#include "../../include/objects/polymesh.h"

// Need x, y, z validation to check for malformed stuff
Vertex parseVertexData(std::string line) {
    // Storage variables
    float x, y, z = 0.0f;
    float w = 1.0f;
    // End point of each value
    size_t xend, yend, zend = 0;
    xend = line.find(' ');
    yend = line.find(' ', xend + 1);
    zend = line.find(' ', yend + 1);
    // Convert 
    x = std::stof(line.substr(0, xend));
    y = std::stof(line.substr(xend, yend-xend));
    z = std::stof(line.substr(yend, zend));
    // Check if w value given
    if (zend != std::string::npos) {
        // try to convert remainder of string to float
        try
        {   // Success
            w = stof(line.substr(zend));
        }
        catch(std::invalid_argument const& e)
        {   // Fail, do nothing
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "return\n\n";
    return Vertex(x, y, z, w);
}

// Need some validation
Vector parseNormalData(std::string line) {
    float x, y, z = 0.0f;
    // End point of each value
    size_t xend, yend, zend = 0;
    xend = line.find(' ');
    yend = line.find(' ', xend + 1);
    // Convert 
    x = std::stof(line.substr(0, xend));
    y = std::stof(line.substr(xend, yend-xend));
    z = std::stof(line.substr(yend));
    std::cout << "return\n\n";
    return Vector(x, y, z);
}

void parseFaceData(std::string line) {
    // 1. split at ' '
    // 2. count number of vertices listed
    // 3. if > 3, split into triangles
    // 4. parse v/vt/vn
}

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
        switch (line[0]) {
            // Comments
            case '#':
                break;
            // Vertex [X]
            case 'v':
                switch (line[1]) {
                    // Vertex cord
                    case ' ':
                        m_vertices.push_back(parseVertexData(line.substr(2)));
                        m_vertex_count++;
                        break;
                    // Vertex normal
                    case 'n':
                        m_normals.push_back(parseNormalData(line.substr(2)));
                        // MAKE NORMAL
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
                // std::cout << "face\n";
                break;
            default:
                break;
        }
    }
}

void Polymesh::print() {
    std::cout << "\n";
    for (unsigned int i = 0; i < m_vertex_count; i++) {
        std::cout << "(" << m_vertices[i].m_x << ", " << m_vertices[i].m_y << ", " << m_vertices[i].m_z << ", " << m_vertices[i].m_w << ")\n";
    }
}

Polymesh::~Polymesh() {
    // Object destructor
}