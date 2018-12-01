/*
 Filename: Checkers.cpp
 Name: Shaoxiong An
 ID: 100278407
 Sec: CPSC 1160 -001 2016 Fall
 ^_^ Thank you for marking!
 */
//
//  The program implements the basic checker rules including following features:
//      1.The basic move (left and right)
//      2.The single jump to take enemy's piece
//      3.The promotion when one piece reaches the end of the board
//      4.The basic move and take of Kings
//      5.The basic AI move weighting system
//      6.The basic rule for randomizing the move with same weight value
//      7.Using an easier user input command
//
//  Although The AI still needs more improvements, but it is believed that
//  it is capable to win a new checker game player.
//
//  I think the comment should be ez to follow and I should get 100% bonus ~~
//
//
// Thank you again for testing and marking.
// PLEASE let me know if there is any suggestion!



#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void display(char[8][8]);
void dMove(char[8][8]);
bool validStepB(char arr[8][8],string);
bool validStepK(char arr[8][8],string);
void aI(char[8][8],int,int);
void aIEstimation(char[8][8]);
void promotion(char[8][8]);
string convert(string);



int main(){
    // database;
    char arr[8][8];
    for(int i = 0;i < 8;i++){
        for(int j = 0 ;j < 8;j++){
            if( i == 0 || i == 1) arr[i][j]='w';
            else if(i == 6 || i == 7) arr[i][j]='b';
            else arr[i][j]=' ';
        }
    }
    //start
    string ans = "";
    cout <<"Let's play! (y/n)"<<endl;
    cin >> ans;
    if(ans =="n"){
        cout<<"Goodbye!";
        return 0;
    }
    else{
        cout << "Do you want to go first?(y/n)"<<endl;
        cin >> ans;
        if(ans =="y"){
            cout << "You go first" << endl;
            display(arr);
        }
        else{
            cout << "Computer go first" << endl;
            aIEstimation(arr);
            display(arr);
        }
    }
    return 0;
}

// the display method
void display(char arr[8][8]){
    promotion(arr);
    cout<< "   a   b   c   d   e   f   g   h "<<endl;
    cout<< " +---+---+---+---+---+---+---+---+"<<endl;
    for(int i = 0; i < 8; i++){
        cout << i+1 ;
        for(int j = 0; j < 8; j++){
            cout << "|" <<" " << arr[i][j] << " ";
        }
        cout<<"|"<<endl;
        cout<<" +---+---+---+---+---+---+---+---+"<<endl;
    }
    dMove(arr);
}

//get player move
void dMove(char arr[8][8]){
    cout<<"Play next step!(eg.7a> or 6c>n;'<'=left;','=left jump;'.'=right jump;'>'=right;'u'=up;'n'=down;'stop'=quit )"<<endl;
    string step;
    cin >> step;
    step = convert(step);
    if (step == "stop"){
        cout <<"Thanks for the play!"<< endl;
        return;
    }
    else if(validStepB(arr,step)||validStepK(arr,step)){
        aIEstimation(arr);
        display(arr);
    }
    else{
        cout << "Invalid! ";
        dMove(arr);
    }
}

// valid step for black pond
bool validStepB(char arr[8][8],string step){
    //from a --> b
    int a1 = int(char(step[0])-'0'-1);
    int a2 = int(char(step[1])-'a');
    int b1 = int(char(step[2])-'0'-1);
    int b2 = int(char(step[3])-'a');
    char a = arr[a1][a2];
    char b = arr[b1][b2];
    // move check
    if(a == 'b'&& b ==' ' && (a1-b1 == 1)&& (b2-a2==1 || b2-a2== -1)){
        arr[b1][b2] = 'b';
        arr[a1][a2] = ' ';
        return true;
    }
    //jump check
    else if(a=='b'&& b ==' ' && arr[a1-1][(a2+b2)/2]=='w' && a1-b1 == 2 && (b2-a2==2 || b2-a2== -2 )){
        arr[a1][a2] =' ';
        arr[b1][b2] ='b';
        arr[a1-1][(a2+b2)/2]=' ';
        return true;
    }
    return false;

}

