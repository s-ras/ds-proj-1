#include "datastructures.h"

//* CLASS : GENRERALIZED LIST CLASS IMPLEMENTATION

GeneralizedList::GeneralizedList(){
    this->head = NULL;
}

Node* GeneralizedList::get_head(){ 
    return this->head;
}

bool GeneralizedList::is_empty(){
    return this->head == NULL;
}

Node* GeneralizedList::insert_contact(std::string name, Node* down){
    Contact* new_contact = new Contact;
    new_contact->set_name(name);
    new_contact->set_down(down);
    new_contact->set_next(head);
    head = new_contact;
    return new_contact;
}

void GeneralizedList::print(){ 
    output(this->head, std::cout); 
}

void GeneralizedList::write(File& file){ 
    file.changeMode("write");
    output(head, file.expose()); 
}

void GeneralizedList::clear(){
    head = clearList(this->head);
}

Node* GeneralizedList::find_contact(std::string name){
    return search_contact(head, name);
}

void GeneralizedList::remove_contact(){
    Node* found = NULL;
    while (true){
        std::cout << "Name?" << std::endl;
        std::string inp;
        std::getline(std::cin, inp);
        lowerCase(inp);
        found = find_contact(inp);
        if (! found){
            std::cout << "Contact doesn't exist! Try again." << std::endl;
        } else {
            break;
        }
    }
    head = delete_contact(head, found);
}

Node* GeneralizedList::find_value(std::string val){
    return search_value(head, val);
}

void GeneralizedList::remove_value(){
    Node* found = NULL;
    while (true){
        std::string inp;
        std::cout << "value to trace?" << std::endl;
        std::getline(std::cin, inp);
        lowerCase(inp);
        found = find_value(inp);
        if (! found){
            std::cout << "Value doesn't exist! Try again." << std::endl;
            continue;
        }
        break;
    }
    Node* parent = find_parent(head, found);
    Property* par = (Property*) parent;
    par->set_down(delete_value(par->get_down(), found));
    while (true){
        if (par->get_down() == NULL){
            Node* temp = par;
            Node* prnd = find_parent(head, par);
            if (prnd->get_type() == "contact"){
                Contact* par_con = (Contact*) prnd;
                par_con->set_down(delete_property(par_con->get_down(), temp));
                break;
            } else if (prnd->get_type() == "property"){
                par = (Property*) prnd;
                par->set_down(delete_property(par->get_down(), temp));
            }
        } else {
            break;
        }
    }
}

TraverseWrapper GeneralizedList::find_property(){
    TraverseWrapper tw(NULL, NULL, NULL);
    select_property(this->head, tw);
    return tw;
}

void GeneralizedList::remove_property(){
    TraverseWrapper tw = find_property();
    if (tw.parent == NULL){
        std::cout << "No properties to delete!" << std::endl;
        return;
    }
    if (tw.parent->get_type() == "contact"){
        Contact* con_par = (Contact*) tw.parent;
        con_par->set_down(delete_property(tw.level_head, tw.current));
    } else if (tw.parent->get_type() == "property"){
        Property* prop_par = (Property*) tw.parent;
        prop_par->set_down(delete_property(tw.level_head, tw.current));
        while (true){
            if (prop_par->get_down() == NULL){
                Node* temp = prop_par;
                Node* prnd = find_parent(head, prop_par);
                if (prnd->get_type() == "contact"){
                    Contact* par_con = (Contact*) prnd;
                    par_con->set_down(delete_property(par_con->get_down(), temp));
                    break;
                } else if (prnd->get_type() == "property"){
                    prop_par = (Property*) prnd;
                    prop_par->set_down(delete_property(prop_par->get_down(), temp));
                }
            } else {
                break;
            }
        }
    }
}

