#include "lib/datastructures.h"
#include "lib/filehandling.h"
#include "lib/textanalyzer.h"
#include "lib/buildlist.h"
#include "lib/menu.h"

using namespace std;

const string FILE_NAME = "database.txt";

int main(){

    File file(FILE_NAME);
    GeneralizedList db;
    if (file.check()){
        build_db(file, db);
    }

    menu(db);

    db.write(file);

    return 0;

}