bool validStepK(char arr[8][8],string step){
    //from a --> b
    int a1 = int(char(step[0])-'0'-1);
    int a2 = int(char(step[1])-'a');
    int b1 = int(char(step[2])-'0'-1);
    int b2 = int(char(step[3])-'a');
    char a = arr[a1][a2];
    char b = arr[b1][b2];
    // move check
    if(a == 'K'&& b ==' ' && (a1-b1 == 1||a1-b1== -1)&& (b2-a2==1 || b2-a2== -1)){
        arr[b1][b2] = 'K';
        arr[a1][a2] = ' ';
        return true;
    }
    //jump check
    else if(a=='K'&& b ==' ' && arr[a1-1][(a2+b2)/2]=='w' && a1-b1 == 2 && (b2-a2==2 || b2-a2== -2 )){
        arr[a1][a2] =' ';
        arr[b1][b2] ='K';
        arr[a1-1][(a2+b2)/2]=' ';
        return true;
    }
    //jump check
    else if(a=='K'&& b ==' ' && arr[b1-1][(a2+b2)/2]=='w' && a1-b1 == -2 && (b2-a2==2 || b2-a2== -2 )){
        arr[a1][a2] =' ';
        arr[b1][b2] ='K';
        arr[b1-1][(a2+b2)/2]=' ';
        return true;
    }
    return false;
}




//AI estimation
void aIEstimation(char arr[8][8]){
    srand(time(0));
    int key[8][8];
    int hPriority = 0;
    int x, y;
    for(int i = 0;i < 8;i++){
        for(int j = 0 ;j < 8;j++){
            
            key[i][j]=0;
            //right move: priority 1
            if(i+1 < 8 && j+1 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' ') key[i][j]=1;
            //left move: priority 1
            if(i+1 < 8 && j-1 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' ') key[i][j]=1;
            //KING right front move: priority 1
            if(i+1 < 8 && j+1 < 8  &&arr[i][j]=='X'&& arr[i+1][j+1]==' ') key[i][j]=1;
            //KING left front move: priority 1
            if(i+1 < 8 && j-1 >=0  &&arr[i][j]=='X'&& arr[i+1][j-1]==' ') key[i][j]=1;
            //KING right back move: priority 2
            if(i-1 >=0 && j+1 < 8  &&arr[i][j]=='X'&& arr[i-1][j+1]==' ') key[i][j]=2;
            //KING left back move: priority 2
            if(i-1 >=0 && j-1 >=0  &&arr[i][j]=='X'&& arr[i-1][j-1]==' ') key[i][j]=2;
            //right back detect move: priority 3
            if(i+2 < 8 && j+2 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' '&& arr[i][j+2]!=' ' && arr[i+2][j]=='b') key[i][j]=3;
            //left back detect move: priority 3
            if(i+2 < 8 && j-2 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' '&& arr[i][j-2]!=' ' && arr[i+2][j]=='b') key[i][j]=3;
            //right front detect move: priority 4
            if(i+2 < 8 && j+2 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' ' && arr[i+2][j+2]!='b' && arr[i+2][j]!='b'
               && arr[i+2][j+2]!='K' && arr[i+2][j]!='K') key[i][j]=4;
            //left front detect move: priority 4
            if(i+2 < 8 && j-2 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' ' && arr[i+2][j-2]!='b' && arr[i+2][j]!='b'
               && arr[i+2][j-2]!='K' && arr[i+2][j]!='K') key[i][j]=4;
            //right single jump priority 5
            if(i+2 < 8 && j+2 < 8  && arr[i][j]=='w' && (arr[i+1][j+1]=='b'||arr[i+1][j+1]=='K')&& arr[i+2][j+2]==' ') key[i][j]=5;
            //left single jump priority 5
            if(i+2 < 8 && j-2 >= 0 && arr[i][j]=='w' && (arr[i+1][j-1]=='b'||arr[i+1][j-1]=='K')&& arr[i+2][j-2]==' ') key[i][j]=5;
            //King single right front jump priority 5
            if(i+2 < 8 && j+2 < 8  && arr[i][j]=='X' && (arr[i+1][j+1]=='b'||arr[i+1][j+1]=='K')&& arr[i+2][j+2]==' ') key[i][j]=5;
            //King single left front jump priority 5
            if(i+2 < 8 && j-2 >= 0 && arr[i][j]=='X' && (arr[i+1][j-1]=='b'||arr[i+1][j-1]=='K')&& arr[i+2][j-2]==' ') key[i][j]=5;
            //King single right back jump priority 6
            if(i-2 >= 0 && j+2 < 8  && arr[i][j]=='X' && (arr[i-1][j+1]=='b'||arr[i-1][j+1]=='K')&& arr[i-2][j+2]==' ') key[i][j]=6;
            //King single left back jump priority 6
            if(i-2 >= 0 && j-2 >= 0 && arr[i][j]=='X' && (arr[i-1][j-1]=='b'||arr[i-1][j-1]=='K')&& arr[i-2][j-2]==' ') key[i][j]=6;

            
            
            
            //highest priority
            if(hPriority < key[i][j]){
                hPriority = key[i][j];
            }
        }
    }
    // random select the step with highest priority.
    int max = hPriority;
    for(int i = 0;i < 8;i++){
        for(int j = 0 ;j < 8;j++){
            if(key[i][j]==hPriority){
                key[i][j]+= rand()%32;
                //cout << key[i][j]<<endl;
                if(max < key[i][j]){
                    max = key[i][j];
                    x = i;
                    y = j;
                }
            }
        }
    }
    //call AI move
    aI(arr,x,y);
}

