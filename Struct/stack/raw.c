#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point {int row, col;}  stack[512];//申请栈
int top = 0;

void push(struct point p) //压栈
{
  stack[top++] = p;
}

struct point pop(void) //弹出
{
  return stack[top--];
}

int empty(void) //栈底控制
{
  return top == 0;
}

int maze[MAX_ROW][MAX_COL] = { /*地图1是墙，0是路*/
  {0, 1, 1, 1, 1}, 
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 1, 0}, 
  {0, 0, 1, 1, 0},// 5 * 5 为终点
};

void print_maze(void)
{
  int i, j;
  for (i = 0; i < MAX_ROW; i++){
    for (j = 0; j < MAX_COL; j++)
      printf("%d", maze[i][j]);
    putchar('\n');
  }
  printf("*******************\n");
}
struct point predec[MAX_ROW][MAX_COL] = { //定义保存地图的空间
  {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
  {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
  {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
  {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
  {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
};

void visit(int row, int col, struct point pre) //移动细节
{
  struct point visit_point = { row, col };
  maze[row][col] = 2;//标记地图
  predec[row][col] = pre; //保存动作
  push(visit_point);
}

int main (void)
{
  struct point p = { 0, 0 };//初始化点。
  
  maze[p.row][p.col] = 2; //把路过的点 值变为二
  push(p);
  
  while (!empty()){
    p = pop();
    if (p.row < MAX_ROW - 1 && p.col < MAX_COL - 1)//goal
      break;
    if (p.col+1 < MAX_COL && maze[p.row][p.col+1] == 0)//right
      visit(p.row, p.col+1, p);
    if (p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0)//down
      visit(p.row+1, p.col, p);
    if (p.col-1 >= 0 && maze[p.row][p.col-1] == 0)//left
      visit(p.row, p.col-1, p);
    if (p.row-1 >= 0 && maze[p.row-1][p.col] == 0)//up
      visit(p.row-1, p.col, p);
     print_maze();
  }
  if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1){
    printf("(%d, %d)\n", p.row, p.col);
    while (predec[p.row][p.col].row != -1){
      p = predec[p.row][p.col];
      printf("(%d, %d)\n", p.row, p.col);
    }
  }
  else
    printf("NO PATH!\n");
  return 0;
}