#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "textanalyzer.h"

class Node{
    protected:
        Node* next;
    public:
        Node();
        virtual std::string get_type() = 0;
        void set_next(Node*);
        Node* get_next();
};

class Data: public Node{
    private:
        std::string value;
    public:
        Data ();
        virtual std::string get_type();
        void set_value(std::string);
        std::string get_value();
};

class Property: public Node{
    private:
        std::string property_key;
        Node* down;
    public:
        Property(); 
        virtual std::string get_type();
        void set_key(std::string);
        std::string get_key();
        Node* get_down();
        void set_down(Node*);
};

class Contact: public Node{
    private:
        std::string name;
        Node* down;
    public:
        Contact();
        virtual std::string get_type();
        void set_name(std::string);
        std::string get_name();
        void set_down(Node*);
        Node* get_down();
};

class LinkedListNode: public Node {
    private:
        Node* data;
    public:
        LinkedListNode (Node*, Node*);
        virtual std::string get_type();
        Node* get_next();
        Node* get_data();
};

class LineStackNode: public Node {
    private:
        Line* data;
        Node* get_next();
    public:
        LineStackNode(Line*, Node*);
        virtual std::string get_type();
        Line* get_data();
        friend class LineStack;
};

class PropertyWrapper{
    public:
        PropertyWrapper(Property*, int);
        Property* property;
        int indent;
};

class PropertyStackNode: public Node {
    private:
        PropertyWrapper data;
        Node* get_next();
    public:
        PropertyStackNode(PropertyWrapper, Node*);
        virtual std::string get_type();
        PropertyWrapper get_data();
        friend class PropertyStack;
};

class GeneralStackNode: public Node {
    private:
        Node* data;
        Node* get_next();
    public:
        GeneralStackNode(Node*, Node*);
        virtual std::string get_type();
        Node* get_data();
        friend class GeneralStack;
};

class TraverseWrapper{ 
    public:
        TraverseWrapper(Node*, Node*, Node*);
        void update(Node*, Node*, Node*);
        Node* parent;
        Node* level_head;
        Node* current;
};

#endif