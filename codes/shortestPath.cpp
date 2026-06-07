#include "farhad.h"
using namespace std;
int solve(int x,int y,Array<Array<int>> &maze ,Array<Array<int>> &moves )
{   
    
    static Queue<Array<int>> queue{Array<int>{x,y}};
    if(x==maze.getLength()-1 && y==maze[0].getLength()-1)
        return maze[x][y]-1;
    for(int i=0;i<moves.getLength();i++)
    {
        int nx = x+moves[i][0];
        int ny = y+moves[i][1];
        if(nx>=0 && ny>=0 && nx<maze.getLength() && ny<maze[0].getLength() && maze[nx][ny]==0){
            maze[nx][ny] = maze[x][y]+1;
            queue.insert(Array{nx,ny}); 
        }
    }

    queue.remove();
    if(queue.isEmpty())
        return -1;
    return solve(queue[0][0],queue[0][1],maze,moves);
    
}
int shortestPath(Array<Array<int>> &maze,Array<Array<int>> &moves){
    maze[0][0]=1;
    return solve(0,0,maze,moves);
}
int main()
{
    Array<Array<int>> maze{
                        {0,-1, 0,-1,-1,-1,-1,-1,-1, 0},
                        {0,-1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0,-1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0,-1,-1,-1,-1,-1,-1,-1,-1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    Array<Array<int>> moves{{1,0},
                            {0,1},
                            {-1,0},
                            {0,-1}};
    cout<<shortestPath(maze,moves)<<endl;
}
/*
                        {1,-1, 0,-1,-1,-1,-1,-1,-1, 0},
                        {0,-1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0,-1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0,-1,-1,-1,-1,-1,-1,-1,-1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
*/