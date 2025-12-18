#include <stdlib.h>
#include <iostream>
#include <string>
#include <cinttypes>
#include <cstdio>

#define W 10
#define H 10
#define INF 255

const std::string Letters = "ABCDEFGHIJ";
const int8_t LettersSize = 10;
const int8_t MaxNumberGrid = 10;


const char Robot = 'R';
const char Wall  = 'X';
const char Merkis = 'G';
const char Empty = 'O';

//ingromacija par šunu
struct State {
    uint8_t x;
    uint8_t y;
    uint8_t dir; //0=N,1=E,2=S,3=W
};

//Lai mainītu virzienu, mums jāpievieno vērtība no šiem masīviem.
const int8_t dx[4] = {0,1,0,-1};
const int8_t dy[4] = {-1,0,1,0};


std::uint8_t Attalums[MaxNumberGrid][LettersSize][4];


void SetChar(char **massivs, int8_t CordsLetters, int8_t CordsNumber, char CharToSet){
    if(massivs[CordsNumber][CordsLetters]!=Empty){return;}

    massivs[CordsNumber][CordsLetters]=CharToSet;
}
int8_t CordFromLetters(std::string x){
    return Letters.find(x[0]);

}
int8_t CordFromNumber(std::string x){
    return std::stoi(x.substr(1))-1;
}


bool bfsWithPath(char **arr,
                 uint8_t sx, uint8_t sy, uint8_t sdir,
                 uint8_t gx, uint8_t gy,
                 char *actions, uint16_t &len) {

    uint8_t dist[H][W][4];
    uint8_t parentDir[H][W][4];
    char parentAct[H][W][4];

    // Initialize
    for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
            for(int d=0; d<4; d++)
                dist[y][x][d] = INF;

    State queue[200]; // fixed-size queue
    uint16_t head = 0, tail = 0;

    auto push = [&](State s){ queue[tail++] = s; };
    auto pop  = [&](){ return queue[head++]; };
    auto empty = [&](){ return head == tail; };

    dist[sy][sx][sdir] = 0;
    push({sx,sy,sdir});

    while(!empty()) {
        State cur = pop();
        uint8_t cd = dist[cur.y][cur.x][cur.dir];

        if(cur.x == gx && cur.y == gy)
            break;

        // Turn left
        uint8_t ld = (cur.dir + 3) % 4;
        if(dist[cur.y][cur.x][ld] == INF){
            dist[cur.y][cur.x][ld] = cd+1;
            parentDir[cur.y][cur.x][ld] = cur.dir;
            parentAct[cur.y][cur.x][ld] = 'L';
            push({cur.x, cur.y, ld});
        }

        // Turn right
        uint8_t rd = (cur.dir + 1) % 4;
        if(dist[cur.y][cur.x][rd] == INF){
            dist[cur.y][cur.x][rd] = cd+1;
            parentDir[cur.y][cur.x][rd] = cur.dir;
            parentAct[cur.y][cur.x][rd] = 'R';
            push({cur.x, cur.y, rd});
        }

        // Move forward
        int nx = cur.x + dx[cur.dir];
        int ny = cur.y + dy[cur.dir];

        if(nx>=0 && nx<W && ny>=0 && ny<H && arr[ny][nx]!=Wall){
            if(dist[ny][nx][cur.dir] == INF){
                dist[ny][nx][cur.dir] = cd+1;
                parentDir[ny][nx][cur.dir] = cur.dir;
                parentAct[ny][nx][cur.dir] = 'F';
                push({(uint8_t)nx,(uint8_t)ny,cur.dir});
            }
        }
    }

    // Find best direction at goal
    uint8_t bestDir = 0;
    uint8_t bestDist = INF;
    for(uint8_t d=0; d<4; d++){
        if(dist[gy][gx][d] < bestDist){
            bestDist = dist[gy][gx][d];
            bestDir = d;
        }
    }
    if(bestDist == INF) return false;

    // Reconstruct path backwards
    len = 0;
    uint8_t cx = gx;
    uint8_t cy = gy;
    uint8_t cd = bestDir;

    while(!(cx==sx && cy==sy && cd==sdir)){
        char act = parentAct[cy][cx][cd];
        actions[len++] = act;
        uint8_t pd = parentDir[cy][cx][cd];

        if(act=='F'){
            cx -= dx[pd];
            cy -= dy[pd];
        }
        // L/R: position unchanged
        cd = pd;
    }

    // Reverse actions to correct order
    for(int i=0;i<len/2;i++){
        char tmp = actions[i];
        actions[i] = actions[len-1-i];
        actions[len-1-i] = tmp;
    }

    return true;
}


int main(){

    std::string Start = "A1";
    std::string Goal  = "H8";
    std::string NOT = 
    "B2,C2,D2,E2,F2,G2,H2,I2,J2,"   // top horizontal wall row
    "B3,B4,B5,B6,B7,"                   // vertical wall in column B
    "D3,D4,D5,D6,"                       // vertical wall in column D
    "F4,F5,F6,F7,F8,"                // vertical wall in column F
    "H3,H4,H5,H6,H7,"                   // vertical wall in column H
    "A9,B9,C9,D9,E9,F9,G9,H9,I9,J9";   // bottom horizontal wall row


    //Izveidojam massivu
    char **arr;
    arr = (char**) malloc(sizeof(char*) * MaxNumberGrid);

    for(int8_t i=0; i<MaxNumberGrid; i++){
        arr[i] = (char*) malloc(sizeof(char) * LettersSize);
    }

    //Aizpildam masivu.
    for(int8_t i=0; i<MaxNumberGrid; i++){
        for(int8_t j = 0; j<LettersSize;j++){

            arr[i][j]= Empty;

        }
    }

    SetChar(arr,CordFromLetters(Start),CordFromNumber(Start),Robot);
    SetChar(arr,CordFromLetters(Goal),CordFromNumber(Goal),Merkis);

    int8_t pos=NOT.find(',');
    std::string cord;
    while(pos != std::string::npos){
        cord = NOT.substr(0,pos);
        SetChar(arr,CordFromLetters(cord),CordFromNumber(cord),Wall);
        NOT.erase(0,pos+1);
        pos = NOT.find(',');
    }
    if(NOT.length()!=0){
        SetChar(arr,CordFromLetters(NOT),CordFromNumber(NOT),Wall);
    }



    //parbaude
    for(int8_t i=0; i<MaxNumberGrid; i++){
        for(int8_t j = 0; j<LettersSize;j++){

            std::cout<<arr[i][j]<<' ';

        }
        std::cout<<std::endl;
    }

    //attalumi initialization
    for (int y = 0; y < MaxNumberGrid; y++)
        for (int x = 0; x < LettersSize; x++)
            for (int d = 0; d < 4; d++)
                Attalums[y][x][d] = 255;

    uint8_t sx = CordFromLetters(Start);
    uint8_t sy = CordFromNumber(Start);

    uint8_t gx = CordFromLetters(Goal);
    uint8_t gy = CordFromNumber(Goal);

    // start North
    uint8_t startVirz = 0;

    char actions[200];
    uint16_t len = 0;

    bool found = bfsWithPath(arr, sx, sy, 0, gx, gy, actions, len);

    if(found){
        std::cout<<std::endl;
        for(uint16_t i=0;i<len;i++) std::cout << actions[i] << ' ';
        std::cout << "\nTotal actions: " << len << "\n";
    }else{
        std::cout << "No path found\n";
}
}
