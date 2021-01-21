#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
/* Include other headers as needed */
char board[30][30]={' '};  // Initialisation of board
struct node{
    int x,y;
    char val;
    struct node *next;
};
struct node *head=0,*temp=0,*newNode=0;
char check='a';
void createBorders();                // To show Game Board before Start               
void createNode();                   // To create Body of Snake intially
void createSnakeBody();              // Creates Snake Body with head + 5 nodes
void printInitial();                 // Static view before Start
void createFood();                   // Creates food object randomly on board
void collision();                    // Checks if Snake collides with itself
void addNewNode();                   // If snake eats food then new node is added
void moveRemainingBody();            // moves remaining body acc to head movement 
void movement();                     // mainly handles head movement
void moveSnake();                    // Directions to Snake
/********/
int main()
{
    createBorders();
    createSnakeBody(); //Initially creates body of 5 nodes+1 head
    createFood();      //Creates Food at 15,10 
    printInitial();
    movement();
    return 0;
}
/********/

void createBorders(){
    for(int i=0;i<30;i++){    //Print The Borders of Board
        for(int j=0;j<30;j++){
            if(i==0 || i==29 || j==0 || j==29)board[i][j]='*';
        }
    }
}


void createNode(){
    newNode= (struct node *)malloc(sizeof(struct node));
if(head==0){
    head=temp=newNode;
}else{
    temp->next=newNode;
    temp=newNode;
}
}
void createSnakeBody(){
    createNode();
    temp->x=5;
    temp->y=10;
    temp->val='@';
    board[head->x][head->y]=head->val;
    int c=5;
    while(c>0){
        int xt=temp->x;
        int yt=temp->y + 1;
        createNode();
        newNode->x=xt;
        newNode->y=yt;
        newNode->val='o';
        board[temp->x][temp->y]=temp->val;
        c--;
    }
    
}
void printInitial(){
    
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(board[i][j]=='*' ||board[i][j]=='@' || board[i][j]=='o')printf("%c ",board[i][j]);
            else printf("  ");
        }printf("\n");
    }
}

void createFood(){
    struct node *food=0;
    food=(struct node *)malloc(sizeof(struct node));
    do{
        food->x = (rand() % 28) + 1; //rand(1,28);//food->x=20;
        food->y = (rand() % 28) + 1; //rand(1,28);//15;
    }while(board[food->x][food->y]=='@' || board[food->x][food->y]=='o');
    food->val='*';
    board[food->x][food->y]=food->val;
}

void moveRemainingBody(int x2,int y2){
    while(newNode!=0){
        
        int t1 = newNode->x;
        newNode->x=x2;
        x2=t1;
        t1=newNode->y;
        newNode->y=y2;
        y2=t1;
        board[newNode->x][newNode->y]=newNode->val;
        newNode=newNode->next;
    } board[x2][y2]=' ';
}
void addNewNode(){
    struct node * t;
    t=(struct node *)malloc(sizeof(struct node));
    t->next=head->next;
    t->x=head->x;
    t->y=head->y;
    t->val='o';
    head->next=t;
    createFood();
}
void collision(){
    system("clear");
    //createBorders();
    board[15][10]='G';
    board[15][11]='A';
    board[15][12]='M';
    board[15][13]='E';
    board[15][14]=' ';
    board[15][15]='O';
    board[15][16]='V';
    board[15][17]='E';
    board[15][18]='R';
    
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(board[i][j]=='*' || board[i][j]>=65 && board[i][j]<=90)printf("%c ",board[i][j]);
            else printf("  ");
        }printf("\n");
    }
        exit(0);
}
void moveSnake(int x1,int y1){
    if(x1==0 && y1==0)return;
    int flag=0;
    int x2= head->x;
    int y2= head->y;
    if(head->x + x1 == 0)head->x = 28;
    else if(head->x + x1 == 29)head->x=1;
    else if(board[head->x + x1][head->y] == '*'){
        addNewNode(); flag=1;
        head->x+=x1;
    }
    else head->x+=x1;
    
    if(head->y + y1 == 0)head->y = 28;
    else if(head->y + y1 == 29)head->y=1;
    else if(board[head->x][head->y+y1] == '*' && flag==0){
        addNewNode();
        head->y+=y1;
    }
    else if(board[head->x][head->y+y1] == 'o'){
       collision(); 
    }
    else head->y+=y1;
    
    board[head->x][head->y]=head->val;
    
    newNode=head->next;
    moveRemainingBody(x2,y2);
        system("clear");
        printf(" "); 
         
    printInitial();
}
void movement(){
    printf("Press A for left D for right W for up and S for down\n");
    char ch;
    int flag=0;
    
    while(1){
        char left='a',right='d',up='w',down='s';
       static  int x=0;
       static  int y=0;
         struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
            if( poll(&mypoll, 1, 300) )
    {
        scanf(" %c", &ch); 
    }
    else
    {
        usleep(100000);
        moveSnake(x,y);
    }
        if(ch==left){
         if(check==right){
            continue;
         }
             else{ 
                 check=left;
            x=0; y=-1;
               
            }
        }
        else if(ch==right){
             if(check==left){}
            else{
                 check=right;
                x=0; y=1;  
            }
        }
        else if(ch==up){
             if(check==down){}
             else{
                 check=up;
               x=-1; y=0;  
             }
        }
        else if(ch==down){
            if(check==up){}
             else{
                 check=down;
              x=1; y=0;  
             }
        }
        moveSnake(x,y);
          }
}
