#include "buildlist.h"

void process(PropertyStack* ps){
    if (! ps->is_empty()){
        int ind_level = ps->get_top().indent;
        while (true){
            PropertyWrapper a = ps->pop();
            if (ps->is_empty()){
                ps->push(a);
                break;
            }
            PropertyWrapper b = ps->pop();
            if (b.indent < ind_level){
                ps->push(b);
                ps->push(a);
                break;
            }
            b.property->set_next(a.property);
            ps->push(b);
        }
    }
}

void build_property(LineStack* ls, PropertyStack* ps, int ind){
    Node* last_data = NULL;
    while (ls->get_top()->get_indent() >= ind){
        Line* temp = ls->pop();
        if (temp->get_type() == "value"){
            last_data = new_data(temp->get_content(), last_data);
        } else if (temp->get_type() == "property"){
            if (! ps->is_empty()){
                if (temp->get_indent() < ps->get_top().indent){
                    process(ps);
                    Property* child_prop = ps->pop().property;
                    Property* new_prop = (Property* ) new_property(temp->get_content(), child_prop, NULL);
                    ps->push(PropertyWrapper(new_prop, temp->get_indent()));
                } else {
                    Property* new_prop = (Property* ) new_property(temp->get_content(), last_data, NULL);
                    ps->push(PropertyWrapper(new_prop, temp->get_indent()));
                }
            } else {
                Property* new_prop = (Property* ) new_property(temp->get_content(), last_data, NULL);
                ps->push(PropertyWrapper(new_prop, temp->get_indent()));            
            }
        }
    }
}

void build_contact(GeneralizedList& db, LineStack* ls, PropertyStack* ps){
    Node* last_data = NULL;
    while (! ls->is_empty()){
        Line* temp = ls->pop();
        if (temp->get_type() == "value"){
            last_data = new_data(temp->get_content(), last_data);
        } else if (temp->get_type() == "property"){
            if (! ps->is_empty()){
                if (temp->get_indent() < ps->get_top().indent){
                    process(ps);
                    Property* child_prop = ps->pop().property;
                    Property* new_prop = (Property* ) new_property(temp->get_content(), child_prop, NULL);
                    ps->push(PropertyWrapper(new_prop, temp->get_indent()));
                } else {
                    Property* new_prop = (Property* ) new_property(temp->get_content(), last_data, NULL);
                    ps->push(PropertyWrapper(new_prop, temp->get_indent()));
                }
            } else {
                Property* new_prop = (Property* ) new_property(temp->get_content(), last_data, NULL);
                ps->push(PropertyWrapper(new_prop, temp->get_indent()));            
            }
        } else if (temp->get_type() == "contact"){
            process(ps);
            if (! ps->is_empty()){
                Property* child_prop = ps->pop().property;
                db.insert_contact(temp->get_content(), child_prop);
            } else {
                db.insert_contact(temp->get_content(), NULL);
            }
        }
    }
}

void build_db(File& file, GeneralizedList& db){
    LineStack* ls = new LineStack;
    PropertyStack* ps = new PropertyStack;
    std::string read;
    file.changeMode("read");
    while (getline(file.expose(), read)){
        Line* l = new Line(read);
        if (ls->is_empty()){
            ls->push(l);
        } else if (l->get_indent() >= ls->get_top()->get_indent()){
            ls->push(l);
        } else if (l->get_indent() < ls->get_top()->get_indent()){
            if (l->get_type() == "contact"){
                build_contact(db ,ls, ps);
                ls->push(l);
            } else if (l->get_type() == "property"){
                build_property(ls, ps, l->get_indent());
                ls->push(l);
            }
        }
    }
    build_contact(db ,ls, ps);
}