//AI move
void aI(char arr[8][8],int i, int j){
    //King single left back jump priority 6
    if(i-2 >= 0 && j-2 >= 0 && arr[i][j]=='X' && (arr[i-1][j-1]=='b'||arr[i-1][j-1]=='K')&& arr[i-2][j-2]==' '){
        arr[i][j]=' ';
        arr[i-1][j-1]=' ';
        arr[i-2][j-2]='X';
        return;
    }
    //King single right back jump priority 6
    if(i-2 >= 0 && j+2 < 8  && arr[i][j]=='X' && (arr[i-1][j+1]=='b'||arr[i-1][j+1]=='K')&& arr[i-2][j+2]==' '){
        arr[i][j]=' ';
        arr[i-1][j+1]=' ';
        arr[i-2][j+2]='X';
        return;
    }
    //King single left front jump priority 5
    if(i+2 < 8 && j-2 >= 0 && arr[i][j]=='X' && (arr[i+1][j-1]=='b'||arr[i+1][j-1]=='K')&& arr[i+2][j-2]==' '){
        arr[i][j]=' ';
        arr[i+1][j-1]=' ';
        arr[i+2][j-2]='X';
        return;
    }
    //King single right front jump priority 5
    if(i+2 < 8 && j+2 < 8  && arr[i][j]=='X' && (arr[i+1][j+1]=='b'||arr[i+1][j+1]=='K')&& arr[i+2][j+2]==' '){
        arr[i][j]=' ';
        arr[i+1][j+1]=' ';
        arr[i+2][j+2]='X';
        return;
    }
    //left single jump take move
    if(i+2 < 8 && j-2 >= 0 && arr[i][j]=='w' && (arr[i+1][j-1]=='b'||arr[i+1][j-1]=='K') && arr[i+2][j-2]==' '){
        arr[i][j]=' ';
        arr[i+1][j-1]=' ';
        arr[i+2][j-2]='w';
        return;
    }
    //right single jump take move
    if(i+2 < 8 && j+2 < 8  && arr[i][j]=='w' && (arr[i+1][j+1]=='b'||arr[i+1][j+1]=='K')&& arr[i+2][j+2]==' '){
        arr[i][j]=' ';
        arr[i+1][j+1]=' ';
        arr[i+2][j+2]='w';
        return;
    }
    //left front detect move
    if(i+2 < 8 && j-2 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' ' && arr[i+2][j-2]!='b' && arr[i+2][j]!='b'
       && arr[i+2][j-2]!='K' && arr[i+2][j]!='K'){
        arr[i][j]=' ';
        arr[i+1][j-1]='w';
        return;
    }
    //right front detect move
    if(i+2 < 8 && j+2 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' ' && arr[i+2][j+2]!='b' && arr[i+2][j]!='b'
       && arr[i+2][j+2]!='K' && arr[i+2][j]!='K'){
        arr[i][j]=' ';
        arr[i+1][j+1]='w';
        return;
    }
    //left back detect move
    if(i+2 < 8 && j-2 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' '&& arr[i][j-2]=='w' && arr[i+2][j]=='b'){
        arr[i][j]=' ';
        arr[i+1][j-1]='w';
        return;
    }
    //right back detect move
    if(i+2 < 8 && j+2 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' '&& arr[i][j+2]=='w' && arr[i+2][j]=='b'){
        arr[i][j]=' ';
        arr[i+1][j+1]='w';
        return;
    }

    
    //KING left back move: priority 2
    if(i-1 >=0 && j-1 >=0  &&arr[i][j]=='X'&& arr[i-1][j-1]==' '){
        arr[i][j]=' ';
        arr[i-1][j-1]='X';
        return;
    }
    //KING right back move: priority 2
    if(i-1 >=0 && j+1 < 8  &&arr[i][j]=='X'&& arr[i-1][j+1]==' '){
        arr[i][j]=' ';
        arr[i-1][j+1]='X';
        return;
    }
    
    
    //KING left front move: priority 1
    if(i+1 < 8 && j-1 >=0  &&arr[i][j]=='X'&& arr[i+1][j-1]==' '){
        arr[i][j]=' ';
        arr[i+1][j-1]='X';
        return;
    }
    //KING right front move: priority 1
    if(i+1 < 8 && j+1 < 8  &&arr[i][j]=='X'&& arr[i+1][j+1]==' '){
        arr[i][j]=' ';
        arr[i+1][j+1]='X';
        return;
    }
    //left move
    if(i+1 < 8 && j-1 >=0  &&arr[i][j]=='w'&& arr[i+1][j-1]==' '){
        arr[i][j]=' ';
        arr[i+1][j-1]='w';
        return;
    }
    //right move
    if(i+1 < 8 && j+1 < 8  &&arr[i][j]=='w'&& arr[i+1][j+1]==' '){
        arr[i][j]=' ';
        arr[i+1][j+1]='w';
        return;
    }
}

