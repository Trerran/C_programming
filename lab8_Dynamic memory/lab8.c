#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <string.h>
#include <termios.h>
#define WIDTH 35
#define HEIGHT 15

void set_game_mode(int enable){
    struct termios my_settings;
    tcgetattr(STDIN_FILENO,&my_settings);
    if (enable){
        my_settings.c_lflag|=ECHO;
        my_settings.c_lflag|=ICANON;
    }
    else{
        my_settings.c_lflag&=~ECHO;
        my_settings.c_lflag&=~ICANON;
        my_settings.c_cc[VMIN] = 0;
        my_settings.c_cc[VTIME] = 0;
    }
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&my_settings);
}

char* combine_field(char direction,char* field, int* snake,int len){
    int tmp_pos1=0;
    int tmp_pos2=0;
    if (direction=='r'){
        for (int i=0;i<len;i++){
            if (i==0){
                tmp_pos1=snake[0];
                snake[0]+=1;
            }
            else{
                tmp_pos2=snake[i];
                snake[i]=tmp_pos1;
                tmp_pos1=tmp_pos2;
            }
            if (i==0 && field[snake[i]]!='|'){
                field[snake[i]]='#';
            }
            else if (i==0 && field[snake[i]]=='|'){
                return NULL;
            }
            else if (field[snake[i]]=='#'){
                return NULL;
            }
            else{
                field[snake[i]]='o';
            }
        }
    }
    if (direction=='l'){
        for (int i=0;i<len;i++){
            if (i==0){
                tmp_pos1=snake[0];
                snake[0]-=1;
            }
            else{
                tmp_pos2=snake[i];
                snake[i]=tmp_pos1;
                tmp_pos1=tmp_pos2;
            }
            if (i==0 && field[snake[i]]!='|'){
                field[snake[i]]='#';
            }
            else if (i==0 && field[snake[i]]=='|'){
                return NULL;
            }
            else if (field[snake[i]]=='#'){
                return NULL;
            }
            else{
                field[snake[i]]='o';
            }
        }
    }
    if (direction=='u'){
        for (int i=0;i<len;i++){
            if (i==0){
                tmp_pos1=snake[0];
                snake[0]-=WIDTH;
            }
            else{
                tmp_pos2=snake[i];
                snake[i]=tmp_pos1;
                tmp_pos1=tmp_pos2;
            }
            if (i==0 && field[snake[i]]!='-'){
                field[snake[i]]='#';
            }
            else if (i==0 && field[snake[i]]=='-'){
                return NULL;
            }
            else if (field[snake[i]]=='#'){
                return NULL;
            }
            else{
                field[snake[i]]='o';
            }
        }
    }
    if (direction=='d'){
        for (int i=0;i<len;i++){
            if (i==0){
                tmp_pos1=snake[0];
                snake[0]+=WIDTH;
            }
            else{
                tmp_pos2=snake[i];
                snake[i]=tmp_pos1;
                tmp_pos1=tmp_pos2;
            }
            if (i==0 && field[snake[i]]!='-'){
                field[snake[i]]='#';
            }
            else if (i==0 && field[snake[i]]=='-'){
                return NULL;
            }
            else if (field[snake[i]]=='#'){
                return NULL;
            }
            else{
                field[snake[i]]='o';
            }
        }
    }
    return field;
}

void clear_field(char* field,int* snake, int len){
    for (int i=0;i<len;i++){
        field[snake[i]]=' ';
    }
}

char change_direction(char direction,char tmp_direction){
    if ((tmp_direction=='w' || tmp_direction=='W') && direction!='d'){
        direction='u';
    }
    else if((tmp_direction=='a' || tmp_direction=='A') && direction!='r'){
        direction='l';
    }
    else if((tmp_direction=='s' || tmp_direction=='S') && direction!='u'){
        direction='d';
    }
    else if((tmp_direction=='d' || tmp_direction=='D') && direction!='l'){
        direction='r';
    }
    return direction;
}