void GeneralizedList::add_contact(){
    std::string inp;
    while (true){
        std::cout << "Name?" << std::endl;
        std::getline(std::cin, inp);
        lowerCase(inp);
        Node* found = find_contact(inp);
        if (found){
            std::cout << "Contact exists already! Try another name" << std::endl;
        } else {
            break;
        }
    }
    insert_contact(inp, NULL);
}

void GeneralizedList::add_value(){
    std::cout << "Select property to add new value to. If you chose a Property that contains subproperties you will be asked to create a new subproperty for your new value." << std::endl;
    TraverseWrapper tw = find_property();
    if (tw.current->get_type() == "contact"){
        GeneralStack* gs = new GeneralStack;
        build_property_hierarchy(tw, gs);
        std::string inp;
        while (true){
            std::cout << "value to add?" << std::endl;
            std::getline(std::cin, inp);
            lowerCase(inp);
            Node* found = find_value(inp);
            if (found){
                std::cout << "Value already exists! Try another value." << std::endl;
                continue;
            }
            break;
        }
        Property* tp = (Property*) gs->get_top();
        tp->set_down(new_data(inp, tp->get_down()));
        Node* last = gs->pop();
        while (! gs->is_empty()){
            Property* sttp = (Property*) gs->get_top();
            sttp->set_down(last);
            last = gs->pop();
        }
        Contact* con = (Contact*) tw.current;
        con->set_down(inject_property(con->get_down(), last));
    } else if (tw.current->get_type() == "property"){
        Property* prop = (Property*) tw.current;
        if (prop->get_down()->get_type() == "data"){
            std::string inp;
            while (true){
                std::cout << "value to add?" << std::endl;
                std::getline(std::cin, inp);
                lowerCase(inp);
                Node* found = find_value(inp);
                if (found){
                    std::cout << "Value already exists! Try another value." << std::endl;
                    continue;
                }
                break;
            }
            prop->set_down(new_data(inp, prop->get_down()));
        } else if (prop->get_down()->get_type() == "property"){
            GeneralStack* gs = new GeneralStack;
            build_property_hierarchy(tw, gs);
            std::string inp;
            while (true){
                std::cout << "value to add?" << std::endl;
                std::getline(std::cin, inp);
                lowerCase(inp);
                Node* found = find_value(inp);
                if (found){
                    std::cout << "Value already exists! Try another value." << std::endl;
                    continue;
                }
                break;
            }
            Property* tp = (Property*) gs->get_top();
            tp->set_down(new_data(inp, tp->get_down()));
            Node* last = gs->pop();
            while (! gs->is_empty()){
                Property* sttp = (Property*) gs->get_top();
                sttp->set_down(last);
                last = gs->pop();
            }
            prop->set_down(inject_property(prop->get_down(), last));
        }
    }
}

void GeneralizedList::print_contact(){
    Node* found = NULL;
    while (true){
        std::cout << "Name?" << std::endl;
        std::string inp;
        std::getline(std::cin, inp);
        lowerCase(inp);
        found = find_contact(inp);
        if (! found){
            std::cout << "Contact doesn't exist! Try again." << std::endl;
        } else {
            break;
        }
    }
    print_con(found);
}

void GeneralizedList::trace_value(){
    Node* found = NULL;
    while (true){
        std::string inp;
        std::cout << "value to trace?" << std::endl;
        std::getline(std::cin, inp);
        lowerCase(inp);
        found = find_value(inp);
        if (! found){
            std::cout << "Value doesn't exist! Try again." << std::endl;
            continue;
        }
        break;
    }
    GeneralStack* gs = new GeneralStack;
    trace_path(head, gs, found);
    print_path(gs);
}

//* CLASS : LINE STACK CLASS IMPLEMENTATION

LineStack::LineStack(){
    top = NULL;
    size = 0;
}

LineStack::~LineStack(){
    this->clear();
}

bool LineStack::is_empty(){
    return top == NULL;
}

Line* LineStack::get_top(){
    if (size > 0){
        return top->get_data();
    }
    return NULL;
}

