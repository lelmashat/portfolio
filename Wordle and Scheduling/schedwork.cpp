#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID worker ID 
static const Worker_T INVALID_ID = (unsigned int)-1;


bool canSchedule(const AvailabilityMatrix& avail, const size_t day, const Worker_T worker) {
    return avail[day][worker];
}

// Helper function to check if a worker has reached the maximum shifts allowed over the period
bool isValidShifts(const DailySchedule& sched, const Worker_T worker, const size_t maxShifts) {
    size_t shifts = 0;
    for (const auto& day : sched) {
        shifts += count(day.begin(), day.end(), worker);
    }
    return shifts <= maxShifts;
}

bool backtrack(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day, Worker_T minWorker) {
    if (day == avail.size()) {
        // Base case: All days scheduled, check if all workers have valid shifts
        for (Worker_T worker = 0; worker < avail[0].size(); ++worker) {
            if (!isValidShifts(sched, worker, maxShifts))
                return false;
        }
        return true; // All workers have valid shifts for all days
    }

    // Try to assign workers for the current day
    for (Worker_T worker = minWorker; worker < avail[day].size(); ++worker) {
        if (canSchedule(avail, day, worker) && isValidShifts(sched, worker, maxShifts)) {
            sched[day].push_back(worker);
            if (sched[day].size() == dailyNeed) {
                // Move to the next day
                if (backtrack(avail, dailyNeed, maxShifts, sched, day + 1, 0))
                    return true; // A valid schedule found
            } else {
                // Continue assigning workers for the current day
                if (backtrack(avail, dailyNeed, maxShifts, sched, day, worker+1))
                    return true; // A valid schedule found
            }
            // cout << "Backtrack worker=" << worker << " day=" << day << endl;
            // Backtrack
            sched[day].pop_back();
        }
    }
    // No valid schedule found for the current day
    return false;
}




bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if (avail.size() == 0U) {
        return false;
    }
    sched.clear();
    size_t numWorkers = avail[0].size();
    size_t numDays = avail.size();
    
    sched.resize(numDays);
    if (backtrack(avail, dailyNeed, maxShifts, sched, 0, 0))
        return true;
    else {
        sched.clear(); // Clear schedule if no solution found
        return false;
    }
}

