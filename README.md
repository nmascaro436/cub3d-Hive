# cub3D

A 3D maze game written in C that uses raycasting to draw a first-person view from a 2D map, inspired by Wolfenstein 3D.

*This project was created as part of the 42 curriculum at Hive Helsinki, as a group of two.*

## Features
- Raycasting engine that renders a pseudo-3D view in real time
- Textured walls
- Floor and ceiling colours
- Player movement and rotation through the maze
- Maps loaded from files, with validation

## Built with
C, MLX42 graphics library, Makefile

## How to run
```bash
make
./cub3D path/to/map.cub
```
Example maps are in the `maps/` folder.

## What I learned
Cub3D was my first project with graphics. I learned how raycasting turns a flat 2D map into a 3D view, and how much of it depends on math and careful handling of edge cases. Loading and validating maps taught me to check input before using it, and working in a group of two meant splitting the work and combining it without breaking each other's code.