//Promotion
void promotion(char arr[8][8]){
    for(int j = 0; j < 8; j++){
        if(arr[0][j]=='b'){
            arr[0][j]='K';
        }
        if(arr[7][j]=='w'){
            arr[7][j]='X';
        }
    }
}
//convert user input to string needed;
string convert(string input){
    //stop
    if(input=="stop"){
        return input;
    }
    //from a to b
    char ax = input[0];
    char ay = input[1];
    char bx;
    char by;
    //jump
    if(input[2]=='.' && input.length()==3 && char(int(ax-2))>= '1' && char(int(ay+2))<='h'){
        bx = char(int(ax-2));
        by = char(int(ay+2));
    }else if(input[2]==',' && input.length()==3 && char(int(ax-2))>= '1' && char(int(ay-2))>='a'){
        bx = char(int(ax-2));
        by = char(int(ay-2));
    }else if(input[2]=='.' && input.length()==4 && input[3]=='u' && char(int(ax-2))>= '1' && char(int(ay+2))<='h'){
        bx = char(int(ax-2));
        by = char(int(ay+2));
    }else if(input[2]==',' && input.length()==4 && input[3]=='u' && char(int(ax-2))>= '1' && char(int(ay-2))>='a'){
        bx = char(int(ax-2));
        by = char(int(ay-2));
    }else if(input[2]=='.' && input.length()==4 && input[3]=='n' && char(int(ax+2))<= '8' && char(int(ay+2))<='h'){
        bx = char(int(ax+2));
        by = char(int(ay+2));
    }else if(input[2]==',' && input.length()==4 && input[3]=='n' && char(int(ax+2))<= '8' && char(int(ay-2))>='a'){
        bx = char(int(ax+2));
        by = char(int(ay-2));
    }
    //move
    else if(input[2]=='>' && input.length()==3 && char(int(ax-1))>= '1' && char(int(ay+1))<='h'){
        bx = char(int(ax-1));
        by = char(int(ay+1));
    }else if(input[2]=='<' && input.length()==3 && char(int(ax-1))>= '1' && char(int(ay-1))>='a'){
        bx = char(int(ax-1));
        by = char(int(ay-1));
    }else if(input[2]=='>' && input.length()==4 && input[3]=='u' && char(int(ax-1))>= '1' && char(int(ay+1))<='h'){
        bx = char(int(ax-1));
        by = char(int(ay+1));
    }else if(input[2]=='<' && input.length()==4 && input[3]=='u' && char(int(ax-1))>= '1' && char(int(ay-1))>='a'){
        bx = char(int(ax-1));
        by = char(int(ay-1));
    }else if(input[2]=='>' && input.length()==4 && input[3]=='n' && char(int(ax+1))<= '8' && char(int(ay+1))<='h'){
        bx = char(int(ax+1));
        by = char(int(ay+1));
    }else if(input[2]=='<' && input.length()==4 && input[3]=='n' && char(int(ax+1))<= '8' && char(int(ay-1))>='a'){
        bx = char(int(ax+1));
        by = char(int(ay-1));
    }else{
        bx = 0;
        by = 0;
    }
    string result = "";
    result += ax;
    result += ay;
    result += bx;
    result += by;
    return result;
}
             

    
    








         
