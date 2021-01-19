# chpcy

### What?

A small utiliy that show or change the Android scheduling policy (PCY) for a given thread or process

Powered by libprocessgroup / libcutils

### Why?

To check out how Android use internal libraries to manage thread scheduling

### Where to use?

Mostly on Android, especially Termux. Can be used in app I think...

### Why not release binary?

Since it depends on libprocessgroup.so or libcutils.so that is Android version specific and NDK does not provide stubs for compiling, you have to compile the binary on your own.

### How to compile?

Anything that uses `libprocessgroup` needs to be built from AOSP!!!

This is why `toybox` that allows reading PCY using `top` & `ps` have to be built from AOSP. See [landley/toybox#43 comment](https://github.com/landley/toybox/issues/43#issuecomment-261735594).

While I haven't did that yet, the other methods are:

1. Pull `/system/lib64/libprocessgroup.so` from device and use NDK to build `chpcy`. TODO

1. Build `chpcy` directly on-device using Termux, which you can just:

        $ make

### How to use?

    $ ./chpcy <pid>
    $ ./chpcy <pid> <policy>

### It does not work! / It can't change PCY!

May need higher privilege accounts like root, or some stuff that I don't know. Sorry, TODO

### Why not to use `chpcy`? (or `libprocessgroup` in general)

Aside from "unknown" problems, it seems that old `libcutils` code just fallback to Linux scheduling methods (`SCHED_BATCH`, `SCHED_NORMAL` etc) but has been removed in newer version which may or may not still using it. See [old code](https://android.googlesource.com/platform/system/core.git/+/android-4.2.2_r1/libcutils/sched_policy.c)

This [commit](https://android.googlesource.com/platform/system/core/+/82b72a566761b8379fd2964ed801696803867510%5E%21/libprocessgroup/sched_policy.cpp) seems to change the code yet again to use task profiles.

I also wonder if normal users / applications should use `libprocessgroup` at all since it seems to delegate to hardware / kernel / system uses.

### Extra references

<https://laptrinhx.com/android-process-scheduling-3378431205/>

<https://github.com/landley/toybox/search?q=pcy>

<https://android.googlesource.com/platform/system/core/+/master/libcutils/sched_policy_test.cpp>

<https://android.googlesource.com/platform/system/core/+/master/libprocessgroup/include/processgroup/sched_policy.h>

<https://android.googlesource.com/platform/system/core/+/master/libprocessgroup/sched_policy.cpp>

### TLDR

Just use `chrt`, `sched_setscheduler()` or those Java APIs in user space if you have no root
