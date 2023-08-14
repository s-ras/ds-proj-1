#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "nodes.h"
#include "textanalyzer.h"
#include "filehandling.h"

//* CLASS PROTOTYPES

class GeneralizedList{
    private:
        Node* head;
    public:
        GeneralizedList();
        Node* get_head();
        bool is_empty();
        Node* insert_contact(std::string, Node*);
        void print();
        void write(File&);
        void clear();
        Node* find_contact(std::string);
        void remove_contact();
        Node* find_value(std::string);
        void remove_value();
        TraverseWrapper find_property();
        void remove_property();
        void add_contact();
        void add_value();
        void print_contact();
        void trace_value();
};

class LineStack{
    private:
        LineStackNode* top;
        int size;
    public:
        LineStack();
        ~LineStack();
        bool is_empty();
        Line* get_top();
        int get_size();
        Line* pop();
        void push(Line*);
        void clear();
};

class PropertyStack{
    private:
        PropertyStackNode* top;
        int size;
    public:
        PropertyStack();
        ~PropertyStack();
        bool is_empty();
        PropertyWrapper get_top();
        int get_size();
        PropertyWrapper pop();
        void push(PropertyWrapper);
        void clear();
};

class GeneralStack{
    private:
        GeneralStackNode* top;
        int size;
    public:
        GeneralStack();
        ~GeneralStack();
        bool is_empty();
        Node* get_top();
        int get_size();
        Node* pop();
        void push(Node*);
        void clear();
        bool in_stack(Node*);  
};

//! FUNCTION PROTOTYPES

Node* new_property(std::string, Node*, Node*);
Node* new_data(std::string, Node*);
std::string makeIndent(int);
void output(Node*, std::ostream&);
Node* clearList(Node*);
Node* search_contact(Node*, std::string);
Node* delete_contact(Node*, Node*);
Node* search_value(Node*, std::string);
Node* trace_path(Node*, GeneralStack*, Node*);
Node* find_parent(Node*, Node*);
void print_path(GeneralStack*);
Node* delete_value(Node*, Node*);
Node* purge_value(Node*);
Node* delete_property(Node*, Node*);
Node* purge_property(Node*);
Node* search_property(Node*, std::string);
void list_contacts(Node*);
void list_prop(Node*);
void select_property(Node*, TraverseWrapper&);
void build_property_hierarchy(TraverseWrapper, GeneralStack*);
Node* inject_property(Node*, Node*);
void print_con(Node*);

#endif