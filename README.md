# datastructs.h
C library of commonly used data types and data structures. It's a hobby project mainly for my own amusement and for practice, but it's also aimed to be portable and installable.

As of now, the library is under development. Updates will be made irregularly and... eventually.

## Overview
The library provides the following functionalities:
  * string
  * array (more secure than traditional C arrays, inspired by C++)
  * vector (dynamic arrays, inspired by C++)
  * matrix (2D and 3D arrays)
  * linked list
  * stack
  * queue
  * binary tree (n-ary tree?)
  * and a lot more...

## Installation

### Linux
Coming soon...

### Windows and MacOS
We'll see...

## Further development
To-do list (for now):
  * finish string type
    * conversions: string to number
    * conversions: number to string
  * array vs. vector: decide which one to implement
    * pro's of doing both: more tools catering to more specific needs
    * con's of doing both: the only difference is that vectors are resizeable while arrays aren't. Apart from that, they're identical.
  * rename ``NO_WARNINGS`` to ``DATASTRUCTS_NO_WARNINGS``
  * possibility to turn off warnings not just globally, but to individual sub-libraries (i.e. ``DATASTRUCTS_NO_WARNINGS_STRING``, etc.)
  * make the library installable

## (Re)sources
Valuable resources that helped along the way:
  * My university professor's lecture notes: http://aszt.inf.elte.hu/~asvanyi/ad/ad1jegyzet/ad1jegyzet.pdf
  * https://people.inf.elte.hu/pgm6rw/algo/
  * Jacob Sorber's YouTube channel: https://www.youtube.com/@JacobSorber