int LineStack::get_size(){
    return size;
}

Line* LineStack::pop(){
    if (size > 0){
        LineStackNode* temp = top;
        top = (LineStackNode*) top->get_next();
        Line* tmpdt = temp->get_data();
        delete temp;
        size--;
        return tmpdt;
    }
    return NULL;
}

void LineStack::push(Line* dt){
    LineStackNode* new_node = new LineStackNode(dt, top);
    top = new_node;
    size++;
}

void LineStack::clear(){
    if (size > 0){
        while (top != NULL){
            LineStackNode* temp = top;
            top = (LineStackNode*) top->get_next();
            delete temp;
        }
        size = 0;
    }
}

//* CLASS : PROPERTY STACK CLASS IMPLEMENTATION

PropertyStack::PropertyStack(){
    top = NULL;
    size = 0;
}

PropertyStack::~PropertyStack(){
    this->clear();
}

bool PropertyStack::is_empty(){
    return top == NULL;
}

PropertyWrapper PropertyStack::get_top(){
    if (size > 0){
        return top->get_data();
    }
    return PropertyWrapper(NULL, 0);
}

int PropertyStack::get_size(){
    return size;
}

PropertyWrapper PropertyStack::pop(){
    if (size > 0){
        PropertyStackNode* temp = top;
        PropertyWrapper tmddt = temp->get_data();
        top = (PropertyStackNode*) top->get_next();
        delete temp;
        size--;
        return tmddt;
    }
    return PropertyWrapper(NULL, 0);
}

void PropertyStack::push(PropertyWrapper d){
    PropertyStackNode* new_node = new PropertyStackNode(d, top);
    top = new_node;
    size++;
}

void PropertyStack::clear(){
    if (size > 0){
        while (top != NULL){
            PropertyStackNode* temp = top;
            top = (PropertyStackNode*) top->get_next();
            delete temp;
        }
        size = 0;
    }
}

//* CLASS : GENERAL STACK CLASS IMPLEMENTATION

GeneralStack::GeneralStack(){
    top = NULL;
    size = 0;
}

GeneralStack::~GeneralStack(){
    this->clear();
}

bool GeneralStack::is_empty(){
    return top == NULL;
}

Node* GeneralStack::get_top(){
    if (size > 0){
        return top->get_data();
    }
    return NULL;
}

int GeneralStack::get_size(){
    return size;
}

Node* GeneralStack::pop(){
    if (size > 0){
        GeneralStackNode* temp = top;
        Node* tmddt = temp->get_data();
        top = (GeneralStackNode*) top->get_next();
        delete temp;
        size--;
        return tmddt;
    }
    return NULL;
}

void GeneralStack::push(Node* d){
    GeneralStackNode* new_node = new GeneralStackNode(d, top);
    top = new_node;
    size++;
}

void GeneralStack::clear(){
    if (size > 0){
        while (top != NULL){
            GeneralStackNode* temp = top;
            top = (GeneralStackNode*) top->get_next();
            delete temp;
        }
        size = 0;
    }
}

bool GeneralStack::in_stack(Node* d){
    bool found = false;
    GeneralStackNode* temp = top;
    while (temp != NULL){
        if (temp->get_data() == d){
            found = true;
            break;
        }
        temp = (GeneralStackNode*) temp->get_next();
    }
    return found;
}

//! Functions :

Node* new_property(std::string key, Node* down, Node* next){
    Property* new_property = new Property;
    new_property->set_key(key);
    new_property->set_down(down);
    new_property->set_next(next);
    return new_property;
}

Node* new_data(std::string value, Node* next){
    Data* new_data = new Data;
    new_data->set_value(value);
    new_data->set_next(next);
    return new_data;
}

std::string makeIndent(int ind){
    std::string res = "";
    for (int i = 0; i < ind; i++){
        res += "\t";
    }
    return res;
}

