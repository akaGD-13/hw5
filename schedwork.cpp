

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(int day, int position, AvailabilityMatrix avail,
    const size_t dailyNeed,
    const size_t maxShifts, vector<int>& maxShifts_vec,
    DailySchedule& sched
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    vector<int> maxShifts_vec;
    for (size_t i=0; i < avail[0].size(); i++){
        maxShifts_vec.push_back(0);
    }

    for (size_t i=0; i < avail.size(); i++){
        vector<Worker_T> temp;
        for (int i=0; i<dailyNeed; i++){
          temp.push_back(-1);
        }
        sched.push_back(temp);
    }
    

    return schedule_helper(0,0,avail, dailyNeed, maxShifts, maxShifts_vec, sched);

}


bool schedule_helper(int day, int position,  AvailabilityMatrix avail,
    const size_t dailyNeed,
    const size_t maxShifts, vector<int>& maxShifts_vec,
    DailySchedule& sched
)
{
    //base case
    if (day >= sched.size()){
        return true;
    }

    for (size_t i=0; i < avail[day].size(); i++){ // i is the Worker_ID
        if (avail[day][i] == 1){// avaliable
            sched[day][position] = i;
            maxShifts_vec[i]+= 1;
            avail[day][i] = 0;

            if (maxShifts_vec[i] <= maxShifts){ 
                // next recursion
                bool status;
                if (position == dailyNeed -1){//last postion of the day
                    status = schedule_helper(day+1,0,avail, dailyNeed, maxShifts, maxShifts_vec, sched); //new day, first position
                }
                else{
                    status = schedule_helper(day,position+1,avail, dailyNeed, maxShifts, maxShifts_vec, sched);
                }

                if (status == true){
                    return true;
                }
            }
            maxShifts_vec[i] -= 1; // this option does not work, reset it 
            avail[day][i] = 1;         
        }
        
    }

    return false; // run out of all options


}

