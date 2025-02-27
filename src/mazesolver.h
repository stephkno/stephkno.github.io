#ifndef MAZESOLVE_H
#define MAZESOLVE_H

    #include <string>
    #include <map>
    #include <sstream>

    #include "queue.h"
    #include "disjoint_set.h"

    class MazeSolver{

        DisjointSet<uint> mazeSet;
        Queue_<int> room_queue;
        vector<bool> visited;

        uint width, height;
        uint entry, exit;

        uint current_room = 0;
        uint n_steps = 0;
        bool solved = false;

        // char representation of maze rooms
        string mazeWalls[16] = {
            "╬","╣","╩","╝","╠","║","╚","✘",
            "╦","╗","═","✘","╔","✘","✘","▒"
        };
        string thinMazewalls[16] = {
            "┼","┤","┴","┘","├","│","└","↓",
            "┬","┐","─","→","┌","↑","←","▒"
        };

        // maze directions
        enum Direction
        {
            RIGHT = 1,
            UP = 8,
            LEFT = 4,
            DOWN = 2
        };

        int getNeighbor(int room, Direction direction);

    public:

        MazeSolver();
        ~MazeSolver();
        void SetMaze(DisjointSet<uint> & mazeSet, uint width, uint height, uint entry, uint exit);

        bool SolveStep();

        bool MazeComplete();
        uint RoomsVisited();
        string toString();

    };

#endif