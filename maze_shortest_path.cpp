#include <iostream>
#include <queue>
#include <string>

/* Maze structure
 * 0 = Wall
 * 1 = Available (Empty space)
 * 2 = Exit (Terminal point)
 */

#define wall 0
#define empty_space 1
#define terminal_point 2

// M × N Matrix
#define M 10
#define N 10

// Coordinate data structure to store maze cell locations
struct Coordinate
{
    int x, y;
};

// Maze cell data structure
struct Cell
{
    Coordinate location; // Cell coordiantes (x, y)
    int distance; // Minimum distance from the source of the maze
};

// Below arrays detail all four possible movements from a cell
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

bool IsValidNeighbour(int maze[][N], bool visited[][N], int row, int col)
{
    // Check if the target location is in maze boundaries
    if ((row >= 0) && (row < M) && (col >= 0) && (col < N))
    {
        // Check if the location is not a wall and has not already been visited
        if (maze[row][col] != wall && !visited[row][col]) return true;
    }
    return false;
}

// An algorithm based on BFS (Breadth First Search) traveral
int FindShortestPath(int maze[][N], Coordinate source)
{
    // A binary matrix to keep track of all visited cells
    bool visited[M][N] { false };

    // Queue to keep track of cells that need to be visited
    std::queue<Cell> q;

    int min_distance = INT_MAX;

    // Processing the source cell:
    visited[source.x][source.y] = true;
    q.push({ {source.x, source.y}, 0 });

    while (!q.empty())
    {
        // Dequeue the front of the queue to process it
        Cell current_cell = q.front();
        q.pop();

        // If the current cell is the exit, then save the minimum distance and break out of the while loop
        if (maze[current_cell.location.x][current_cell.location.y] == terminal_point)
        {
            min_distance = current_cell.distance;
            break;
        }

        // Check all adjacent cells for validity and add them to queue if valid
        for (int i = 0; i < 4; i++)
        {
            Coordinate next_cell { current_cell.location.x + row[i], current_cell.location.y + col[i] };
            if (IsValidNeighbour(maze, visited, next_cell.x, next_cell.y))
            {
                // Mark the target cell as visited and add it to the processing queue
                visited[next_cell.x][next_cell.y] = true;
                q.push({ next_cell, current_cell.distance + 1 });
            }
        }
    }

    return (min_distance != INT_MAX) ? min_distance : 0;
}

int main()
{
    // Maze
    int maze[M][N] =
    {
        { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 1, 1, 0, 0, 2 },
    };

    Coordinate starting_point { 0,0 };

    // Finding the shortest path from the starting point to the exit/terminal point (specified in matrix)
    int distance = FindShortestPath(maze, starting_point);

    if (distance != 0) std::cout << "The shortest path from starting point to terminal point has length: " << distance;
    else std::cout << "The exit can't be reached from the given starting point";

    return 0;
}