void output(Node* head, std::ostream& out){
    Node* current = head;
    static int indent = 0;
    while (current != NULL){
        if (current->get_type() == "contact"){
            Contact* cur_cont = (Contact*) current;
            out << "- contact: " << cur_cont->get_name() << std::endl;
            indent = 1;
            output(cur_cont->get_down(), out);
        } else if (current->get_type() == "property"){
            Property* cur_prop = (Property*) current;
            out << makeIndent(indent) << "- property: " << cur_prop->get_key() << std::endl;
            indent++;
            output(cur_prop->get_down(), out);
            indent--;
        } else if (current->get_type() == "data"){
            Data* cur_data = (Data*) current;
            out << makeIndent(indent) << "- value: " << cur_data->get_value() << std::endl;
        }
        current = current->get_next();
    }
}

Node* clearList(Node* head){
    while (head != NULL){
        Node* temp;
        if (head->get_type() == "contact"){
            Contact* cur_cont = (Contact*) head;
            clearList(cur_cont->get_down());
        } else if (head->get_type() == "property"){
            Property* cur_prop = (Property*) head;
            clearList(cur_prop->get_down());
        }
        temp = head;
        head = head->get_next();
        delete temp;
    }
    return head;
}

Node* search_contact(Node* head, std::string key){
    Contact* current = (Contact*) head;
    while (current != NULL){
        if (current->get_name() == key){
            return current;
        }
        current = (Contact*) current->get_next();
    }
    return NULL;
}

Node* delete_contact(Node* head, Node* node){
    if (head == NULL){
        return NULL;
    } else if (head == node){
        head = head->get_next();
        Contact* temp = (Contact*) node;
        temp->set_down(clearList(temp->get_down()));
        delete temp;
    } else {
        Contact* p = NULL, *q = (Contact*) head;
        while (q != NULL){
            if (q == node){
                Contact* temp = (Contact*) q;
                p->set_next(q->get_next());
                temp->set_down(clearList(temp->get_down()));
                delete temp;
                break;
            }
            p = q;
            q = (Contact*) q->get_next();
        }
    }
    return head;
}

Node* search_value(Node* head, std::string key){
    Node* current = head;
    Node* res = NULL;
    while (current != NULL){
        if (current->get_type() == "contact"){
            Contact* cur_cont = (Contact*) current;
            res = search_value(cur_cont->get_down(), key);
            if (res != NULL){
                break;
            }
        } else if (current->get_type() == "property"){
            Property* cur_prop = (Property*) current;
            res = search_value(cur_prop->get_down(), key);
            if (res != NULL){
                break;
            }
        } else if (current->get_type() == "data"){
            Data* cur_data = (Data*) current;
            if (cur_data->get_value() == key){
                res = current;
                break;
            } else {
                res = NULL;
            }
        }
        current = current->get_next();
    }
    return res;
}

Node* trace_path(Node* head, GeneralStack* gs, Node* nd){
    if (nd == NULL){
        return NULL;
    }
    Node* res = NULL;
    Node* current = head;
    while (current != NULL){
        if (current->get_type() == "contact"){
            gs->push(current);
            if (current == nd){
                res = current;
                break;
            }
            Contact* cur_cont = (Contact*) current;
            res = trace_path(cur_cont->get_down(), gs, nd);
            if (res == NULL){
                while (gs->in_stack(current)){
                    gs->pop();
                }
            } else {
                break;
            }
        } else if (current->get_type() == "property"){
            gs->push(current);
            if (current == nd){
                res = current;
                break;
            }
            Property* cur_prop = (Property*) current;
            res = trace_path(cur_prop->get_down(), gs, nd);
            if (res == NULL){
                while (gs->in_stack(current)){
                    gs->pop();
                }
            } else {
                break;
            }   
        } else if (current->get_type() == "data"){
            gs->push(current);
            if (current == nd){
                res = current;
                break;
            }
            if (res == NULL){
                gs->pop();
            } else {
                break;
            }   
        }
        current = current->get_next();
    }
    return res;
}

