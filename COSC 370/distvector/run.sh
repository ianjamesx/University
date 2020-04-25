#!/bin/bash
cc prog3.c node0.c node1.c node2.c node3.c -w #just ignore all warnings for now
echo "Program compiled, running..."
./a.out #run program
