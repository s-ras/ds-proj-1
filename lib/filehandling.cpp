#include "filehandling.h"

File::File(std::string fn){
    setFileName(fn);
    check();
}

void File::setFileName(std::string filename){
    fn = filename;
    has_filename = true;
}

bool File::check(){
    if (has_filename){
        if (! changeMode("read")){
            std::cout << "Database file not found, creating a new database ..." << std::endl;
            changeMode("write");
            changeMode("read");
            return false;
        }
        return true;
    }
    if (f.fail()){
        std::cout << "Couldn't access database file, application terminated!";
        exit(1);
    }
    return false;
}

bool File::changeMode(std::string mode){
    bool sucess = true;
    if (has_filename){
        try {
            f.close();
            if (mode == "read"){
                f.open(fn, std::ios::in);
            } else if (mode == "write"){
                f.open(fn, std::ios::out);
            } else if (mode == "append"){
                f.open(fn, std::ios::app);
            } else if (mode == "close"){
                f.close();
            } else {
                throw -1;
            }
            if (f.fail()){
                throw -2;
            }
        } catch(int err){
            if (err == -1){
                std::cout << "Invalid file mode!" << std::endl;
            } else if (err == -2){
                std::cout << "Couldn't change file mode!" << std::endl;
            }
            sucess = false;
            std::cout << err << std::endl;
        }
    }
    return sucess;
}

std::fstream& File::expose(){
    return f;
}