int spawn_apples(char* game){
    int* random_nums=calloc(HEIGHT*WIDTH,sizeof(int));
    int ind=0;
    int apple=-1;
    for (int i=0;i<HEIGHT*WIDTH;i++){
        if (game[i]==' '){
            random_nums[ind]=i;
            ind+=1;
        }
    }
    if (ind==0){
        free(random_nums);
        return -1;
    }
    apple=random_nums[rand()%ind];
    free(random_nums);
    return apple;
}

int speed(int score){
    int speed=250000;
    if (score<3){
        speed=250000;
    }
    else if (score>=3 && score<=6){
        speed-=50000;
    }
    else if(score>6 && score<11){
        speed-=100000;
    }
    else{
        speed-=150000;
    }
    return speed;
}

int main(){
    char *field=calloc(HEIGHT*WIDTH,sizeof(char));  
    if (field==NULL){
        return 1;
    }
    for (int i=0;i<HEIGHT;i++){
        for (int j=0;j<WIDTH;j++){
            if ((j==0 && i==0) || (j==WIDTH-1 && i==0) || (j==0 && i==HEIGHT-1) || ((j==WIDTH-1 && i==HEIGHT-1))){
                field[i*WIDTH+j]='+';
            }
            else if (i==0 || i==HEIGHT-1){
                field[i*WIDTH+j]='-';
            }
            else if (j==0 || j==WIDTH-1){
                field[i*WIDTH+j]='|';
            }
            else{
                field[i*WIDTH+j]=' ';
            }
        }
    }
    srand(time(NULL));
    int* snake=calloc(4,sizeof(int));
    int tmp=(HEIGHT / 2) * WIDTH + (WIDTH / 2);
    for (int i=0;i<4;i++){
        snake[i]=tmp;
        tmp-=1;
    }
    int len=4;
    char direction='r';
    int time_sleep=250000;
    char* previous_game=malloc(WIDTH*HEIGHT*sizeof(char));
    int score=0;
    int apple=-1;
    char tmp_direction;
    set_game_mode(0);
    while (1){ 
        if (read(STDIN_FILENO,&tmp_direction,1)==1){
            direction=change_direction(direction,tmp_direction);
        }
        char* game=combine_field(direction,field,snake,len);
        if (game!=NULL){
            if (apple==snake[0]){
                len+=1;
                int* tmp_snake=realloc(snake,len*sizeof(int));
                if (tmp_snake!=NULL){
                    snake=tmp_snake;
                    snake[len-1]=snake[len-2];
                }
                apple=-1;
                score+=1;
                time_sleep=speed(score);
                if(len==(HEIGHT-2)*(WIDTH-2)){
                for (int i=0;i<HEIGHT;i++){
                    for (int j=0;j<WIDTH;j++){
                        printf("%c",game[i*WIDTH+j]);
                    }
                    printf("\n");
                }
                printf("YOU WIN!\n");
                printf("SCORE: %d\n",score);
                break;
                }
            }
            if (apple==-1){
                apple=spawn_apples(game);       
            }
            if (apple!=-1){
                game[apple]='*';
            }
            for (int i=0;i<HEIGHT;i++){
                for (int j=0;j<WIDTH;j++){
                    printf("%c",game[i*WIDTH+j]);
                }
                printf("\n");
            }
            printf("SCORE: %d\n",score);
        }
        else{
            for (int i=0;i<HEIGHT;i++){
                for (int j=0;j<WIDTH;j++){
                    printf("%c",previous_game[i*WIDTH+j]);
                }
                printf("\n");
            }
            printf("YOU LOSE!\n");
            printf("SCORE: %d\n",score);
            break;
        }
        memcpy(previous_game,game,WIDTH*HEIGHT);
        clear_field(field,snake,len);
        usleep(time_sleep);
        printf("\033[H\033[J");
    }
    set_game_mode(1);
    free(snake);
    free(previous_game);
    free(field);
    return 0;
}