#ifndef OBJECT_PARSER_H_
#define OBJECT_PARSER_H_

#include "..\..\include\objects\polymesh.h"

/*
 * Object parser abstract base class
 * 
 * Derrived classes allow for the parsing of 3d models stored as different file types
 */
class ObjectParser {

    public:
        // Constructor
        ObjectParser() = default;
        // File parser
        virtual Polymesh* parse(const char* filename) = 0;
        // Destructor
        virtual ~ObjectParser() = default;

};

#endif