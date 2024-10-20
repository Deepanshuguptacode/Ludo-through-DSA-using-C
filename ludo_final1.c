#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

//TO print the board


//To print empty or home boxes
void print_empbox(char at[30],int i){
        printf("         %c        ",at[i]);   
}
//To print the middle box or winner box
void print_mid_empbox(char at[30],int i){
        printf("%c WIN  %c",at[i],at[i+1]);   
}
//To print frist index box((5-i)for indexing decreasing values in 1st col to 0-5 )
//((i+6)&(i+12) are for indexing increasing values in 2nd &3rd column to 6-11 or 11-17)
void print_ver_indbox(char at[72],int i){
    printf("|%c |%c |%c |",at[(5-i)],at[i+6],at[i+12]);   
}
//To print the last index box((53-i) (47-i)for index decreasing in 1st & 2nd col to 53-48 & 47-42 )
//((5-i)for indexing increasing values in 3rd col to 36-41)
void print_ver_last_indbox(char at[72],int i){
    printf("|%c |%c |%c |",at[53-i],at[47-i],at[i+36]);   
}

//To print the middle index boxes in horizoltal order

//This is for printing the indexing incresing values of 1st & 2nd column of 2nd box and 1st col of 3rd box
//1st & 2nd col of 2nd boxes indexing are 66-71 & 60-65
//1st col of 3rd boxes indexing are 18-23
void print_hor_inc_indbox(char at[72],int i){
    for(int j=0;j<6;j++){
        printf("|%c ",at[i+j]);
        }
        printf("|");
}
//This is for printing the indexing decresing values of 2nd & 3rd column of 3rd box and 3rt col of 2nd box
//2nd col of 2rd boxes indexing are 59-54
//2nd & 3rd col of 3rd boxes indexing are 29-24 & 35-30
void print_hor_dec_indbox(char at[72],int i){
    for(int j=0;j<6;j++){
        printf("|%c ",at[i-j]);
        }
        printf("|");
}

//To print line and spaces
void print_long_line(){
    printf("-------------------");
}
void print_short_line(){
    printf("--------");
}
void print_short_blank_line(){
    printf("        ");
}
void print_long_blank_line(){
    printf("|                 |");
}

void print_board(char box_at[72],char empty_box[72]){
        printf("\n");print_long_line();print_short_line();print_long_line();printf("\n");
        //for 1st index box
        for(int i=0;i<6;i++){
            print_empbox(empty_box,i);print_ver_indbox(box_at,i);print_empbox(empty_box,i+6);
            //to reduce it to five times because we already print one line above
            if(i+1<6){
                printf("\n");print_long_blank_line();print_short_line();print_long_blank_line();printf("\n");}
        }
            //to print 2nd box 
            printf("\n");print_long_line();print_short_line();print_long_line();printf("\n");
            print_hor_inc_indbox(box_at,66);print_mid_empbox(empty_box,12);print_hor_inc_indbox(box_at,18);//for 1st col
            
            printf("\n");print_long_line();print_short_blank_line();print_long_line();printf("\n");
            print_hor_inc_indbox(box_at,60);print_mid_empbox(empty_box,14);print_hor_dec_indbox(box_at,29);//for 2nd col

            printf("\n");print_long_line();print_short_blank_line();print_long_line();printf("\n");
            print_hor_dec_indbox(box_at,59);print_mid_empbox(empty_box,16);print_hor_dec_indbox(box_at,35);// fo 3rd col


            printf("\n");print_long_line();print_short_line();print_long_line();printf("\n");
            //to print last index box
        for(int i=0;i<6;i++){
            print_empbox(empty_box,i+18);print_ver_last_indbox(box_at,i);print_empbox(empty_box,i+24);
            if(i+1<6){
            printf("\n");print_long_blank_line();print_short_line();print_long_blank_line();printf("\n");}
        }
        printf("\n");print_long_line();print_short_line();print_long_line();printf("\n");   
}

