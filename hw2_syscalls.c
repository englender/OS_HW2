//
// Created by ronien on 05/05/2019.
//
#include <sys/types.h>

int is_short(pid_t pid){

//    if(pid<0){            //roni - should we check for this?
//        return -ESRCH;
//    }
    task_t* p=find_task_by_pid(pid);
    if(p == NULL){
        return -ESRCH;
    }
    if(p->policy == SCHED_SHORT)
        return 1;

    return 0;
}

int short_remaining_time(pid_t pid){

//    if(pid<0){            //roni - should we check for this?
//        return -ESRCH;
//    }
    task_t* p=find_task_by_pid(pid);
    if(p == NULL){
        return -ESRCH;
    }
    if(p->policy != SCHED_SHORT)
        return -EINVAL;
    return (p->requested_time)*HZ/1000;
}

int short_place_in_queue(pid_t pid){

}