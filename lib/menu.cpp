#include "menu.h"

int print_options(){
    int choice;
    do {
        std::cout << "1- Show contact information\n2- Show all data\n3- Add new contact\n4- Add new value\n5- Remove contact\n6- Remove property\n7- Remove value\n8- Trace value\n9- Clear database\n10- exit\nOptions?\t";
        std::cin >> choice;
        std::cin.ignore();
        if (choice > 10 || choice < 1){
            std::cout << "Invalid option! Try again." << std::endl;
        }
    } while (choice > 10 || choice < 1);
    return choice;
}

void menu(GeneralizedList& db){
    while (true){
        int choice = print_options();
        std::cout << "--------------------------------------------------------------------" << std::endl;
        switch (choice){
            case 1:
                db.print_contact();
                break;
            case 2:
                db.print();
                break;
            case 3:
                db.add_contact();
                break;
            case 4:
                db.add_value();
                break;
            case 5:
                db.remove_contact();
                break;
            case 6:
                db.remove_property();
                break;
            case 7:
                db.remove_value();
                break;
            case 8:
                db.trace_value();
                break;
            case 9:
                db.clear();
                break;
            case 10:
                return;
                break;
            default:
                break;
        }
        std::cout << "--------------------------------------------------------------------" << std::endl;
    }
}