// to roll the dice
void dice(int *n){
    srand(time(NULL));
    *n= abs(((rand()%10)-3));
    if(*n==0)
        *n=6;
}
//for opening
void openn(int n,int player,int *p,char empty_box[30],char box_at[72]){
    if(n==1 || n==6){
        if(player==1){
            empty_box[6]=' ';
            box_at[13]='@';
            *p=13;//p is for position
        }
        else{
            empty_box[18]=' ';
            box_at[49]='#';
            *p=49;//p is for position
        }
    }
}
// for running th game
void run_game(char box_at[72],int n,int *p,int player){
    //postion is assign to k for further easy calculation
    int k=*p;
    //this is for rewriting R and S
    if(k==13 || k==31 || k==49 || k==67){
        box_at[k]='S';
    }
    else if(k==3 || k==21 || k==39 || k==57){
        box_at[k]='R';
    }
    else
        box_at[k]=' ';
    
    k=k+n;
    if(player==1){
        //for skiping middle columns except winning coloumn
        if( k>24 && k<30 || k>42 && k<48 || k>60 && k<66)
            k=k+5;
            //for restaring the poston to 0
            if(k>71)
                k=k-72;
            if(k-n<11){
                if(k>11)
                    k=k-n;
            }
            box_at[k]='@';
    }
    else{
        //for skiping middle columns except winning coloumn
        if(k>6 && k<12 || k>24 && k<30 || k>60 && k<66)
            k=k+5;
            //for restaring the poston to 0
            if(k>71)
                k=k-72;
            if(k-n<47 && k-n>40){
                if(k>47)
                    k=k-n;
            }
            box_at[k]='#';
    }
    //returing k to postion
    *p=k;
}
// for beating 
void beating(char empty_box[30],int p[4],int player){
    //for saving in rest and start place
    if(p[player]!=3 || p[player]!=13 || p[player]!=21 || p[player]!=31 || p[player]!=39 || p[player]!=49 || p[player]!=57 || p[player]!=67){
        // if equal then beat the put frist one in home
        if(p[1]==p[3]){
            if(player==1){ //if player 2 aldready present their so player 2 should get beat
                empty_box[18]='#'; //for sending player 2 to home
                p[3]=0; //for resting the postion to 0
            }
            else{
                empty_box[6]='@';
                p[1]=0;
            }
        }
    }
}
    int main(){
        int i;
        char box_at[72];
        char empty_box[30];
        //intialsing the index box
        for(i=0;i<72;i++){
            box_at[i]=' ';
        }
        //for rest and start boxes
        box_at[13]=box_at[31]=box_at[67]=box_at[49]='S';
        box_at[3]=box_at[21]=box_at[57]=box_at[39]='R';
        //intialsing the empty box
        for(i=0;i<30;i++){
            empty_box[i]=' ';
        }
        //for home boxes 
        empty_box[6]=empty_box[7]=empty_box[10]=empty_box[11]='@';
        empty_box[18]=empty_box[19]=empty_box[22]=empty_box[23]='#';
        print_board(box_at,empty_box);

        //for intializing player and position of player 
        int player=1;
        int p[4]={0,0,0,0};
        while(1){
            int t=0,d;
            //printing which player has turn
            if(player==1){
                printf("Player @\n");
            }
            else{
                printf("Player #\n");
            }

            //dice the number
            printf("Enter any number to Roll Dice\n");
            //scanf is just for stop
            scanf("%d",&t);
            //just for rolling animation
            for(int i=0;i<10;i++){
                print_board(box_at,empty_box);
                printf("rolling the dice..... \n%d",i);
                sleep(0.4);
                system("cls");
            }
            for(int i=0;i<10;i++){
                print_board(box_at,empty_box);
                printf("rolling the dice..... \n%d",i);
                sleep(0.8);
                system("cls");
            }
            dice(&d);//dice function 
            if(empty_box[player*6]==' '){
                run_game(box_at,d,&p[player],player);
                beating(empty_box,p,player);
                //to clear the screen and reprinting the updated board
                system("cls");
                print_board(box_at,empty_box);
                //to print the dice number
                printf("Dice Rolled .....%d\n",d);
                if(box_at[11]=='@' || p[player]==47){
                    for(int i=0;i<5;i++){
                        sleep(3);
                        printf("\t\tWINNER PLAYER %d WINNER",player);
                    }
                    break;
                }
            }
            else{
                openn(d,player,&p[player],empty_box,box_at);
                //to clear the screen and reprinting the updated board
                system("cls");
                print_board(box_at,empty_box);
                //to print the dice number
                printf("Dice Rolled .....%d\n",d);
            }
            if(d==6){
                continue;
            }
            //switching the player
            (player==1) ? (player=3):(player=1);
        }
    return 0;
}