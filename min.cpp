#include "clui.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <windows.h>
using namespace std;
char** save_usernames=new char*[1000];
int* save_scores=new int[1000];
char board[20][20][2];
int direction[4][2]={{0,+1},{0,-1},{+1,0},{-1,0}};
int count_flag =0;//shomarande flag
int count_total=0;//baraye bordo bakht
int count_save=0;//baraye saveha
int count_users=0;
char username[50];
void select_list();
void print_list();
void check_for_score(int bomb)
{
    bool flag= false;
    for(int i=0; i <1000 ; i++)
    {
        if(strcmp(username,save_usernames[i])==0 && save_scores[i]!=0)
        {
            save_scores[i]+=bomb;
            flag = true;
            break;
        }
    }
    if(flag==false)
    {
        strcpy(save_usernames[count_users],username);
        save_scores[count_users]=bomb;
        count_users++;
    }
}
int length(string word)
{
    int i=0;
    while(word[i] != '\0')
    {
        i++;
    }
    return i;
}
void string_copy(string save_board) 
{
    int size=length(save_board);
    for(int i=0; i<size; i++)
    {
        username[i]=save_board[i];
    }
    username[size]='\0';
}
void copy_users(string line,int j) 
{
    int size=length(line);
    for(int i=0; i<size; i++)
    {
        save_usernames[j][i]=line[i];
    }
    save_usernames[j][size]='\0';
}
void rest_user_score()
{
    for(int i=0; i<1000; i++)
    {
        save_scores[i]=0;
    }

}
void load_save_list()
{
    fstream file;
    file.open("save.txt",ios::in);
    if(file.is_open())
    {
        clear_screen();
        string line;
        while(getline(file,line))
        {
            if(line[0]=='.')
            {
                int selected =0,i=1;
                while(line[i]!='\0')
                {
                    selected=(selected*10)+(line[i]-'0');
                    i++;
                }
                cout << selected << "  :  ";
                getline(file,line);
                cout << line << endl;
            }
        }
        file.close();
    }
    cout << "\nEnter the number or -1 to delet :\n";
}
void load_user_list()
{
    fstream file;
    file.open("save_usernames.txt",ios::in);
    if(file.is_open())
    {
        string line;
        int i=0,j=0;
        while(getline(file,line))
        {
            if(save_scores[i]>0)
            {
                copy_users(line,j);
                j++;
            }
            i++;
        }
        file.close();
    }
}
void load_scores()
{
   fstream file;
    file.open("save_score.txt",ios::in);
    if(file.is_open())
    {
        string line;
        int j=0;
        while(getline(file,line) && j !=1000)
        {
            int size=length(line);
            for(int i=0; i<size; i++)
            {
                save_scores[j]=(save_scores[j]*10)+(line[i]-'0');
            }
            j++;
        }
        file.close();
    } 
}
void save_leaderboard()
{
   fstream file;
    file.open("save_usernames.txt",ios::out);
    if(file.is_open())
    {
        for(int i = 0; i <1000 ; i++)
        {
            if(save_scores[i]>0)
            {
                file << save_usernames[i] << endl;
            }
        }
        file.close();
    } 
    file.open("save_score.txt",ios::out);
    if(file.is_open())
    {
        for(int i = 0; i <1000 ; i++)
        {
            if(save_scores[i]>0)
            {
                file << save_scores[i] << endl;
            }
        }
        file.close();
    }
}
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void load_game(int* N,int* bomb,int selected_save)
{
    if(selected_save==-1)
    {
        *N = 0;
      fstream file;
      file.open("save.txt",ios::out);
      if(file.is_open())
      {
          file.close();
      }  
      file.open("counter.txt",ios::out);
      if(file.is_open())
      {
          file.close();
      } 
      count_save=0;
    }
    else
    {
        fstream file;
        file.open("save.txt",ios::in);
        if(file.is_open())
        {
            clear_screen();
            cout << "\n\n\n\n\t\tpleas waite...\n";
            string line;
            bool flag = false;
            while(getline(file,line))
            {
                if(line[0]=='.')
                {
                    int selected =0,i=1;
                    while(line[i]!='\0')
                    {
                        selected=(selected*10)+(line[i]-'0');
                        i++;
                    }
                    if(selected==selected_save)
                    {
                        flag = true;
                    }
                }else;
                if(flag && getline(file,line))
                {
                    string_copy(line);
                    file >> *N;
                    file >> *bomb;
                    file >> count_flag;
                    file >> count_total;
                    for(int i=0; i< *N; i++)
                    {
                        for(int j=0; j< *N; j++)
                        {
                            file >> board[i][j][1];
                            file >> board[i][j][0];
                        }
                    }
                    break;
                }
            }
            file.close();
        }
    }
}
void save_game(int N , int bomb)
{
    fstream file;
    file.open("save.txt",ios::app);
    if(file.is_open())
    {
        count_save++;
        file << "." << count_save << endl;
        file << username << endl;
        file << N << endl;
        file << bomb << endl;
        file << count_flag << endl;
        file << count_total << endl;
        for(int i=0; i < N; i++)
        {
            for(int j=0; j < N; j++)
            {
                file << board[i][j][1] << endl;
                file << board[i][j][0] << endl;
            }
        }
        file.close();
    }
    
}
int check_board(char save_board[20][20][2],int N,int total)
{
    if(count_total==total)
    return 1;
    else
    return 0;
}
int select_and_flag(char selected , int row_col[2] ,char save_board[20][20][2],int bomb,int N)
{
    if(selected == 'f' && board[row_col[0]][row_col[1]][1] != '0' && board[row_col[0]][row_col[1]][1] != '1' && board[row_col[0]][row_col[1]][1] != '2' && board[row_col[0]][row_col[1]][1] != '3' && board[row_col[0]][row_col[1]][1] != '4' && board[row_col[0]][row_col[1]][1] != '5' && board[row_col[0]][row_col[1]][1] != '6' && board[row_col[0]][row_col[1]][1] != '7' && board[row_col[0]][row_col[1]][1] != '8')
    {
        if( board[row_col[0]][row_col[1]][1] == '!')
        {
            count_flag--;
            board[row_col[0]][row_col[1]][1] = 254;
        }
        else if(count_flag != bomb)
        {
            count_flag++;
            board[row_col[0]][row_col[1]][1]= '!';
        }
        return 0;
    }
    else if(selected == ' ')
    {
        count_total++;
        if(save_board[row_col[0]][row_col[1]][0] == '*')
            return 1;
        else if(save_board[row_col[0]][row_col[1]][0] != '*' &&  save_board[row_col[0]][row_col[1]][1] != '!')
        {
            board[row_col[0]][row_col[1]][1] =save_board[row_col[0]][row_col[1]][0];
            return 0;
        }
        else if(save_board[row_col[0]][row_col[1]][0] != '*' &&  save_board[row_col[0]][row_col[1]][1] == '!')
        {
            board[row_col[0]][row_col[1]][1] =save_board[row_col[0]][row_col[1]][0];
            count_flag--;
            return 0;
        }
    }
    else if(selected == 'q')
    {
        print_list();
        select_list();
    }
    else if(selected == 'o')
    {
        save_game(N , bomb);
        print_list();
        select_list();
    }
    return 0;
}
int change_direction(char selected , int row_col[2] ,char save_board[20][20][2],int N)
{
    if(selected == 'w')
    {
        if(row_col[0]-1 >= 0 )
        {
            row_col[0]--;
        }
        return 0;
    }
    else if(selected == 's')
    {
        if(row_col[0]+1 < N )
        {
            row_col[0]++;
        }
        return 0;
    }
    else if(selected == 'd')
    {
        if(row_col[1]+1 < N )
        {
            row_col[1]++;
        }
        return 0;
    }
    else if(selected == 'a')
    {
        if(row_col[1]-1 >= 0 )
        {
            row_col[1]--;
        }
        return 0;
    }
    return 0;
}
int do_select_action(char selected , int row_col[2] , char save_board[20][20][2],int N,int bomb)
{
    int result = 0;
    result = select_and_flag(selected ,  row_col ,  save_board ,bomb,N);
    if(result == 1)
        return 1;
    change_direction( selected ,  row_col , save_board, N); 
    return 0;
}
void fill_with_number(char save_board[20][20][2],int N)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(save_board[i][j][0] == '*')
            {
                if(i-1 >= 0)
                {
                    if(j-1 >= 0 && save_board[i-1][j-1][0] != '*')
                        save_board[i-1][j-1][0]++;else;
                    if(j+1 < N && save_board[i-1][j+1][0] != '*')
                        save_board[i-1][j+1][0]++;else;
                    if(save_board[i-1][j] [0] != '*')
                        save_board[i-1][j][0]++;
                }else;
                if(i+1 < N )
                {
                    if(j-1 >= 0 && save_board[i+1][j-1][0] != '*')
                        save_board[i+1][j-1][0]++;else;
                    if(j+1 < N && save_board[i+1][j+1][0] != '*' )
                        save_board[i+1][j+1][0]++;else;
                    if(save_board[i+1][j][0] != '*')
                        save_board[i+1][j][0]++;
                }
                    if(j-1 >= 0 && save_board[i][j-1][0] != '*')
                        save_board[i][j-1][0]++;else;
                    if(j+1 < N && save_board[i][j+1][0] != '*')
                        save_board[i][j+1][0]++;else;
            }
        }
    }
}
void put_bomb(char save_board[20][20][2],int N,int bomb)
{
    int count=0;
    while(count!=bomb)
    {
        int row=rand()%N;
        int col=rand()%N;
        if(save_board[row][col][0]=='0')
        {
            save_board[row][col][0]='*';
            count++;
        }
    }
}
void reset_board(int N,int bomb)
{
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            board[i][j][1] =254;
            board[i][j][0] ='0';
        }
    }
    put_bomb(board,N,bomb);
    fill_with_number(board,N);
}
void print_board(int select_x , int select_y ,int N)
{
    change_color_rgb(252,186,3);
    printf("use 'w','s','d','a' for going up,down,right,left\n");
    printf("use space,'f','o','q' for select , putting flag(!) , save and quit\n");
    reset_color();
    for(int i=0; i<N; i++)
    {
        gotoxy(0,i+4);
        for(int j=0; j<N; j++)
        {
            gotoxy(2*j,i+4);
            if(select_x==i && select_y==j)
            {
                change_color_rgb(61,252,3);
                printf("%c ",board[i][j][1]);
                reset_color();
            }
            else if(board[i][j][1]=='!')
            {
                change_color_rgb(240,22,94);
                printf("%c ",board[i][j][1]);
                reset_color();
            }
            else
            {
                if(board[i][j][1]=='1')
                {
                    change_color_rgb(15,235,255); 
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='2')
                {
                    change_color_rgb(15,107,255);
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='3')
                {
                    change_color_rgb(255,247,15);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='4')
                {
                    change_color_rgb(255,143,15);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='5')
                {
                    change_color_rgb(255,15,251);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='6')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='7')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='8')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else
                    printf("%c ",board[i][j][1]);
            }
                
        }
    }
}
void print_finished_board(char save_board[20][20][2],int N)
{
    for(int i=0; i<N; i++)
    {
        gotoxy(0,i+4);
        for(int j=0; j<N; j++)
        {
            if(save_board[i][j][0] == '*')
            board[i][j][1] = '*';
            else
            board[i][j][1] = save_board[i][j][0];
            if(board[i][j][1]=='*')
            {
                change_color_rgb(240,22,94);
                printf("%c ",board[i][j][1]);
                reset_color();
            }
            else
            {
                if(board[i][j][1]=='1')
                {
                    change_color_rgb(15,235,255); 
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='2')
                {
                    change_color_rgb(15,107,255);
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='3')
                {
                    change_color_rgb(255,247,15);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='4')
                {
                    change_color_rgb(255,143,15);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='5')
                {
                    change_color_rgb(255,15,251);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='6')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='7')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1]=='8')
                {
                    change_color_rgb(171,56,17);                    
                    printf("%c ",board[i][j][1]);  
                    reset_color();
                }
                else if(board[i][j][1] == '0')
                {
                    printf("%c ",board[i][j][1]);
                }
            }
                
        }
    }
}
void print_win(char save_board[20][20][2],int N,int bomb)
{

    clear_screen();
    check_for_score(bomb);
    change_color_rgb(63,255,15);
    printf("\t%c%c Congratulation YOU WIN %c%c\n",(char)3,(char)2,(char)2,(char)3);
    reset_color();
    print_finished_board( save_board,N);
}
void print_explosion(char save_board[20][20][2],int N)
{
    clear_screen();
    change_color_rgb(255,63,15);
    printf("\t Unfortunately YOU LOSE\n");
    reset_color();
    print_finished_board(save_board,N);
}
void print_list()
{
    clear_screen();
    printf("Enter the number :\n1.New Game\n2.Load Game\n3.Change Name\n4.Leaderboard\n5.Quit");
}
void do_new_game(int bomb,int total,int N,bool flag)
{
    if(flag==false)
    {
        clear_screen();
        cout << "Enter the username less than 50 characters:" << endl;
        cin.getline(username,50);
    }
    clear_screen();
    print_board(0,0,N);
    int explosion=0 , row_col[2]={0} , check=0;
    while(explosion==0 && check==0)
    {
        char select=getch();
        explosion=do_select_action(select , row_col,board,N,bomb);
        clear_screen();
        print_board(row_col[0] , row_col[1],N);
        check=check_board(board,N,total);
    }
    if(explosion==0)
        print_win(board,N,bomb);
    else
        print_explosion(board,N);
    printf("\npess any key to continue");
    getch();
    print_list();
    select_list();
}
int tedad()
{
    clear_screen();
    printf("Enter the number : \n1.Easy\n2.Medium\n3.Hard\n4.Your favorite");
    int n=0;
    while(n<=0 || n >4)
    {
        n=getch()-'0';
    }
    return n;
}
void favorite(int* N,int* bomb)
{
    int n,b;
    cout << "\nEnter the size <21 & >4: " << endl;
    while(n>20 || n<5)
    {
        cin >> n;
        if(n>20 || n<5)
            cout << "\nPleas enter the valid size <21 & >4: " << endl;
    }
    cout << "Enter the number of bomb : " << endl;
    cin >> b;
    *N=n;
    *bomb=b;
    clear_screen();
    cout << "Enter the username less than 50 characters:" << endl;
    cin.getline(username,50);
}
void new_game(bool flag)
{
    count_total=0;
    count_flag = 0;
    int N,bomb,total;
    int* n=&N;
    int* b=&bomb;
    int x=tedad();
    switch(x)
    {
        case 1:
        N=5;
        total=21;
        bomb=4;
        reset_board(N,bomb);
        do_new_game(bomb,total,N,flag);
        break;
        case 2:
        N=12;
        total=116;
        bomb=28;
        reset_board(N,bomb);
        do_new_game(bomb,total,N,flag);
        break;
        case 3:
        N=20;
        total=304;
        bomb=96;
        reset_board(N,bomb);
        do_new_game(bomb,total,N,flag);
        break;
        case 4:
        favorite(n,b);
        total=(N*N)-bomb;
        reset_board(N,bomb);
        do_new_game(bomb,total,N,flag);
        break;
    }
}
void play_the_loaded_game()
{
    int N,bomb,total;
    int* n=&N;
    int* b=&bomb;
    int select=-2;
    while(select<-1 || select >count_save)
    cin >> select;
    load_game(n,b,select);
    total=(N*N)-bomb;
    if(N==0)
    {
        clear_screen();
        print_list();
        select_list();
    }
    else
    {
        clear_screen();
        print_board(0,0,N);
        int explosion=0 , row_col[2]={0} , check=0;
        while(explosion==0 && check==0)
        {
            char select=getch();
            explosion=do_select_action(select , row_col,board,N,bomb);
            clear_screen();
            print_board(row_col[0] , row_col[1],N);
            check=check_board(board,N,total);
        }
        if(explosion==0)
            print_win(board,N,bomb);
        else
            print_explosion(board,N);
        printf("\npess any key to continue");
        getch();
        print_list();
        select_list();
    }
}
void change_name()
{
    clear_screen();
    for(int i = 0; i <1000 ; i++)
    {
        if(save_scores[i]>0)
         cout << i << " : " << save_usernames[i] << endl;
    }
    cout << "Enter the number of user or enter -1/-2 to quit/delet :" << endl;
    int input;
    cin >> input;
    if(input == -1)
    {
        print_list();
        select_list();
    }
    else if(input == -2)
    {
        count_users=0;
        rest_user_score();
        fstream file;
        file.open("save_usernames.txt",ios::out);
        if(file.is_open())
        {
            file.close();
        } 
        file.open("save_score.txt",ios::out);
        if(file.is_open())
        {
            file.close();
        }
        file.open("counter.txt",ios::out);
        if(file.is_open())
        {
            file << count_save <<endl;
            file << count_users <<endl;
            file.close();
        }
        print_list();
        select_list();
    }
    else if(input >= 0)
    {
        strcpy(username,save_usernames[input]);
        new_game(true);
    }
}
void leaderboard()
{
    clear_screen();
    for(int i=0; i <1000 ; i++)
    {
        if(save_scores[i]>0)
        {
            cout << save_usernames[i] << " : " << save_scores[i] << endl;
        }
    }
    cout << "press any key to continue" << endl;
    getch();
    print_list();
    select_list();
}
void select_list()
{
    while(true)
    {
        int num_list=getch()-'0';
        if(num_list==1)
        {
            new_game(false);
            break;
        }
        else if(num_list==2)
        {
            load_save_list();
            play_the_loaded_game();
            break;
        }
        else if(num_list==3)
        {
            change_name();
            break;
        }
        else if(num_list==4)
        {
            leaderboard();
            break;
        }
        else if(num_list==5)
        {
            save_leaderboard();
            fstream file;
            file.open("counter.txt",ios::out);
            if(file.is_open())
            {
                file << count_save <<endl;
                file << count_users <<endl;
                file.close();
            }
            for(int i = 0; i <50 ; i++)
                delete[] save_usernames[i];
            delete[] save_usernames;
            delete[] save_scores;
            exit(0);
        }
    }
}
int main()
{
    
    for(int i=0;i<1000;i++)
    {
        save_usernames[i]=new char[50];
    }
    fstream file;
    file.open("counter.txt",ios::in);
    if(file.is_open())
    {
        file >> count_save;
        file >> count_users;
        file.close();
    }
    rest_user_score();
    load_scores();
    load_user_list();
    srand(time(NULL));
    init_clui();
    print_list();
    select_list();
    return 0;
}