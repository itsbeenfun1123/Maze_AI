#ifndef BENZMAZESOLUTION_HPP
#define BENZMAZESOLUTION_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <iostream>
#include <vector>

class BenzMazeSolver : public MazeSolver
{
    public:
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
        bool testing(const Maze& maze, MazeSolution& mazeSolution);

    private:
        std::vector<std::vector<bool>> trial;
};








#endif