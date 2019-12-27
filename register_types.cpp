/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "ppg.h"

void register_ppg_types() {
    ClassDB::register_class<PPG>();
}

void unregister_ppg_types() {
   // Nothing to do here in this example.
}