# chpcy

### What?

A small utiliy that show or change the Android scheduling policy (PCY) for a given thread or process

Powered by libprocessgroup / libcutils

### Why?

To check out how Android use internal libraries to manage thread scheduling

### Where to use?

Mostly on Android, especially Termux. Can be used in app I think...

### Why not release binary?

Since it depends on `libprocessgroup.so` or `libcutils.so` that is Android version specific and NDK does not provide stubs for compiling, you have to compile the binary on your own.

### How to compile?

Anything that uses `libprocessgroup` needs to be built from AOSP!!!

This is why `toybox` that allows reading PCY using `top` & `ps` have to be built from AOSP

<https://github.com/landley/toybox/issues/43#issuecomment-261735594>

While I figured out how, the other methods are:

1. Pull `/system/lib64/libprocessgroup.so` from device and use NDK to build `chpcy`. **TODO**

1. Build `chpcy` directly on-device using Termux, which you can just:

        $ make

### How to use?

    $ ./chpcy <pid>
    $ ./chpcy <pid> <policy>

### But it does not work! / it can't change PCY!

May need higher privilege accounts like root, or some stuff that I don't know. Sorry, **TODO**

#### Further investigation seems to suggest that libcutils / libprocessgroup are private libraries and shouldn't be used by user apps. If you really have to use them, you should bundle them yourself. This explains why the libs have to built from AOSP as Android version changes. I assume they will be blocked via linker namespaces.

<https://android-developers.googleblog.com/2016/06/improving-stability-with-private-cc.html>

<https://android-developers.googleblog.com/2016/06/android-changes-for-ndk-developers.html>

<https://github.com/android/ndk/issues/1186#issuecomment-585352743>

<https://source.android.com/devices/architecture/modular-system/runtime#linker-configuration-changes>

<https://source.android.com/devices/architecture/vndk/linker-namespace>

### Extra references

<https://laptrinhx.com/android-process-scheduling-3378431205/>

<https://github.com/landley/toybox/search?q=pcy>

<https://android.googlesource.com/platform/system/core/+/master/libcutils/sched_policy_test.cpp>

<https://android.googlesource.com/platform/system/core/+/master/libprocessgroup/include/processgroup/sched_policy.h>

<https://android.googlesource.com/platform/system/core/+/master/libprocessgroup/sched_policy.cpp>

<https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/os/Process.java>

### Proper alternatives (that are reliable for user applications) / TLDR

Just use `chrt` or `sched_setscheduler()` or `Java APIs` **TODO** in user space

<https://developer.android.com/reference/android/os/Process#THREAD_PRIORITY_BACKGROUND>

<https://github.com/android/ndk/issues/1182#issuecomment-582534626> (use Java API when NDK is missing the API)

<https://developer.android.com/about/versions/nougat/android-7.0-changes#ndk-update>
