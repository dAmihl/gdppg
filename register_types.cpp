/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "gdppg.h"
#include "PPGNodeRef.h"

void register_gdppg_types() {
    ClassDB::register_class<GdPPG>();
	ClassDB::register_class<PPGNodeRef>();
}

void unregister_gdppg_types() {
   // Nothing to do here in this example.
}
