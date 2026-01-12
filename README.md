# Skyline-Analyzer

## Overview
#### This project constructs the 2D "skyline" (outer contour) of a city given a set of rectangular buildings. It reads building coordinates, processes them as vertical edge events, and outputs the critical points where the height of the skyline changes.The core of the solution is a Sweep-Line Algorithm backed by a Modified Priority Queue. Unlike a standard C++ std::priority_queue, this custom data structure supports the efficient removal of any specific building's height when the sweep line passes its right edge.

## Key Features
#### Sweep-Line Algorithm: Decomposes buildings into "Left" and "Right" edge events and processes them in sorted order along the x-axis.Modified Priority Queue (MPQ):A custom binary heap implementation ModifiedPQueue.Maintains a lookup table (location vector) to map input indices to heap positions.Arbitrary Removal: Allows removing non-root elements in $O(\log N)$ time, which is critical for removing a building's height once its end x-coordinate is reached.Optimized Sorting: Implements a custom Quicksort with Median-of-Three pivoting and hybrid Insertion Sort for small subarrays to sort building edges efficiently.Edge Case Handling: Handles multiple building edges aligning on the same x-coordinate and buildings starting at $x=0$.

## How It Works
#### Event Generation: Each building defined by (x_{left}, height, x_{right}) is split into two nodes: 7
  #### Start Node: Stores x_{left} and height.
  #### End Node: Stores x_{right} and height.
#### Sorting: All nodes are sorted by their x-coordinates using the custom Quicksort implementation.
#### Sweeping: The program iterates through the sorted nodes: If a Start Node is encountered, the height is inserted into the MPQ.If an End Node is encountered, the height is removed from the MPQ using its original input index.The program checks getMax() from the heap. If the maximum height changes compared to the previous step, a contour point (x, new\_height) is printed.

## Input Format (input.txt)
#### The program reads from a file named input.txt.First Line: Integer N (number of buildings).Subsequent Lines: N lines containing 3 integers each: x_left height x_right
