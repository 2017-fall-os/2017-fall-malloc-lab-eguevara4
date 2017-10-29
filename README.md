# os-malloc
This directory contains:

myAllocator.c: a first-fit and best-fit allocator

The updated version of myAllocator.c has 4 updated functions.

findBestFit()
This function returns the block prefix of a block that is
larger or equal to the requested size but is also the smallest
among the ones that are greater or equal to the requested size.

bestFitAllocRegion()
This function is the same as firstFitAllocRegion() except it
uses the funtion findBestFit() to find a block.

resizeRegionOriginal()
This function is the original implementation of resizeRegion()
The new implementation is resizeRegion();

resizeRegion()
This function instead of creating a new block it modifies the
orignal blocks. The idea is to find if the next block of the
block that is being resized is free. If it is then it checks
if there is enough space for the new size when the two are combined.
If it has enough space then the suffix of the block being resized
is moved. The prefix of the next block is also moved. Both
blocks prefixes and suffixes are updated to reflect the new positions.

myAllocator.h: its header file

myAllocatorTest1.c: a test program for my allocator

This file is used to test the implementations of resizeRegion() and
bestFitAllocRegion().

malloc.c: a replacement for malloc that uses my allocator
test1.c: a test program that uses this replacement malloc



There are two different testers as some implementations of printf
call malloc to allocate buffer space. This causes test1 to behave
improperly as it uses myAllocator as a malloc replacement. In this
case myAllocatorTest1 will function correctly. The only difference
between the programs is that test1 uses myAllocator as a malloc
replacement and myAllocatorTest1 uses myAllocator directly.

Makefile: a fairly portable "makefile", targets "all" and "clean"

To compile: 
 $ make 
To clean:
 $ make clean

The cygwin runtime uses malloc() and brk() extensively.  It is
interesting to compare the output of test1 & myAllocatorTest1.  All
those extra allocated regions are being used by cygwin's libraries!

