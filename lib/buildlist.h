#ifndef BUILD_LIST_H
#define BUILD_LIST_H

#include "datastructures.h"
#include "filehandling.h"

void process(PropertyStack*);
void build_property(LineStack*, PropertyStack*, int);
void build_contact(GeneralizedList&, LineStack*, PropertyStack*);
void build_db(File&, GeneralizedList&);

#endif