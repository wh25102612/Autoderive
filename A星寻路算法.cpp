#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define ZXDJ  10
#define XXDJ  14

#define ROWS 10
#define COLS 10

enum direct{p_up, p_down, p_left, p_right, p_lup, p_ldown, p_rup, p_rdown};

struct MyPoint{
    int row;
    int col;

    int f;
    int g;
    int h;

    void setF(){ f = g + h; }
};

struct treeNode{
    MyPoint				pos;
    vector<treeNode*>	child;
    treeNode*			pParent;
};

treeNode* createNode(int row, int col);
int getH(MyPoint pos, MyPoint endPos);

int main(){
    int map[ROWS][COLS] = {
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
    };
    bool pathMap[ROWS][COLS] = { 0 };

    MyPoint begPos = { 1, 1 };
    MyPoint endPos = { 9, 7 };

    treeNode* pRoot = NULL;
    pRoot = createNode(begPos.row, begPos.col);
    pathMap[begPos.row][begPos.col] = true;
    vector<treeNode*> buff;

    treeNode* pCurrent = pRoot;
    treeNode* pChild = NULL;
    bool isFindEnd = false;

    vector<treeNode*>::iterator it;
    vector<treeNode*>::iterator itMin;

    while (1){
        for (int i = 0; i < 8; i++){
            pChild = createNode(pCurrent->pos.row, pCurrent->pos.col);
            switch (i){
    case p_up:
        pChild->pos.row--;
        pChild->pos.g += ZXDJ;
        break;
    case p_down:
        pChild->pos.row++;
        pChild->pos.g += ZXDJ;
        break;
    case p_left:
        pChild->pos.col--;
        pChild->pos.g += ZXDJ;
        break;
    case p_right:
        pChild->pos.col++;
        pChild->pos.g += ZXDJ;
        break;
    case p_lup:
        pChild->pos.row--;
        pChild->pos.col--;
        pChild->pos.g += XXDJ;
        break;
    case p_ldown:
        pChild->pos.row++;
        pChild->pos.col--;
        pChild->pos.g += XXDJ;
        break;
    case p_rup:
        pChild->pos.row--;
        pChild->pos.col++;
        pChild->pos.g += XXDJ;
        break;
    case p_rdown:
        pChild->pos.row++;
        pChild->pos.col++;
        pChild->pos.g += XXDJ;
        break;
            }
            if (1 != map[pChild->pos.row][pChild->pos.col] &&
                true != pathMap[pChild->pos.row][pChild->pos.col])
            {
                pChild->pos.h = getH(pChild->pos, endPos);
                pChild->pos.setF();
                pCurrent->child.push_back(pChild);
                pChild->pParent = pCurrent;
                buff.push_back(pChild);
            }
            else{
                // You can safely delete this node if not needed
                delete pChild;
            }
        }

        itMin = buff.begin();
        for (it = buff.begin(); it != buff.end(); it++){
            itMin = (((*it)->pos.f < (*itMin)->pos.f) ? it : itMin);
        }

        pCurrent = *itMin;
        pathMap[pCurrent->pos.row][pCurrent->pos.col] = true;
        buff.erase(itMin);
        if (pCurrent->pos.row == endPos.row && pCurrent->pos.col == endPos.col){
            isFindEnd = true;
            break;
        }
        if (buff.size() == 0){
            break;
        }
    }

    if (isFindEnd){
        printf("Found the end point!\n");
        printf("path:");
        while (pCurrent){
            printf("(%d,%d)", pCurrent->pos.row, pCurrent->pos.col);
            pCurrent = pCurrent->pParent;
        }
        printf("\n");
    }

    return 0;
}

treeNode* createNode(int row, int col){
    treeNode* pNew = new treeNode;
    memset(pNew, 0, sizeof(treeNode));
    pNew->pos.row = row;
    pNew->pos.col = col;
    return pNew;
}

int getH(MyPoint pos, MyPoint endPos){
    int x = abs(pos.col - endPos.col);
    int y = abs(pos.row - endPos.row);
    return ZXDJ*(x + y);
}
