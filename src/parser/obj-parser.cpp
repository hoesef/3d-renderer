#include "../../include/parser/obj-parser.h"

// Constructor
OBJParser::OBJParser() {}

// .obj file parser
Polymesh* OBJParser::parse(const char* filename) {
    // Open file
    std::ifstream file(filename);

    // Check file opened successfully
    if (file.fail()) {
        std::cerr << "Could not open file: " << filename << "\n";
        return nullptr;
    }

    // Create mesh object
    Polymesh* mesh = new Polymesh();

    // Read file line by line
    std::string line;
    unsigned int line_num = 1;
    while (std::getline(file, line)) {
        
        // Get prefix (#, v, vn, vt, vp, f, etc)
        std::string prefix;
        std::stringstream iss(line);

        iss >> prefix;

        // Parse vertex data
        if (prefix == "v") {
            float x, y, z, w = 0.0f;
            if (!(iss >> x >> y >> z)) { // Check x,y,z data read correctly
                std::cerr << "Malformed line in object file: " << filename << "( " << line_num << ")\n";
                return nullptr;
            }
            // read w data (if any)
            if (!(iss >> w)) {
                w = 1.0f;
            }
            // Add vertex to vertex list
            mesh->m_vertices.push_back(Vertex(x,y,z,w));
            mesh->m_vertex_count++;
        } 
        // Process vertex normals
        else if (prefix == "vn") {
            float x, y, z = 0.0f;
            if (!(iss >> x >> y >> z)) {
                std::cerr << "Malformed line in object file: " << filename << "( " << line_num << ")\n";
                return nullptr;
            }
            mesh->m_normals.push_back(Vector(x,y,z));
            mesh->m_normal_count++;
        } 
        // Process texture cords
        else if (prefix == "vt") {
            float u, v, w = 0.0f;
            if (!(iss >> u)) {
                std::cerr << "Malformed line in object file: " << filename << "( " << line_num << ")\n";
                return nullptr;
            }
            if (!(iss >> v)) {
                v = 0.0f;
            }
            if (!(iss >> w)) {
                w = 0.0f;
            }
            mesh->m_text_cords.push_back(Vector(u,v,w));
            mesh->m_texture_count++;
        } 
        // vvv THIS IS NOT VERY NICE CODE, I WANT TO REFACTOR IT AT SOME POINT vvv
        // Process face data
        else if (prefix == "f") {
            // v/vt/vn
            std::string seg;
            std::vector<std::string> segs;
            std::vector<unsigned int> v;
            while (iss >> seg) {
                std::cout << "\n\n" << seg << "\n";
                std::stringstream s(seg);
                unsigned int x = 0;
                s >> x;
                std::cout << "x: " << x << "\n";
                v.push_back(x);
            }
            std::cout << "Len v: " << v.size();
            for (int i = 1; i < v.size()-1; i++) {
                Triangle t{v[0], v[i], v[i+1]};
                mesh->m_tris.push_back(t);
                mesh->m_tri_count++;
            }

            // Identify what type of face data we are given (v, v/vt, v//vn, v/vt/vn)
            
            // std::cout << seg << "\n";
            

            // if (seg.find("//") != std::string::npos) {
            //     std::cout << "v//vn\n";
            //     std::cout << seg << "\n\n";
            // }
            // else if (seg.find('/') == seg.rfind('/') && seg.find('/') != std::string::npos) {
            //     std::cout << "v/vt\n";
            //     std::cout << seg << "\n\n";
            // } else if (seg.find('/') == std::string::npos) {
            //     std::cout << "v\n";
            //     std::cout << seg << "\n\n";
            // } else {
            //     std::cout << "v/vt/vn\n";
            //     std::cout << seg << "\n\n";
            // }
        }

    }

    return mesh;

}

// Destructor
OBJParser::~OBJParser() {
    std::cout << "ObjParser destructor called\n";
}