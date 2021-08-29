#include <bits/stdc++.h>

using namespace std;

/*
Common mistakes with BFS
1. didn't leave a mark when visiting starting point
2. didn't leave a mark when pushing to queue
3. didn't do a proper check to see if neighboring element is out of range
*/



#define X first
#define Y second
#define MAX 1000

int board[MAX][MAX];
bool vis[MAX][MAX];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    queue<pair<int,int>> Q;
    vis[0][0]=1;
    Q.push({0,0});

    while(!Q.empty())
    {
        auto cur = Q.front();
        Q.pop();
        for (int dir=0;dir<4;dir++)
        {
            int xpos = cur.X + dx[dir];
            int ypos = cur.Y + dy[dir];
            if (xpos < 0 || xpos >= MAX || ypos <0 || ypos >= MAX) continue;
            if (vis[xpos][ypos] || board[xpos][ypos] != 1) continue;
            vis[xpos][ypos] = 1;
            Q.push({xpos,ypos}); 
        }
    }
}