#include <ics46/factory/DynamicFactory.hpp>
#include "BenzMazeSolution.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(
    MazeSolver, BenzMazeSolver, "BenzMaze Solver (Required)");



void BenzMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    trial.resize(maze.getWidth(), std::vector<bool>(maze.getHeight(), false));
    testing(maze, mazeSolution);
}


bool BenzMazeSolver::testing(const Maze& maze, MazeSolution& mazeSolution)
{
    std::pair<int, int> current = mazeSolution.getCurrentCell();
    std::pair<int, int> ending = mazeSolution.getEndingCell();

    if( current == ending)
    {
        return true;
    }
    
    else
    {
        if(trial[current.first][current.second])
        {
            return false;
        }

        trial[current.first][current.second] = true;
        
        if(maze.wallExists(current.first, current.second, Direction::down) == false && 
        trial[current.first][current.second+1] == false)
        {
            mazeSolution.extend(Direction::down);
            if (testing(maze, mazeSolution) == false)
            {
                mazeSolution.backUp();
            }else{
                return true;
            }
        }

        if(maze.wallExists(current.first, current.second, Direction::right) == false && 
        trial[current.first+1][current.second] == false)
        {
            mazeSolution.extend(Direction::right);
            if (testing(maze, mazeSolution) == false)
            {
                mazeSolution.backUp();
            }else{
                return true;
            }
        }

        if(maze.wallExists(current.first, current.second, Direction::up) == false && 
        trial[current.first][current.second-1] == false)
        {
            mazeSolution.extend(Direction::up);
            if (testing(maze, mazeSolution) == false)
            {
                mazeSolution.backUp();
            }else{
                return true;
            }
        }

        if(maze.wallExists(current.first, current.second, Direction::left) == false && 
        trial[current.first-1][current.second] == false)
        {
            mazeSolution.extend(Direction::left);
            if (testing(maze, mazeSolution) == false)
            {
                mazeSolution.backUp();
            }else{
                return true;
            }
        }

        return false;

    }
}