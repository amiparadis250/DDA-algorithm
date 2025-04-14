# Computer Graphics: Line and Circle Drawing Algorithms

This project implements two fundamental computer graphics algorithms:
1. DDA (Digital Differential Analyzer) Line Drawing Algorithm
2. Midpoint Circle Drawing Algorithm

Both algorithms are implemented in C++ using SDL2 for visualization and demonstrate the core concepts of rasterization in computer graphics.

## Overview

The application provides a visual representation of line and circle drawing algorithms with a grid of dots for better visualization. The implementations follow the mathematical principles of these classical algorithms while providing an interactive way to see how they work.

## Algorithms Implemented

### 1. DDA (Digital Differential Analyzer) Line Algorithm

DDA is a line drawing algorithm used to determine which pixels should be colored to form a straight line between two given points. It works by calculating intermediate positions along the line path and rounding them to the nearest integer coordinates.

#### How DDA Works:

1. Calculate the differences in x and y coordinates (dx, dy)
2. Determine the number of steps needed (maximum of |dx| or |dy|)
3. Calculate the increment values for x and y coordinates
4. Starting from the first endpoint, increment x and y, rounding to the nearest integer, and plot each point

#### Advantages:
- Simple implementation
- Works for all line slopes
- Handles both steep and gentle slopes

#### Limitations:
- Requires floating-point calculations which may cause rounding errors
- Can appear less precise than Bresenham's algorithm for certain line angles

### 2. Midpoint Circle Algorithm

The Midpoint Circle Algorithm is an efficient method for drawing circles by leveraging symmetry. It determines which pixels should be colored to form a circle of a given radius around a center point.

#### How Midpoint Circle Works:

1. Calculate the initial decision parameter p = 1 - radius
2. Start at point (0, radius) relative to the center
3. For each step, decide whether to move to E or SE based on the decision parameter
4. Update the decision parameter accordingly
5. Use 8-way symmetry to plot points in all octants

#### Advantages:
- Only uses integer arithmetic, making it efficient
- Leverages symmetry to reduce calculations
- Produces a smooth circle appearance

#### Limitations:
- Works only for circles (requires modifications for ellipses)
- May produce visual artifacts for very small radii

## Implementation Details

### Graphics Rendering
- SDL2 is used for window creation and rendering
- Points are rendered as 2×2 pixel squares to enhance visibility

### Grid System
- A grid of dots is drawn as reference points
- Input coordinates are scaled to match the grid spacing
- Grid spacing is configurable (default: 20 pixels)

### User Interface
- Command-line interface for input of coordinates
- Visual output through an SDL2 window
- Supports window resizing and event handling

## How to Use

1. Compile the program using a C++ compiler with SDL2 libraries
2. Run the executable
3. Follow the prompts to enter coordinates:
   - For lines: starting point (x0, y0) and ending point (x1, y1)
   - For circles: center point (x, y) and radius
4. The window will display the resulting line or circle on a grid

## Building and Running

### Prerequisites
- C++ compiler (GCC, Clang, MSVC)
- SDL2 development libraries

### Compilation

```bash
# For DDA Line Algorithm
g++ dda_line.cpp -o dda_line -lSDL2

# For Midpoint Circle Algorithm
g++ midpoint_circle.cpp -o midpoint_circle -lSDL2
```

### Running

```bash
# Run DDA Line Algorithm
./dda_line

# Run Midpoint Circle Algorithm
./midpoint_circle
```

## Sample Outputs

### DDA Line Drawing
When drawing a line from (2,2) to (22,12), the algorithm plots points along the path, creating a straight line across the grid.

### Midpoint Circle Drawing
When drawing a circle with center at (15,15) and radius 10, the algorithm creates a perfect circle by plotting points in all eight octants.

## Mathematical Foundation

### DDA Line Algorithm
For a line from (x0,y0) to (x1,y1):
- dx = x1 - x0
- dy = y1 - y0
- steps = max(|dx|, |dy|)
- x_increment = dx / steps
- y_increment = dy / steps

For each step i from 0 to steps:
- x = x0 + i * x_increment
- y = y0 + i * y_increment
- Plot point at (round(x), round(y))

### Midpoint Circle Algorithm
For a circle with center (xc,yc) and radius r:
- Start at point (0,r) relative to center
- Initial decision parameter p = 1 - r

For each x from 0 while x < y:
- If p < 0: 
  - Move to E (x+1,y)
  - p = p + 2x + 1
- Else: 
  - Move to SE (x+1,y-1)
  - p = p + 2(x-y) + 1
- Use 8-way symmetry to plot points in all octants

## Credits
This implementation was created as part of a Computer Graphics assignment to demonstrate fundamental rasterization algorithms.