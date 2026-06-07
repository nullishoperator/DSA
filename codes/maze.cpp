#include "farhad.h"
using namespace std;
bool solve(int x, int y, Array<Array<bool>> &maze, Array<Array<int>> &moves,Array<int> move, Array<Array<int>>& answer ){
    maze[x][y]=true;
    answer.insert(move);
    x=x+move[0];
    y=y+move[1];
    if(x>=maze.getLength() || y>=maze[0].getLength() || x<0 || y<0 || maze[x][y]==true)
        return false;
    if(x==maze.getLength()-1 && y==maze[0].getLength()-1)
        return true;
    for(int i=0;i<moves.getLength();i++){
        if(solve(x,y,maze,moves,moves[i],answer))
            return true;
        answer.remove();
    }
    return false;
}
bool findPath(Array<Array<bool>> &maze, Array<Array<int>> &moves,Array<Array<int>>& answer){
    return solve(0,0,maze,moves,moves[0],answer);
}
int main(){

    Array<Array<bool>> maze{
        {false,false,false,false,false,false,false,true,false,false},//0
        {false,false,false,false,false,false,true,false,false,false},//1
        {false,false,false,false,false,true,false,false,false,false},//2
        {false,false,false,false,true,false,false,true,false,false},//3
        {false,false,false,true,false,false,false,true,false,false},//4
        {false,false,true,false,false,false,false,true,false,false},//5
        {false,true,false,false,false,false,false,true,false,false},//6
        {false,false,false,false,false,false,false,true,false,false},//7
        {false,false,false,false,false,false,false,true,false,false},//8
    //     0     1     2     3     4     5     6     7    8     9
    };
    Array<Array<int>> moves{
        {1,0},//down
        {0,1},//right
        {-1,0},//up
        {0,-1}//left
    };
    Array<Array<int>> answer;
    if(findPath(maze,moves,answer))
        cout<<answer;
    
    return 0;
}