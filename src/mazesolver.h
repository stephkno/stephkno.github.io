#ifndef MAZESOLVE_H
#define MAZESOLVE_H

    #include <string>
    #include <unordered_map>
    #include <sstream>

    #include "queue.h"
    #include "disjoint_set.h"

    class MazeSolver{

        DisjointSet<uint> mazeSet;
        Queue_<uint> room_queue;
        vector<bool> visited;

        uint width, height;
        uint entry, exit;

        uint current_room = 0;
        uint n_steps = 0;

        // whether maze has been solved
        bool solved = false;

        // whether solved path has been found
        bool pathed = false;

        // map to track parent of all steps
        // room, parent room
        vector<int> parents;

        // path from entrance to exit
        vector<uint> path;

        // char representation of maze rooms
        string mazeWalls[16] = {
            "╬","╣","╩","╝","╠","║","╚","✘",
            "╦","╗","═","✘","╔","✘","✘","▒"
        };
        string thinMazewalls[16] = {
            "┼","┤","┴","┘","├","│","└","↓",
            "┬","┐","─","→","┌","↑","←","▒"
        };
        string thickMazewalls[16] = {
            "╋","┫","┻","┛","┣","┃","┗","✘",
            "┳","┓","━","✘","┏","✘","✘","▒"
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

        void SolveStep();

        bool MazeComplete();
        uint RoomsVisited();
        string toString();

    };

#endif