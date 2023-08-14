#include "textanalyzer.h"

void Line::count_indent(std::string& inp){
    indent = (int) std::count(inp.begin(), inp.end(), '\t');
    inp.erase(remove(inp.begin(), inp.end(), '\t'), inp.end());
}

void Line::analyze(std::string inp){
    lowerCase(inp);
    type = inp.substr(inp.find("- ") + 2, inp.find(": ") - 2);
    content = inp.substr(inp.find(": ") + 2);
}

Line::Line(std::string inp){
    count_indent(inp);
    analyze(inp);
}

int Line::get_indent(){
    return indent;
}

std::string Line::get_type(){
    return type;
}

std::string Line::get_content(){
    return content;
}

void lowerCase(std::string &str){
    for (int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
}