Node* find_parent(Node* head, Node* nd){
    if (nd == NULL){
        return NULL;
    } else if (nd->get_type() == "contact"){
        return NULL;
    }
    GeneralStack* gs = new GeneralStack;
    trace_path(head, gs, nd);
    gs->pop();
    return gs->pop();
}

void print_path(GeneralStack* gs){
    GeneralStack* rv = new GeneralStack;
    while (! gs->is_empty()){
        rv->push(gs->pop());
    }
    int indent = 0;
    while (! rv->is_empty()){
        Node* temp = rv->pop();
        if (temp->get_type() == "contact"){
            Contact* temp_con = (Contact*) temp;
            std::cout << "- contact: " << temp_con->get_name() << std::endl;
        } else if (temp->get_type() == "property"){
            Property* temp_prop = (Property*) temp;
            std::cout << makeIndent(indent) << "- property: " << temp_prop->get_key() << std::endl;
        } else if (temp->get_type() == "data"){
            Data* temp_dt = (Data*) temp;
            std::cout << makeIndent(indent) << "- value: " << temp_dt->get_value() << std::endl;
        }
        indent++;
    }
}

Node* delete_value(Node* head, Node* nd){
    if (head == NULL){
        return NULL;
    } else if (head == nd){
        Node* temp = head;
        head = temp->get_next();
        delete temp;
    } else {
        Node* p = NULL, *q = head;
        while (q != NULL){
            if (q == nd){
                Node* temp = q;
                p->set_next(q->get_next());
                delete temp;
                break;
            }
            p = q;
            q = q->get_next();
        }
    }
    return head;
}

Node* purge_value(Node* head){
    while (head != NULL){
        Node* temp = head;
        head = head->get_next();
        delete temp;
    }
    return head;
}

Node* delete_property(Node* head, Node* nd){
    if (head == NULL){
        return NULL;
    } else if (head == nd){
        Property* temp = (Property*) head;
        head = temp->get_next();
        if (temp->get_down()->get_type() == "data"){
            temp->set_down(purge_value(temp->get_down()));
        } else if (temp->get_down()->get_type() == "property"){
            temp->set_down(purge_property(temp->get_down()));
        }
        delete temp;
    } else {
        Node* p = NULL, *q = head;
        while (q != NULL){
            if (q == nd){
                Property* temp = (Property*) q;
                p->set_next(q->get_next());
                if (temp->get_down() != NULL){
                    if (temp->get_down()->get_type() == "data"){
                        temp->set_down(purge_value(temp->get_down()));
                    } else if (temp->get_down()->get_type() == "property"){
                        temp->set_down(purge_property(temp->get_down()));
                    }   
                }             
                delete temp;
                break;
            }
            p = q;
            q = q->get_next();
        }
    }
    return head;
}

Node* purge_property(Node* head){
    while (head != NULL){
        Property* temp = (Property*) head;
        if (temp->get_down()->get_type() == "value"){
            temp->set_down(purge_value(temp->get_down()));
        } else if (temp->get_down()->get_type() == "property"){
            temp->set_down(purge_property(temp->get_down()));
        }
        head = head->get_next();
        delete temp;
    }
    return head;
}

Node* search_property(Node* head, std::string key){
    if (head == NULL){
        return NULL;
    }
    Node* current = head;
    if (head->get_type() == "value"){
        return NULL;
    }
    while (current != NULL){
        Property* cur_prop = (Property*) current;
        if (cur_prop->get_key() == key){
            return current;
        }
        current = current->get_next();
    }
    return NULL;
}

void list_contacts(Node* head){
    Contact* current = (Contact*) head;
    while (current != NULL){
        std::cout << "- contact: " << current->get_name() << std::endl;
        current = (Contact*) current->get_next();
    }
}

