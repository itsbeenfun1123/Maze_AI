#ifndef BENZMAZE_HPP
#define BENZMAZE_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include <iostream>
#include <random>

class BenzMazeGenerator : public MazeGenerator
{
public:
    void generateMaze(Maze& maze) override;
    std::vector<Direction> choices(int x, int y, Maze& maze);
    void digTunnel(int x, int y, Maze& maze, std::default_random_engine& engine);

private:
    std::vector<std::vector<bool>> visited;
};



#endif