#!/bin/bash

# Compilation with different optimization levels and frame pointer settings
gfortran -O0 -fno-omit-frame-pointer omit_frame_pointer.f90 -o prog_a
gfortran -O0 -fomit-frame-pointer omit_frame_pointer.f90 -o prog_b
gfortran -O1 -fno-omit-frame-pointer omit_frame_pointer.f90 -o prog_c
gfortran -O1 -fomit-frame-pointer omit_frame_pointer.f90 -o prog_d
gfortran -O2 -fno-omit-frame-pointer omit_frame_pointer.f90 -o prog_e
gfortran -O2 -fomit-frame-pointer omit_frame_pointer.f90 -o prog_f

echo "Compilation complete. Executables created: prog_a, prog_b, prog_c, prog_d, prog_e, prog_f"

