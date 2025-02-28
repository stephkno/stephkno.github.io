#include "mazesolver.h"

int MazeSolver::getNeighbor(int room, Direction direction)
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

MazeSolver::MazeSolver()
{

}

MazeSolver::~MazeSolver()
{

}

void MazeSolver::SetMaze(DisjointSet<uint> & mazeSet, uint width, uint height, uint entry, uint exit)
{

    this->mazeSet = mazeSet;
    this->width = width;
    this->height = height;
    this->entry = entry;
    this->exit = exit;
    this->current_room = this->entry;
    this->n_steps = 0;

    this->solved = false;
    this->pathed = false;

    visited.clear();
    path.clear();
    parents.clear();

    room_queue.Enqueue(this->entry);

    for(int i = 0; i < width*height; i++){
        visited.push_back(false);
    }
    for(int i = 0; i < width*height; i++){
        parents.push_back(-1);
    }

}

void MazeSolver::SolveStep()
{
    #ifdef DEBUG
        cout << "Step" << endl;
    #endif

    // backtrack after maze has been solved to find path
    if(solved)
    {
        if(current_room != entry){
            current_room = parents[current_room];
            path.push_back(current_room);
        }else{
            pathed = true;
        }
        return;
    }

    current_room = room_queue.Dequeue();

    #ifdef DEBUG
        cout << "Currently in room: " << current_room << endl;
    #endif

    if(current_room == exit){
        solved = true;
        room_queue.Clear();
        return;
    }

    visited[current_room] = true;

    n_steps++;

    int n = -1;
    int room = mazeSet[current_room];
    
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
            room_queue.Enqueue(static_cast<uint>(n));
            parents[n] = current_room;
        }
    }
    
    // UP
    if((~room & UP))
    {
        n = getNeighbor(current_room, UP);

        if(n>=0 && !visited[n])
        {
            room_queue.Enqueue(static_cast<uint>(n));
            parents[n] = current_room;
        }
    }
    
    // LEFT
    if((~room & LEFT))
    {
        n = getNeighbor(current_room, LEFT);

        if(n>=0 && !visited[n])
        {
            room_queue.Enqueue(static_cast<uint>(n));
            parents[n] = current_room;
        }
    }

    // DOWN
    if((~room & DOWN))
    {
        n = getNeighbor(current_room, DOWN);

        if(n>=0 && !visited[n])
        {
            room_queue.Enqueue(static_cast<uint>(n));
            parents[n] = current_room;
        }
    }

    return;

}

bool MazeSolver::MazeComplete()
{
    return solved && pathed;
}

uint MazeSolver::RoomsVisited()
{
    return n_steps;
}

string MazeSolver::toString()
{

    stringstream os;
    uint i = 0;
    
    for(uint y = 0; y < height; y++)
    {
        
        for(uint x = 0; x < width; x++)
        {

            if(i == current_room)
            {
                #ifdef WASM
                    os << "<b class=\"blink\">☻</b>";
                #else
                    os << "☻";
                #endif
            }
            else if(i == entry)
            {
                #ifdef WASM
                    os << "<b class=\"blink\">S</b>";
                #else
                    os << "S";
                #endif
            }
            else if(i == exit)
            {
                #ifdef WASM
                    os << "<b class=\"blink\">E</b>";
                #else
                    os << "E";
                #endif
            }
            else if(!visited[i])
            {
                os << thinMazewalls[mazeSet[i]];
            }
            else if(find(path.begin(), path.end(), i) != path.end())
            {
                os << mazeWalls[mazeSet[i]];
            }
            else
            {
                os << thickMazewalls[mazeSet[i]];
            }
            
            i++;

        }

        #ifdef WASM
            os << "<br>";
        #else
            os << endl;
        #endif
    }
    return os.str();

}
