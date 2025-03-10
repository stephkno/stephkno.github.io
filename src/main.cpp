
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>

#include "mazegen.h"
#include "mazesolver.h"

using namespace std;

enum MazeDriverState
{
    INIT_GENERATION = 0,
    GENERATE = 1,
    INIT_SOLVE = 2,
    SOLVE = 3,
    HALT = 4
};

MazeGenerator mazeGen;
MazeSolver mazeSolve;

MazeDriverState state;

bool pause = false;
uint start_time = 0;

uint width = 32;
uint height = 32;
uint maze_count = 0;

uint GetTimestamp()
{

    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(
        p1.time_since_epoch()
    ).count();

}

void PutString(string s)
{
    cout << s << endl;
}

// maze driver main loop
void loop()
{

    if(pause)
    {
        return;
    }

    switch(state)
    {

        case(INIT_GENERATION):
        {
            maze_count++;
            cout << maze_count << ": Begin generating " << width << "x" << height << " maze" << endl;
            
            start_time = GetTimestamp();
            mazeGen.Initialize(width, height);
            state = GENERATE;
            break;

        }
        case(GENERATE):
        {
        
            if(!mazeGen.MazeComplete())
            {
                cout << maze_count << endl;
                
                // run single maze generation cycle
                mazeGen.GenerateStep();
                
                // print maze
                PutString(mazeGen.toString());
                return;

            }

            // print maze gen time
            cout << "Done generating maze" << endl;
            cout << "Time: " << GetTimestamp() - start_time << " seconds." << endl;
            state = INIT_SOLVE;

            break;

        }
        case(INIT_SOLVE):
        {

            // initialize maze solve
            cout <<  maze_count << "Begin solving maze via BFS" << endl;
            start_time = GetTimestamp();
            mazeSolve.SetMaze(mazeGen.GetSet(), width, height, mazeGen.GetEntry(), mazeGen.GetExit());
            state = SOLVE;

            break;
            
        }
        case(SOLVE):
        {

            if(!mazeSolve.MazeComplete())
            {
                cout << maze_count << endl;

                // run single maze solving cycle
                mazeSolve.SolveStep();

                // print maze
                PutString(mazeSolve.toString());
                
                return;

            }

            cout << "Solved maze with " << mazeSolve.RoomsVisited() << " steps." << endl;
            cout << "Time: " << GetTimestamp() - start_time << " seconds." << endl;
            
            state = HALT;

            break;

        }
        case(HALT):
        {
            
            break;
        
        }
        default:
        {
            
            state = HALT;
            break;
        
        }

    }

}

int main()
{

    while(true){
        loop();
    }
	return 0;

}