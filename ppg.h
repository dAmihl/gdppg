/* ppg.h */

#ifndef PPG_H
#define PPG_H

#include "core/reference.h"

class PPG : public Reference {
    GDCLASS(PPG, Reference);

    int count;

protected:
    static void _bind_methods();

public:
    void add(int p_value);
    void reset();
    int get_total() const;

    PPG();
};

#endif // PPG_H