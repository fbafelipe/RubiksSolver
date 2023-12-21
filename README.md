# RubiksSolver

<p>This is a very simple implementation of a solver for the Rubik's Cube puzzle.</p>

# Building

To build RubiksSolver run these commands:

    $ mkdir build && cd build
    $ cmake .. -DCMAKE_BUILD_TYPE=Release
    $ make

# Output

The output is a list of the moves to be performed in order to solve the Rubik's Cube.<br>
The moves are described as the face you need to rotate, with the Rubik's cube Red Face (the face with the Red Center) facing to you, and the Blue Face (the face with the Blue Center) Facing top.
The face to be rotated is described by a letter representing each face (T is Top, B is Bottom, R is Right, L is Left, N is Near and F is Far) where Near is the face that is facing to you, and Far is the opposite face.
The rotations are clockwise, unless there is an `i` (inverse), then the rotation is counter-clockwise.

### Example output

```
Best: 198
Best: 156
Best: 148
Best: 142
Best: 140
Best: 118
Best: 114
Best: 112
Best: 110
Best: 106
Timeout with 132315 attempts
Solution found with 104 moves. (optimized from 106)
Look at red face, with blue top, then rotate this sequence:

Ti Bi N L L Bi Ti Fi T L Fi T Ri T T N T N Ri Li B L R N Bi Ni T Ni Ti Bi Ni Bi N B B Li Bi L Fi Bi F B Ni T N Ti R R Bi N N Ti F T R N Li N L N N Ri B B Ri Bi R B Fi Bi F B Fi Bi F B Fi Bi F Bi N Bi Ni Bi Ri B R Bi N L B Li Bi Ni B N B Ni B N B B Ni B
```
