//
// Created by ronien on 05/05/2019.
//
//#include <sys/types.h>
#include <linux/sched.h>


//#define MAX_PRIO 139

int is_short(pid_t pid){

    if(pid<0){
        return -ESRCH;
    }
    task_t* p=find_task_by_pid(pid);
    if(p == NULL){
        return -ESRCH;
    }
    if(p->policy == SCHED_SHORT)
        return 1;

    return 0;
}

int short_remaining_time(pid_t pid){

    if(pid<0){
        return -ESRCH;
    }
    task_t* p=find_task_by_pid(pid);
    if(p == NULL){
        return -ESRCH;
    }
    if(p->policy != SCHED_SHORT)
        return -EINVAL;
    return (p->time_slice)*HZ/1000;
}

int short_place_in_queue(pid_t pid){

    if(pid<0){
        return -ESRCH;
    }
    task_t* p=find_task_by_pid(pid);
    if(p == NULL){
        return -ESRCH;
    }
    if(p->policy != SCHED_SHORT)
        return -EINVAL;

    int index, count=0;
    list_t *ptr;
    runqueue_t *rq = this_rq();
    list_t *head = rq->short_array->queue;
//    prio_array_t *shrt=rq->short_array;

    for (index = 0; index <MAX_PRIO; index++) {
        list_t *curr  = head + index;

        list_for_each(ptr, curr){
            if (list_entry(ptr, task_t, run_list)->pid == pid){
                return count;
            }
            count++;
        }
    }
    return -EINVAL;
}
