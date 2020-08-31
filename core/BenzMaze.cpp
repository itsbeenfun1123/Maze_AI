#include <ics46/factory/DynamicFactory.hpp>
#include "BenzMaze.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(
    MazeGenerator, BenzMazeGenerator, "BenzMaze Generator (Required)");

void BenzMazeGenerator::generateMaze(Maze& maze)
{
    maze.addAllWalls();
    visited.resize(maze.getWidth(), std::vector<bool>(maze.getHeight(), false));
    std::random_device device;
    std::default_random_engine engine{device()};
    digTunnel(0, 0, maze, engine);
}

std::vector<Direction> BenzMazeGenerator::choices(int x, int y, Maze& maze)
{
    std::vector<Direction> directionSet;
    if (x+1 < maze.getWidth() && visited[x+1][y] != true)
    {
        directionSet.push_back(Direction::right);
    }
    if (y+1 < maze.getHeight() && visited[x][y+1] != true)
    {
        directionSet.push_back(Direction::down);
    }
    if (x > 0 && visited[x-1][y] != true)
    {
        directionSet.push_back(Direction::left);
    }
    if (y > 0 && visited[x][y-1] != true)
    {
        directionSet.push_back(Direction::up);
    }

    return directionSet;
}


void BenzMazeGenerator::digTunnel(int x, int y, Maze& maze, std::default_random_engine& engine)
{
    visited[x][y] = true;
    std::vector<Direction> unvisited = choices(x, y, maze);
    int options = unvisited.size();

    while(unvisited.size() > 0)
    {
        std::uniform_int_distribution<int> dis{1,options};
        int dice = dis(engine) - 1;

        if (unvisited[dice] == Direction::right)
        {
            maze.removeWall(x, y, Direction::right);
            digTunnel(x+1, y, maze, engine);
        }

        if (unvisited[dice] == Direction::down)
        {
            maze.removeWall(x, y, Direction::down);
            digTunnel(x, y+1, maze, engine);
        }

        if (unvisited[dice] == Direction::left)
        {
            maze.removeWall(x, y, Direction::left);
            digTunnel(x-1, y, maze, engine);
        }

        if (unvisited[dice] == Direction::up)
        {
            maze.removeWall(x, y, Direction::up);
            digTunnel(x, y-1, maze, engine);
        }

        unvisited = choices(x, y, maze);
        options = unvisited.size();
    }


}