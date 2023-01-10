# Multi-Dimensional-Tic-Tac-Toe

Text-based Tic-Tac-Toe in any dimension and any size. Supports diagonals across all dimensions.\\

**Features include:**
- Tutorial
- Game parameter customization (you can change the size and dimension of the board)
- 2+ player multiplayer

## Tutorial:
This tutorial can be found in the game, by typing tutorial.\
\
This is tic-tac-toe in varying dimensions, of varying size.\
Here is an empty 3d board of width 3:

```
+-----------+
|   |   |   |
|   |   |   |
|   |   |   |
+-----------+
```

Coordinates start at 0 and end at (width - 1).\
For example, this X is the point with coordinates (1 2 0) for the same board:
```
+-----------+
|   |   |   |
|   |   |   |
| X |   |   |
+-----------+
```
and this O is the point with coordinates (1 2 2):
```
+-----------+
|   |   |   |
|   |   |   |
| X |   | O |
+-----------+
```
A player wins by filling a straight diagonal in any dimension.\
For example, here are some ways to win:

A diagonal across 1 dimension
```
+-----------+
|   |   |   |
|   |   |   |
|   |XXX|   |
+-----------+
```
A diagonal across 2 dimensions
```
+-----------+
|   |   |  X|
|   |   | X |
|   |   |X  |
+-----------+
```
Another diagonal across 2 dimensions
```
+-----------+
|   |   |   |
|   |   |   |
|X  | X |  X|
+-----------+
```
A diagonal across 3 dimensions
```
+-----------+
|   |   |  X|
|   | X |   |
|X  |   |   |
+-----------+
```
Beware: diagonals can go through all N dimensions of the board.\
Here, they can step through all 3 dimensions\
In a 4d board, they can step through all 4.\
\
Have Fun!
