#ifndef MAZEGEN_H
#define MAZEGEN_H

    #include "disjoint_set.h"
    #include <vector>
    #include <sstream>
    #include <string>
    #include <cmath>
    #include <algorithm>
    #include <random>

    using namespace std;

    class BadNeighbor{
    public:
        string Msg() {
            return "Neighbor out of bounds error.";
        }
    };

    class MazeGenerator{



        // maze rooms
        //vector<uint> maze_rooms;
        vector<uint> rooms_unvisited;

        // maze data
        uint width, height;
        uint entry = 0;
        uint exit = -1;
        uint room_cursor = -1;

        bool initialized = false;

        // disjoint set to represent connection between rooms in maze
        DisjointSet<uint> mazeSet;

        // char representation of maze rooms
        string mazeWalls[16] = {
            "╬","╣","╩","╝","╠","║","╚","↓",
            "╦","╗","═","→","╔","↑","←","▒"
        };
        // Dead end indices: 7, 11, 13, 14

        // maze directions
        enum Direction
        {
            RIGHT = 1,
            UP = 2,
            LEFT = 4,
            DOWN = 8,
        };

        // Get index of neighbor room by room index and direction
        int getNeighbor(uint room, Direction direction);
        
        // return random int between min,max
        int random(uint min, uint max);

        // remove a wall between room and neighbor
        bool RemoveWall(uint room, uint neighbor, Direction direction, Direction neighborDirection);

    public:

        MazeGenerator();

        MazeGenerator(uint width, uint height);

        ~MazeGenerator();

        bool random_order = false;

        // returns true when maze has finished generating
        // tests if all subsets are joined
        bool MazeComplete();

        // initializes blank maze of size width x height
        void Initialize(uint width, uint height);

        // generate maze
        void Generate();

        // single step generate maze
        void GenerateStep();

        uint GetExit()
        {
            return exit;
        }

        // return string representaion of maze
        string toString();

        DisjointSet<uint> & GetSet(){
            return mazeSet;
        }

    };

#endif