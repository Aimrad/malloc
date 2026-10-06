_This project has been created as part of the 42 curriculum by gtoure._

## Description
This project is an implementation of a dynamic memory allocator in C.
It provides custom versions of malloc, free, realloc, and show_alloc_mem, using memory zones managed with mmap.

## Instructions
- git clone the project https://github.com/Aimrad/malloc.git
- To build the project `make `
- To clean the project `make fclean`
- To clean and rebuild the project `make re`

Although it is compiled to be used as a library if you want to test the program you can do
- To run the tests: `make test`
- To build the test executable without running it: `make test-debug`
- To run the tests with Valgrind: `make test-valgrind`

And modify the test files to your heart content if you need to test something

## Resources

- The Fundamentals: What is dynamic memory ?
  - https://ena.etsmtl.ca/pluginfile.php/865698/mod_folder/content/0/11-Allocation%20dynamique/Cours11-AllocationDynamique-3pp.pdf ( A very clear document for beginners on dynamic allocation, featuring prototypes and simple examples. )
  - http://www0.cs.ucl.ac.uk/staff/B.Karp/0019/s2020/lectures/0019-lecture6-mem-alloc.pdf ( A classic introduction that lays the groundwork: the heap, blocks, and the role of the operating system. )

- The Heart of the Reactor: How malloc works internally
  - https://www.andrew.cmu.edu/course/14-513-f18/recitations/recitation10-malloc1.pdf ( Course material that comprehensively covers the concepts of free lists, splitting, and coalescing. )
  - https://www.cs.cmu.edu/afs/cs/academic/class/15213-s12/www/recitations/rec11.pdf ( Another reference document that explains the implementation of an allocator in detail, particularly block header management and coalescing. )
  - https://www.cs.princeton.edu/courses/archive/fall16/cos217/lectures/20_DynamicMemory-6up.pdf ( This document explains the various strategies—such as using singly or doubly linked lists for the free list—and why a doubly linked list speeds up the free operation. )

 - System Heap Management: sbrk vs. mmap
   - https://users.cs.utah.edu/~mflatt/past-courses/cs4400/f16/malloc.pdf ( A clear explanation of using mmap to create memory regions, highlighting the advantages and disadvantages. )

### AI usage

AI tools were used to help review code structure, testing and improve the documentation. The implementation, debugging, and final decisions were carried out and verified by the project author.
