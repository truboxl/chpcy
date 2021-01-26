#include <stdio.h>
#include <unistd.h>

#include "portability.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        puts("chpcy <tid> [<policy>]\n");
        puts("Show or change the Android scheduling policy (PCY) for a given thread or process");
        puts("Powered by libprocessgroup / libcutils\n");
        puts("Example:");
        puts("\tchpcy 2340\tget scheduling policy for TID 2341");
        puts("\tchpcy 15678 bg\tset TID 15678 in bg policy");
        return 0;
    }
    SchedPolicy current_policy;
    int tid;
    sscanf(argv[1], "%d", &tid);
    char *fmt = "TID %d's %s scheduling policy: %s\n";
    if (argc == 2) {
        int result = get_sched_policy(tid, &current_policy);
        printf(fmt, tid, "current", get_sched_policy_name(current_policy));
        return result;
    }
    if (argc == 3) {
        // TODO still no idea why it does not work
        get_sched_policy(tid, &current_policy);
        printf(fmt, tid, "current", get_sched_policy_name(current_policy));
        int new_policy;
        sscanf(argv[2], "%d", &new_policy);
        int result = set_sched_policy(tid, new_policy);
        get_sched_policy(tid, &current_policy);
        printf(fmt, tid, "new", get_sched_policy_name(current_policy));
        return result;
    }
    if (argc > 3) {
        puts("Invalid argument!");
        return -1;
    }
}
