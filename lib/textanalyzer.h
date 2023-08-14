#ifndef TXT_ANALYZER_H
#define TXT_ANALYZER_H

#include <iostream>
#include <string.h>
#include <algorithm>

class Line{
    private:
        int indent;
        std::string type;
        std::string content;
        void count_indent(std::string&);
        void analyze(std::string);
    public:
        Line(std::string);
        int get_indent();
        std::string get_type();
        std::string get_content();
};

void lowerCase(std::string&);

#endif