#include "spinlock_ece391.h"
#include "solution.h"
#include <bits/types.h>


void update_queue(ps_lock *ps){
    if(ps->professors && (!ps->ta || !ps->student)){
        ps->professors--;
        ps->prof_occup++;
        ps->occupancy++;
    }
    else if(!ps->prof_occup && ps->ta){
        ps->ta--;
        ps->ta_occup++;
        ps->occupancy++;
    }
    else if(!ps->prof_occup && ps->student){
        ps->student--;
        ps->student_occup++;
        ps->occupancy++;
    }
}

ps_lock ps_lock_create(spinlock_t *lock) {
  // Fill this out!!!
    spinlock_init_ece391(lock);
    ps_lock a = {
        .spinlock = lock,
        .occupancy = 0,
        .student = 0,
        .ta = 0,
        .professors = 0,
        .student_occup = 0,
        .ta_occup = 0,
        .prof_occup = 0
    };
    return a;
}

void professor_enter(ps_lock *ps) {
  // Fill this out!!!
    spinlock_lock_ece391(ps->spinlock);
    if(ps->student_occup || ps->ta_occup || ps->occupancy >= 20){
        ps->professors++;
    }
    else {
        ps->prof_occup++;
        ps->occupancy++;
    }
    spinlock_unlock_ece391(ps->spinlock);
}

void professor_exit(ps_lock *ps) {
  // Fill this out!!!
    spinlock_lock_ece391(ps->spinlock);
    ps->prof_occup--;
    ps->occupancy--;
    update_queue(ps);
    spinlock_unlock_ece391(ps->spinlock);
}

void ta_enter(ps_lock *ps) {
  // Fill this out!!!
    spinlock_lock_ece391(ps->spinlock);
    if(ps->prof_occup || ps->occupancy >= 20){
        ps->ta++;
    }
    else {
        ps->ta_occup++;
        ps->occupancy++;
    }
    spinlock_unlock_ece391(ps->spinlock);
}

void ta_exit(ps_lock *ps) {
  // Fill this out!!!
    spinlock_lock_ece391(ps->spinlock);
    ps->ta_occup--;
    ps->occupancy--;
    update_queue(ps);
    spinlock_unlock_ece391(ps->spinlock);
}

void student_enter(ps_lock *ps) {
  // Fill this out!!!spinlock_lock_ece391(ps->spinlock);
    if(ps->prof_occup || ps->occupancy >= 20){
        ps->student++;
    }
    else {
        ps->student_occup++;
        ps->occupancy++;
    }
    spinlock_unlock_ece391(ps->spinlock);
}

void student_exit(ps_lock *ps) {
  // Fill this out!!!
    spinlock_lock_ece391(ps->spinlock);
    ps->student_occup--;
    ps->occupancy--;
    update_queue(ps);
    spinlock_unlock_ece391(ps->spinlock);
}

