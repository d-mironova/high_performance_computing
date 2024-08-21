# Makefile for demonstrating circular dependency

target1: target3
\ttouch target1

target2: target1
\ttouch target2

target3: target2
\ttouch target3

