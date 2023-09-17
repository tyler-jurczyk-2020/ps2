#include "spinlock_ece391.h"
#include "solution.h"
#include <bits/types.h>
#include <stdio.h>



ps_lock ps_lock_create(spinlock_t *lock) {

    ps_lock a;
	a.init = 0;
	spinlock_init_ece391(lock);
	a.init = 1;
	a.students = 0;
	a.professors = 0;
	a.tas = 0;
    a.professorsQueue = 0;
	a.tasQueue = 0;
    return a;
}

void professor_enter(ps_lock *ps) {
	int queued = 0;
	while(1){
		if(ps->init){
			spinlock_lock_ece391(ps->spinlock);
			//printf("%d",ps->students);
			if(ps->students==0 && ps->tas==0 || ps->occupancy < 20){
				ps->professors +=1;
				ps->occupancy +=1;
				if(queued){
					ps->professorsQueue-=1;
				}
				spinlock_unlock_ece391(ps->spinlock);	
				break;
			}else if(!queued){
				ps->professorsQueue +=1;
				queued = 1;
				spinlock_unlock_ece391(ps->spinlock);	
			}else{
				spinlock_unlock_ece391(ps->spinlock);	
			}

		}
	}
}

void professor_exit(ps_lock *ps) {
	while(1){
		if(ps->init){
			spinlock_lock_ece391(ps->spinlock);
			ps->professors-=1;
			ps->occupancy -=1;
			spinlock_unlock_ece391(ps->spinlock);
			break;
		}
	}
	
}

void ta_enter(ps_lock *ps) {
	int queued = 0;
	while(1){
		if(ps->init){
			spinlock_lock_ece391(ps->spinlock);
			if(ps->professors==0 && ps->occupancy < 20 && !ps->professorsQueue){
				ps->tas +=1;
				ps->occupancy +=1;
				if(queued){
					ps->tasQueue-=1;
				}
				spinlock_unlock_ece391(ps->spinlock);
				break;
			}else if(!queued){
				ps->tasQueue +=1;
				queued = 1;
				spinlock_unlock_ece391(ps->spinlock);
			}else{
				spinlock_unlock_ece391(ps->spinlock);
			}
		}
	}

}

void ta_exit(ps_lock *ps) {
	while(1){
		if(ps->init){
		spinlock_lock_ece391(ps->spinlock);
		ps->tas-=1;
		ps->occupancy -=1;
		spinlock_unlock_ece391(ps->spinlock);	
		break;
		}
	}
	
}


void student_enter(ps_lock *ps) {
	while(1){
		if(ps->init){
			spinlock_lock_ece391(ps->spinlock);
			if(ps->professors==0 && ps->occupancy < 20 && ps->professorsQueue ==0 &&  ps->tasQueue==0){
				ps->students +=1;
				ps->occupancy +=1;
				printf("%d",ps->students);
				spinlock_unlock_ece391(ps->spinlock);	
				break;
			}else{
				spinlock_unlock_ece391(ps->spinlock);	
			}
		}
	}
}

void student_exit(ps_lock *ps) {

	if(ps->init){
		spinlock_lock_ece391(ps->spinlock);
		ps->students-=1;
		ps->occupancy -=1;
		printf("%d",ps->students);
		spinlock_unlock_ece391(ps->spinlock);	
	}
}