void list_prop(Node* head){
    Property* current = (Property*) head;
    while (current != NULL){
        std::cout << "- property: " << current->get_key() << std::endl;
        current = (Property*) current->get_next();
    }
}

void list_data(Node* head){
    Data* current = (Data*) head;
    while (current != NULL){
        std::cout << "- value: " << current->get_value() << std::endl;
        current = (Data*) current->get_next();
    }
}

void select_property(Node* head, TraverseWrapper& tw){
    list_contacts(head);
    Node* con_found = NULL;
    while (con_found == NULL){
        std::cout << "Select contact:" << std::endl;;
        std::string inp;
        std::getline(std::cin, inp);
        lowerCase(inp);
        con_found = search_contact(head, inp);
        if (con_found == NULL){
            std::cout << "Contact doesn't exist! Try again." << std::endl;;
        }
    }
    tw.update(NULL, head, con_found);
    while (true){
        Node* down = NULL;
        if (tw.current->get_type() == "contact"){
            Contact* con = (Contact*) tw.current;
            down = con->get_down();
        } else if (tw.current->get_type() == "property"){
            Property* prop = (Property*) tw.current;
            down = prop->get_down();
        }
        if (down == NULL){
            return;
        }
        if (down->get_type() == "data"){
            return;
        }
        list_prop(down);
        Node* found = NULL;
        std::cout << "Select property (type \"this\" to select current level.):" << std::endl;;
        std::string inp;
        std::getline(std::cin, inp);
        lowerCase(inp);
        if (inp == "this"){
            return;
        }
        found = search_property(down, inp);
        if (found == NULL){
            std::cout << "Property doesn't exist! Try again." << std::endl;;
        } else {
            tw.update(tw.current, down, found);
        }
    }
}

void build_property_hierarchy(TraverseWrapper tw, GeneralStack* gs){
    while (true){
        std::cout << "New subproperty name? (type \"stop\" to create your new data on current property)" << std::endl;
        std::string inp;
        std::getline(std::cin, inp);
        lowerCase(inp);
        if (gs->is_empty()){
            if (inp == "stop"){
                std::cout << "You need to create at least one new property!" << std::endl;
                continue;
            }
            Node* down = NULL;
            if (tw.current->get_type() == "contact"){
                Contact* con = (Contact*) tw.current;
                down = con->get_down();
            } else if (tw.current->get_type() == "property"){
                Property* prop = (Property*) tw.current;
                down = prop->get_down();
            }
            Node* found = search_property(down, inp);
            if (found){
                std::cout << "This property already exists! Try another property name." << std::endl;  
                continue;
            }
            Node* new_nd = new_property(inp, NULL, NULL);
            Property* new_prop = (Property*) new_nd;
            gs->push(new_prop);
        } else {
            if (inp == "stop"){
                return;
            }
            Node* new_nd = new_property(inp, NULL, NULL);
            Property* new_prop = (Property*) new_nd;
            gs->push(new_prop);
        }
    }
}

Node* inject_property(Node* head, Node* nd){
    nd->set_next(head);
    return nd;
}

void print_con(Node* head){
    Node* current = head;
    static int indent = 0;
    while (current != NULL){
        if (current->get_type() == "contact"){
            Contact* cur_cont = (Contact*) current;
            std::cout << "- contact: " << cur_cont->get_name() << std::endl;
            indent = 1;
            print_con(cur_cont->get_down());
        } else if (current->get_type() == "property"){
            Property* cur_prop = (Property*) current;
            std::cout << makeIndent(indent) << "- property: " << cur_prop->get_key() << std::endl;
            indent++;
            print_con(cur_prop->get_down());
            indent--;
        } else if (current->get_type() == "data"){
            Data* cur_data = (Data*) current;
            std::cout << makeIndent(indent) << "- value: " << cur_data->get_value() << std::endl;
        }
        if (current->get_type() == "contact"){
            break;
        }
        current = current->get_next();
    }
}