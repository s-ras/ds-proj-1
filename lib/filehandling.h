#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <iostream>
#include <fstream>

class File{
    private:
        std::fstream f;
        std::string fn;
        bool has_filename = false;
    public:
        File(std::string);
        void setFileName(std::string);
        bool check();
        bool changeMode(std::string);
        std::fstream& expose();
};

#endif