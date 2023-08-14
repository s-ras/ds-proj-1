#include "nodes.h"

//* CLASS : NODE CLASS IMPLEMENTATION

Node::Node() {
    next == NULL;
}

void Node::set_next(Node* n){
    if (n == NULL){
        next = NULL;
    } else if (this->get_type() == n->get_type()){
        next = n;
    } else {
        std::cout << "Can not assign an object of this type as the next pointer for the current object." << std::endl;
    }
}

Node* Node::get_next(){ 
    return next; 
}

//* CLASS : DATA CLASS IMPLEMENTATION

Data::Data(){
    this->next = NULL;
}

std::string Data::get_type(){
    return "data";
}

void Data::set_value(std::string v) { 
    value = v; 
}

std::string Data::get_value(){
    return value;
}

//* CLASS : PROPERTY CLASS IMPLEMENTATION

Property::Property(){
    this->next = NULL;
    this->down = NULL;
}

std::string Property::get_type(){
    return "property";
}

void Property::set_key(std::string k){
    property_key = k; 
}

std::string Property::get_key(){ 
    return property_key; 
}

void Property::set_down(Node* n){
    if (n == NULL){
        down = n;
    } else if (n->get_type() == "property" || n->get_type() == "data"){
        down = n;
    } else {
        std::cout << "Can not assign an object of this type as the down pointer for the current object." << std::endl;
    }
}

Node* Property::get_down(){ 
    return down; 
}

//* CLASS : CONTACT CLASS IMPLEMENTATION

Contact::Contact(){
    this->next = NULL;
    this->down = NULL;
}

std::string Contact::get_type(){
    return "contact";
}

void Contact::set_name(std::string n) { 
    name = n; 
}

std::string Contact::get_name(){ 
    return name; 
}

void Contact::set_down(Node* n){
    if (n == NULL){
        down = n;
    } else if (n->get_type() == "property"){
        down = n;
    } else {
        std::cout << "Can not assign an object of this type as the down pointer for the current object." << std::endl;
    }
}

Node* Contact::get_down() { 
    return down; 
}

//* CLASS : LINKED LIST NODE IMPLEMENTATION

LinkedListNode::LinkedListNode(Node* d, Node*n){
    data = d;
    next = n;
}

std::string LinkedListNode::get_type(){
    return "linked list node";
}

Node* LinkedListNode::get_data(){
    return data;
}

Node* LinkedListNode::get_next(){
    return next;
}

//* CLASS : LINE STACK NODE IMPLEMENTATION

LineStackNode::LineStackNode(Line* d, Node*n){
    data = d;
    next = n;
}

std::string LineStackNode::get_type(){
    return "stack node";
}

Line* LineStackNode::get_data(){
    return data;
}

Node* LineStackNode::get_next(){
    return next;
}

//* CLASS : PROPERTY WRAPPER IMPLEMENTATION

PropertyWrapper::PropertyWrapper(Property* p = NULL, int ind = 0){
    property = p;
    indent = ind;
}

//* CLASS : PROPERTY STACK NODE IMPLEMENTATION

PropertyStackNode::PropertyStackNode(PropertyWrapper p, Node*n){
    data = p;
    next = n;
}

std::string PropertyStackNode::get_type(){
    return "property stack node";
}


PropertyWrapper PropertyStackNode::get_data(){
    return data;
}

Node* PropertyStackNode::get_next(){
    return next;
}

//* CLASS : GENERAL STACK NODE IMPLEMENTATION

GeneralStackNode::GeneralStackNode(Node* d, Node*n){
    data = d;
    next = n;
}

std::string GeneralStackNode::get_type(){
    return "general stack node";
}


Node* GeneralStackNode::get_data(){
    return data;
}

Node* GeneralStackNode::get_next(){
    return next;
}

//* CLASS : TRAVERSE WRAPPER IMPLEMENTATION

TraverseWrapper::TraverseWrapper(Node* p, Node* h, Node* c){
    parent = p;
    level_head = h;
    current = c;
}

void TraverseWrapper::update(Node* p, Node* h, Node* c){
    parent = p;
    level_head = h;
    current = c;
}