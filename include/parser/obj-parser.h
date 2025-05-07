#ifndef OBJ_PARSER_H_
#define OBJ_PARSER_H_

#include "object-parser.h"

class OBJParser: public ObjectParser {

    public:
        // Constructor
        OBJParser();
        // .obj file parser
        Polymesh* parse(const char* filename) override;
        // Destructor
        ~OBJParser();

};

#endif