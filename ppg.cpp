/* ppg.cpp */

#include "ppg.h"

void PPG::add(int p_value) {
    count += p_value;
}

void PPG::reset() {
    count = 0;
}

int PPG::get_total() const {
    return count;
}

void PPG::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add", "value"), &PPG::add);
    ClassDB::bind_method(D_METHOD("reset"), &PPG::reset);
    ClassDB::bind_method(D_METHOD("get_total"), &PPG::get_total);
}

PPG::PPG() {
    count = 0;
}