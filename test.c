#include <stdio.h>

#include "portability.h"


int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);
    printf("argv = %lu\n", sizeof(**argv)); // sizeof(*argv[]) gives error
    for(int i = 0; i < argc; i++) {
        printf("arg[%d]: %s\n", i, argv[i]);
    }
    for(int i = -2; i < 11; i++) {
        printf("policy id %d: %s\n", i, get_sched_policy_name(i));
    }
    
#if 0
    // Android 10?
    if(cpusets_enabled()) {
        puts("cpusets enabled");
    } else {
        puts("cpusets disabled");
    }
    if(schedboost_enabled()) {
        puts("schedboost enabled");
    } else {
        puts("schedboost disabled");
    }
#endif

#if 0
    // Android 10+?
    for(int i=-1; i<10; i++) {
        printf("policy id %d: %s\n", i, get_cpuset_policy_profile_name(i));
    }
    for(int i=-1; i<10; i++) {
        printf("policy id %d: %s\n", i, get_sched_policy_profile_name(i));
    }
#endif
    return 0;
}
