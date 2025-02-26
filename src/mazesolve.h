#ifndef MAZESOLVE_H
#define MAZESOLVE_H

    #include <string>
    #include <map>

    #include "queue.h"
    #include "disjoint_set.h"

    class MazeSolver{

        DisjointSet<uint> mazeSet;
        vector<bool> visited;

        uint width, height;
        uint entry, exit;

        uint current_room = 0;
        uint x, y = 0;
        bool solved = false;

        Queue_<int> room_queue;

        // char representation of maze rooms
        string mazeWalls[16] = {
            "╬","╣","╩","╝","╠","║","╚","↓",
            "╦","╗","═","→","╔","↑","←","▒"
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

        int getNeighbor(int room, Direction direction)
        {
            int r = room;
            int w = width;
            int h = height;
            
            if(direction == UP && r - w >= 0)
            {
                return room - width;
            }
            else if(direction == DOWN && r + w < w*h)
            {
                return room + width;
            }
            else if(direction == RIGHT && r % w < w-1)
            {
                return room + 1;
            }
            else if(direction == LEFT && r % w != 0)
            {
                return room - 1;
            }

            // no valid room found
            return -1;

        }

    public:

        MazeSolver()
        {

        }

        ~MazeSolver()
        {

        }

        void SetMaze(DisjointSet<uint> & mazeSet, uint width, uint height, uint exit)
        {

            this->mazeSet = DisjointSet<uint>(mazeSet);
            this->width = width;
            this->height = height;
            this->entry = 0;
            this->exit = exit;

            room_queue.Enqueue((int)this->entry);

            for(int i = 0; i < width*height; i++){
                visited.push_back(false);
            }

        }

        bool SolveStep()
        {
            if(room_queue.Length() == 0)
            {
                return false;
            }

            current_room = room_queue.Dequeue();
            
            if(current_room == exit){
                solved = true;
                room_queue.Clear();
                return false;
            }

            //visited.insert({current_room, true});
            visited[current_room] = true;

            int n = -1;
            uint room = mazeSet[current_room];
            
            #ifdef DEBUG
                cout << "Room: " << current_room << " " << room << endl;
                cout << "R: " << std::bitset<8>(~room) << " " << std::bitset<8>(RIGHT) << endl;
                cout << "U: " << std::bitset<8>(~room) << " " << std::bitset<8>(UP) << endl;
                cout << "L: " << std::bitset<8>(~room) << " " << std::bitset<8>(LEFT) << endl;
                cout << "D: " << std::bitset<8>(~room) << " " << std::bitset<8>(DOWN) << endl;
            #endif
            
            // RIGHT
            if((~room & RIGHT))
            {
                n = getNeighbor(current_room, RIGHT);
                
                if(n>=0 && !visited[n])
                {
                    room_queue.Enqueue(n);
                }
            }
            
            // UP
            if((~room & UP))
            {
                n = getNeighbor(current_room, UP);

                if(n>=0 && !visited[n])
                {
                    room_queue.Enqueue(n);
                }
            }

            // LEFT
            if((~room & LEFT))
            {
                n = getNeighbor(current_room, LEFT);

                if(n>=0 && !visited[n])
                {
                    room_queue.Enqueue(n);
                }
            }

            // DOWN
            if((~room & DOWN))
            {
                n = getNeighbor(current_room, DOWN);

                if(n>=0 && !visited[n]){
                    room_queue.Enqueue(n);
                }
            }

            return true;

        }

        bool MazeComplete()
        {
            return room_queue.Length() == 0;
        }

        string toString()
        {
            stringstream os;

            uint i = 0;
            
            for(uint y = 0; y < height; y++)
            {
                
                for(uint x = 0; x < width; x++)
                {

                    if(i == current_room)
                    {
                        os << "<b class=\"blink\">☺</b>";
                    }
                    else if(i == entry)
                    {
                        os << "S";
                    }
                    else if(i == exit)
                    {
                        os << "E";
                    }
                    else if(visited[i])
                    {
                        os << mazeWalls[mazeSet[i]];
                    }
                    else
                    {
                        os << thinMazewalls[mazeSet[i]];
                    }
                    i++;

                }

                os << "<br>";

            }
            return os.str();

        }

    };

#endif