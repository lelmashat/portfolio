#ifndef EVENT_H
#define EVENT_H

#include "wire.h"

struct Event {
    uint64_t time;
    Wire* wire;
    char state;
};

struct EventLess {
    bool operator()(const Event& lhs, const Event& rhs) const {
        return lhs.time < rhs.time; // Sorting in descending order for a min-heap
    }
};

#endif

