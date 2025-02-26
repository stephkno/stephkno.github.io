#include "mazegen.h"

//#define DEBUG

int MazeGenerator::getNeighbor(uint room, Direction direction)
{

    int r = room;

    if(direction == UP && r - width >= 0)
    {
        return room - width;
    }
    else if(direction == DOWN && r + width < width*height)
    {
        return room + width;
    }
    else if(direction == RIGHT && r % width < width-1)
    {
        return room + 1;
    }
    else if(direction == LEFT && r % width != 0)
    {
        return room - 1;
    }

    // no valid room found
    return -1;

}

int MazeGenerator::random(uint min, uint max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}

bool MazeGenerator::RemoveWall(uint room, uint neighbor, Direction direction, Direction neighborDirection)
{

    #ifdef DEBUG
        cout << "Removing wall between room #" << room << " and room #" << neighbor << endl;
    #endif
    
    if(mazeSet[room] - direction <= 0 or mazeSet[neighbor] - direction <= 0)
    {
        return false;
    }

    mazeSet[room] -= direction;
    mazeSet[neighbor] -= neighborDirection;

    return true;

}

MazeGenerator::MazeGenerator() : width(0), height(0)
{
    //std::srand( ( unsigned int )std::time( nullptr ) );
}

MazeGenerator::MazeGenerator(uint width, uint height) : width(width), height(height) 
{
    Initialize(width, height);
}

MazeGenerator::~MazeGenerator()
{

}

bool MazeGenerator::MazeComplete()
{
    return mazeSet.NumSets() == 1;
}

void MazeGenerator::Initialize(uint width, uint height)
{

    this->width = width;
    this->height = height;

    rooms_unvisited.clear();
    uint n = width * height;

    for(uint i = 0; i < n; i++)
    {
        rooms_unvisited.push_back(i);
    }

    mazeSet.NewSubset(n);

    this->initialized = true;
    
    // shuffle spaces to visit if in random mode
    if(random_order)
    {
        auto rng = default_random_engine{};
        shuffle(begin(rooms_unvisited), end(rooms_unvisited), rng);
    }
}

// generate Maze
void MazeGenerator::Generate()
{

    if(!initialized)
    {
        // throw uninitialized error
        return;
    }
    while(!MazeComplete())
    {
        GenerateStep();
    }

}

// generate MazeGenerator single step
void MazeGenerator::GenerateStep()
{
    if(!initialized)
    {
        // throw uninitialized error
        return;
    }

    // continue while MazeGenerator is not one set
    if(mazeSet.NumSets() > 1)
    {

        // get room
        auto room = rooms_unvisited.back();
        room_cursor = room;
        
        int r = random(0,3);
        Direction direction = Direction( pow( 2, r ) );
        
        // get neighboring room
        auto neighbor = getNeighbor(room, direction);

        #ifdef DEBUG
            cout << "Room: " << room << " Direction: " << direction << " Neighbor: " << neighbor << endl;
        #endif
        
        if(neighbor < 0)
        {
            #ifdef DEBUG
                cout << "Error: Neighbor less than 0" << endl;
            #endif
            return;
        }

        // check if room and neighbor are already connected to the Maze
        if(mazeSet.SameSet(room, neighbor))
        {
            #ifdef DEBUG
                cout << "Error: Room and neighbor are in same set" << endl;
            #endif
            return;

        }

        if(!mazeSet.Union(room, neighbor))
        {
            #ifdef DEBUG
                cout << "Error: Union" << endl;
            #endif
            return;

        }
        
        // remove down walls connecting room and neighbor room
        switch(direction)
        {

            case UP:
            {
                if(!RemoveWall(room, neighbor, DOWN, UP))
                {
                    break;
                }
                break;
            }
            case DOWN:
            {
                if(!RemoveWall(room, neighbor, UP, DOWN))
                {
                    break;
                }
                break;
            }
            case LEFT:
            {
                if(!RemoveWall(room, neighbor, LEFT, RIGHT))
                {
                    break;
                }
                break;
            }
            case RIGHT:
            {
                if(!RemoveWall(room, neighbor, RIGHT, LEFT))
                {
                    break;
                }
                break;
            }
            default:
            {
                break;
            }

        }

        rooms_unvisited.pop_back();

    }

    if(MazeComplete()){

        // randomly place exit over a dead end room
        uint room = 0;

        do{

            room = random(1, width*height);
            exit = room;

        }while(room == 0 || 
            (mazeSet[room] != 7 && 
            mazeSet[room] != 11 && 
            mazeSet[room] != 13 && 
            mazeSet[room] != 14));
    }

    return;
}

string MazeGenerator::toString()
{

    stringstream os;

    uint i = 0;
    
    for(uint y = 0; y < height; y++)
    {
        
        for(uint x = 0; x < width; x++)
        {

            if(i == room_cursor)
            {
                os << "<b class=\"blink\">☺</b>";
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