# C++ Barrier Implementation
This is a basic implementation of a thread barrier using C++ condition variables. Sample usage can be found in main.cpp.
An instance of the barrier class is protected against spurious wakeups and valid for multiple uses (multiple "generations" is the terminology some use).