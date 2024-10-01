#ifndef SCHEDWORK_H
#define SCHEDWORK_H

#ifndef RECCHECK
#include <vector>
#endif

// type for the ID of a worker
typedef unsigned int Worker_T;
// n-by-k Matrix of each of the k workers' availability over an n-day period
typedef std::vector<std::vector<bool>> AvailabilityMatrix;

// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T> > DailySchedule;

/**
 *  Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);

#endif
