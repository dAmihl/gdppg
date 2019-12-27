/* gdppg.cpp */

#include "gdppg.h"

void GdPPG::add(int p_value) {
    count += p_value;
}

void GdPPG::reset() {
    count = 0;
}

int GdPPG::get_total() const {
    return count;
}

void GdPPG::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add", "value"), &GdPPG::add);
    ClassDB::bind_method(D_METHOD("reset"), &GdPPG::reset);
    ClassDB::bind_method(D_METHOD("get_total"), &GdPPG::get_total);
}

GdPPG::GdPPG() {
    count = 0;
}