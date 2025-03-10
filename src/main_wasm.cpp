
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>

#include "js.h"
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

uint maze_count = 1;

EM_BOOL keyDownCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) 
{
    
    if(keyEvent->key[0] == ' ')
    {
        
        pause = !pause;

        if(pause){
            cout << "Paused" << endl;
        }else{
            cout << "Unpaused" << endl;
        }

    }
	return false;

}

uint GetTimestamp()
{

    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(
        p1.time_since_epoch()
    ).count();

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
            width = js_random(10,64);
            height = js_random(10,64);
         
            cout << maze_count++ << ": Begin generating " << width << "x" << height << " maze" << endl;
            
            start_time = GetTimestamp();
            mazeGen.Initialize(width, height);
            state = GENERATE;
            break;

        }
        case(GENERATE):
        {
        
            if(!mazeGen.MazeComplete())
            {
                
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
            cout << "Begin solving maze via BFS" << endl;
            start_time = GetTimestamp();
            mazeSolve.SetMaze(mazeGen.GetSet(), width, height, mazeGen.GetEntry(), mazeGen.GetExit());
            state = SOLVE;

            break;
            
        }
        case(SOLVE):
        {

            if(!mazeSolve.MazeComplete())
            {
                
                // run single maze solving cycle
                mazeSolve.SolveStep();

                // print maze
                PutString(mazeSolve.toString());
                
                return;

            }

            cout << "Solved maze with " << mazeSolve.RoomsVisited() << " steps." << endl;
            cout << "Time: " << GetTimestamp() - start_time << " seconds." << endl;

            state = INIT_GENERATION;
            
            cout << "Generating new maze in 3 seconds..." << endl;
            emscripten_sleep(3000);

            break;

        }
        case(HALT):
        {
            
            break;
        
        }
        default:
        {
        
            break;
        
        }

    }

}

int main()
{

    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, true, keyDownCallback);
    emscripten_set_main_loop(loop, 0, false);
	return 0;

}