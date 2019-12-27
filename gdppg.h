/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

    int count;

protected:
    static void _bind_methods();

public:
    void add(int p_value);
    void reset();
    int get_total() const;

    GdPPG();
};

#endif // PPG_H