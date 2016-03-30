# PIC18F-Multitask
Simple multithreading on a PIC18F. Compiles with MikroC PRO. Currently tick is set at 1ms for test purposes. Ideally it should be 10ms+. 
Thread functions must not be too long or short jump from interrupt will fail.
