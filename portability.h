/* portability.h
 *
 * Compatibilty header for compiling chpcy
 *
 */

#if defined(__BIONIC__)

#if __has_include(<processgroup/sched_policy.h>) // Android 10+
#include <processgroup/sched_policy.h>
#elif __has_include(<cutils/sched_policy.h>) // Android 4.1+
#include <cutils/sched_policy.h>

#else
extern int set_sched_policy(int tid, void *policy) __attribute__((weak));
extern int get_sched_policy(int tid, void *policy) __attribute__((weak));
extern char *get_sched_policy_name(int policy) __attribute__((weak));

#if 0
#include <stdbool.h>
extern bool cpusets_enabled() __attribute__((weak));
extern bool schedboost_enabled() __attribute__((weak));
#endif

#endif // __has_include

#else // glibc etc
static inline int set_sched_policy(int tid, void *policy) { return -1; }
static inline int get_sched_policy(int tid, void *policy) { return -1; }
static inline char *get_sched_policy_name(int policy) { return "error"; }

#endif // defined(__BIONIC__)


// unused for now
#if 0
static inline bool cpusets_enabled() { return -1; }
static inline bool schedboost_enabled() { return -1; }
static inline int set_cpuset_policy(int tid, void *policy) { return -1; }

// libprocessgroup only
static inline char *get_cpuset_policy_profile_name(int policy) { return "error"; }
static inline char *get_sched_policy_profile_name(int policy) { return "error"; }
#endif
