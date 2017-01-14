//
//  card.cpp
//  
//
//  Created by Jeremy on 3/27/16.
//
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>

#define MaxNumCard 100 //ㄧ人最多100張
#define MaxNumPlayer 100//最多100名玩家

using namespace std;

string Account[100];
string Password[100];

////////////////////////////////////////////////////GAME CENTER////////////////////////////////////////////
class background_Menu
{
    private:
    string Account_temp;
    string Password_temp;
    int totalplayer;
    char MenuChoice;
    char GameChoice;
    int out;
    int CurrentPlayer;
    int Score[100][3];
    
    public:
    
    background_Menu(){
        
        totalplayer = 0;
        
        for (int i=0; i<100; i++) {
            for (int j =0; j<3; j++) {
                Score[i][j]=0;
            }
        }
    }
    
    void ShowMenu(){
        
        system("clear");
        cout << "\n\n\n\n";
        cout << "\t\t\tGAME CENTER\n\n";
        cout << "\t\tPress 'n' to sign up a new account\n";
        cout << "\t\tPress 'y' to log in\n";
        cin  >> MenuChoice;
        if (MenuChoice == 'y') {
            Login();
            CheckVoid();
        }
        if (MenuChoice == 'n') {
            SetAccount();
            ShowMenu();
        }
        if (MenuChoice != 'y' && MenuChoice != 'n') {
            cout << "Invalid insert\n";
            ShowMenu();
        }
    
    }
    void Login(){
        
        system("clear");
        cout << "\n\n\n\n";
        cout << "\t\tAccount:\n";
        cout << "\t\t";
        cin  >> Account_temp;
        cout << "\n\n";
        cout << "\t\tPassword:\n";
        cout << "\t\t";
        cin  >> Password_temp;
        
    }
    void Delay(int a){
        int c,d;
        for ( c = 1 ; c <= 12767*a ; c++ )
            for ( d = 1 ; d <= 16767*a ; d++ )
            {};
        
    }
    
    void CheckVoid(){
        int i;
        for (i=1; i<totalplayer+1; i++) {
            if (Account_temp == Account[i]) {
                if (Password_temp == Password[i]) {
                    cout << "\n\t\t\t\t";
                    cout << "Success\n";
                    Delay(2);
                    CurrentPlayer = i;
                    ShowRanking();
                    break;
                }else{
                    cout << "\n\t\t\t";
                    cout << "Wrong Password\n";
                    Delay(2);
                    Login();
                    CheckVoid();
                    break;
                }
            }else if(i==totalplayer){
                cout << "\n\t\t\t";
                cout << "invalid Account\n";
                Delay(2);
                Login();
                CheckVoid();
                break;
            }
        }

        
    }
    
    void SetAccount(){
        
        system("clear");
        cout << "\n\n\n\n";
        cout << "\t  Sign up\n\n";
        while(1){
            cout << "\t\tAccount:\n";
            cout << "\t\t";
            cin  >> Account_temp;
            cout << "\n\n";
            for (int i =1; i< totalplayer+1; i++) {
                if (Account_temp == Account[i]) {
                    cout << "\t\tExisted Account\n";
                    Delay(1);
                    out = 1;
                    break;
                }else{out=0;}
            }
            if(out ==1){continue;};
            break;
        }
        Account[totalplayer+1] = Account_temp;
        
        cout << "\t\tPassword:\n";
        cout << "\t\t";
        cin  >> Password_temp;
        cout << "\n\n";
        Password[totalplayer+1] = Password_temp;
        
        cout << "\t\tAccount has been created.\n";
        Delay(1);
        totalplayer++;
    }
    
    void ShowRanking(){
        
        system("clear");
        cout << "\n\n";
        cout << "\tPlayer\t|\tGame 1\t\tGame 2\n";
        for (int i=0; i<80; i++) {cout << "-";};
        cout << "\n";
        for (int i=1; i<totalplayer+1; i++) {
            if (i == CurrentPlayer) {
                cout << "    ★";
            } else {
                cout << "     " ;
            }
            cout << Account[i] << "\n\t\t\t"<<Score[i][1] << "\t\t" <<Score[i][2] << "\n   ";
            for (int i=0; i<60; i++) {cout << "-";};
            cout << "\n";
            
        }
        
        cout << "\n\n\n";
        cout << "\t\t\t" << "Press '1' for Game 1" << "\n";
        cout << "\t\t\t" << "Press '2' for Game 2" << "\n";
        cout << "\t\t\t" << "Press 'm' for Menu" << "\n";
        cout << "\t\t\t" << "Press 'e' for Exit" << "\n";
        cout << "\t\t\t";
        cin  >> GameChoice;
        if (GameChoice != '1' && GameChoice != '2' && GameChoice != 'e' && GameChoice != 'm') {
            cout << "Invalid insert!" << "\n";
            Delay(1);
            ShowRanking();
        }
        
    }
    char getGameChoice(){
    
        return GameChoice;
    
    }
    void WinLose(int WinLose){
        
        if (WinLose) {

            Score[CurrentPlayer][GameChoice-48] = Score[CurrentPlayer][GameChoice-48] + 1;
            
        }
    }
    
};

////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////Class for Game 1////////////////////////////////////////////

class background_Game_1
{
private:
    int checkcard[1005];//檢查是否發到同樣的牌
    int rest_card[4][100];//rest_card[1][1]第一row 第一張牌
    static int row_1_endcard ;//計算各列現在第幾章牌
    static int row_2_endcard ;
    static int row_3_endcard ;
    static int row_4_endcard ;
    
public:
    
    background_Game_1(){
        for (int i=1; i<5; i++) {
            for (int j =1; j<101; j++) {
                rest_card[i][j]=0;
            }
        };
    };
    //看要幾個玩家
    int setPlayer(){
        
        int totalplayer=0;
        system("clear");
        cout << "Enter the number of players who want to play:\n";
        cin >> totalplayer;
        cout << "totalplayer:"<< totalplayer<<endl;
        return totalplayer;
        
    }
    //輸入玩家人數，卡片矩陣[玩家人數][假設最大ㄧ人張數100張]，剩下卡片矩陣
    void setCard(int totalplayer,int card[][MaxNumCard]){
        int numcard=1;//card[1][1]代表player 1，第一張牌
        int numplayer=1;
        int numrand=0;
        int i=1;
        
        while(1){
            card[numplayer][numcard]=numrand=rand()%(totalplayer*10+4)+1;
            if(checkcard[numrand]==1){continue;};
            checkcard[numrand]=1;//發過等於1
            numcard++;
            if(numcard==11){numcard=1;numplayer++;}
            if(numplayer==totalplayer+1){//如過玩家發完牌，換牌面的四張
                while (1) {
                    rest_card[i][1]=numrand=rand()%(totalplayer*10+4)+1;
                    if(checkcard[numrand]==1){continue;};
                    checkcard[numrand]=1;//發過等於1
                    i++;
                    if (i==5)break;//發到第五張停
                }
                break;}
        }
        
    }
    //Delay
    void Delay(int a){
        int c,d;
        for ( c = 1 ; c <= 12767*a ; c++ )
            for ( d = 1 ; d <= 16767*a ; d++ )
            {};
        
    }
    
    //顯示牌面
    void ShowCard(){
        
        system("clear");
        cout << "\tTable:\n" <<endl;
        
        ///////////////////////ROW 1////////////////////////////////////
        cout << " \t\t\t";
        for (int i =1; i<row_1_endcard+1; i++) cout << "----- ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_1_endcard+1; i++) {
            if((rest_card[1][i]/10) !=0)cout << "|"<< rest_card[1][i]<<" | ";//給兩位數以上
            if((rest_card[1][i]/10) ==0)cout << "|"<< rest_card[1][i]<<"  | ";//給個位數
        }
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_1_endcard+1; i++) cout << "|   | ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_1_endcard+1; i++) cout << "----- ";
        cout << " \n\n";
        
        ///////////////////////ROW 2///////////////////////////////////////
        
        cout << " \t\t\t";
        for (int i =1; i<row_2_endcard+1; i++) cout << "----- ";
        cout << "\n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_2_endcard+1; i++) {
            if((rest_card[2][i]/10) !=0)cout << "|"<< rest_card[2][i]<<" | ";//給兩位數以上
            if((rest_card[2][i]/10) ==0)cout << "|"<< rest_card[2][i]<<"  | ";//給個位數
        }
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_2_endcard+1; i++) cout << "|   | ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_2_endcard+1; i++) cout << "----- ";
        cout << " \n\n";
        
        
        ////////////////////////ROW 3//////////////////////////////////////
        
        cout << " \t\t\t";
        for (int i =1; i<row_3_endcard+1; i++) cout << "----- ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_3_endcard+1; i++) {
            if((rest_card[3][i]/10) !=0)cout << "|"<< rest_card[3][i]<<" | ";//給兩位數以上
            if((rest_card[3][i]/10) ==0)cout << "|"<< rest_card[3][i]<<"  | ";//給個位數
        }
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_3_endcard+1; i++) cout << "|   | ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_3_endcard+1; i++) cout << "----- ";
        cout << " \n\n";
        
        ////////////////////////ROW 4//////////////////////////////////////
        
        cout << " \t\t\t";
        for (int i =1; i<row_4_endcard+1; i++) cout << "----- ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_4_endcard+1; i++) {
            if((rest_card[4][i]/10) !=0)cout << "|"<< rest_card[4][i]<<" | ";//給兩位數以上
            if((rest_card[4][i]/10) ==0)cout << "|"<< rest_card[4][i]<<"  | ";//給個位數
        }
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_4_endcard+1; i++) cout << "|   | ";
        cout << " \n";
        
        cout << " \t\t\t";
        for (int i =1; i<row_4_endcard+1; i++) cout << "----- ";
        cout << " \n\n";
        
        //////////////////////////////////////////////////////////////////////
        
    }
    //顯示各玩家選牌後，經過排序後的畫面
    void ShowCardOrder(int totalplayer,int card_order[],int player_order[]){
        
        system("clear");
        cout << "\n\n";
        cout << "\tCard order: " <<endl;
        cout << "\t\t\t";
        for (int i =1; i<totalplayer+1; i++) {cout << "----- ";};
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<totalplayer+1; i++) {
            if((card_order[i]/10) !=0)cout << "|"<< card_order[i]<<" | ";//給兩位數以上
            if((card_order[i]/10) ==0)cout << "|"<< card_order[i]<<"  | ";//給個位數
        }
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<totalplayer+1; i++) {cout << "|   | ";}
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<totalplayer+1; i++) {cout << "----- ";}
        cout << "\n";
        cout << "\t\t\t";
        for (int i =1; i<60; i++) {cout << "-";}
        cout << "\n";
        cout << " Card belong to Player: ";
        for (int i =1; i<totalplayer+1; i++) {
            cout << "  "<<player_order[i]<<"   ";
        }
        cout << "\n\n";
        Delay(1);
        
    }
    //顯示玩家現在的分數
    void ShowPlayerPoint(int totalplayer,int player_point[]){
        
        cout << "Player:\t" ;
        for (int i = 1; i < totalplayer+1; i++) {
            cout << i << "\t";
        }
        cout << "\n\t";
        for(int i = 1; i< 80;i++)cout << "-";
        cout << "\n";
        cout << "Point: \t" ;
        for (int i = 1; i < totalplayer+1; i++) {
            cout << player_point[i] << "\t";
        }
        cout << "\n\n";
        
    }
    //玩家總數，出排順序的卡片，出排順序的玩家，存玩家分數
    void Determine(int totalplayer,int card_order[],int player_order[],int player_point[]){
        
        int min_different =0,temp_CurrentRow,temp_different=0,choice,a=1;
        //存放最小卡片差異      //現在暫存的列    //現在暫存的差異
        
        for (int i = 1; i<totalplayer+1; i++) {
            
            min_different =0;
            temp_CurrentRow =0;
            temp_different = (card_order[i]-rest_card[1][row_1_endcard]);
            if (temp_different>0) {
                if (row_1_endcard==5) {
                    a=1;
                    while (1) {
                        player_point[player_order[i]] = player_point[player_order[i]]+a;
                        a++;
                        if (a==6) {
                            break;
                        }
                    }
                    row_1_endcard =1;
                    min_different =0;
                    rest_card[1][1] = card_order[i];
                }else{
                    
                    min_different  = temp_different;
                    temp_CurrentRow = 1;
                    
                }
            }
            temp_different = (card_order[i]-rest_card[2][row_2_endcard]);
            if ((min_different > temp_different || min_different==0 )&& temp_different>0) {
                if (row_2_endcard==5) {
                    a=1;
                    while (1) {
                        player_point[player_order[i]] = player_point[player_order[i]]+a;
                        a++;
                        if (a==6) {
                            break;
                        }
                    }
                    row_2_endcard =1;
                    min_different =0;
                    rest_card[2][1] = card_order[i];
                }else{
                    
                    min_different  = temp_different;
                    temp_CurrentRow = 2;
                    
                }
            }
            temp_different = (card_order[i]-rest_card[3][row_3_endcard]);
            if ((min_different > temp_different || min_different==0) && temp_different>0) {
                if (row_3_endcard==5) {
                    a=1;
                    while (1) {
                        player_point[player_order[i]] = player_point[player_order[i]]+a;
                        a++;
                        if (a==6) {
                            break;
                        }
                    }
                    row_3_endcard =1;
                    min_different =0;
                    rest_card[3][1] = card_order[i];
                }else{
                    
                    min_different  = temp_different;
                    temp_CurrentRow = 3;
                    
                }
            }
            temp_different = (card_order[i]-rest_card[4][row_4_endcard]);
            if ((min_different > temp_different || min_different==0) && temp_different>0) {
                if (row_4_endcard==5) {
                    a=1;
                    while (1) {
                        player_point[player_order[i]] = player_point[player_order[i]]+a;
                        a++;
                        if (a==6) {
                            break;
                        }
                    }
                    row_4_endcard =1;
                    min_different =0;
                    rest_card[4][1] = card_order[i];
                }else{
                    
                    min_different  = temp_different;
                    temp_CurrentRow = 4;
                    
                }
            }
            if (temp_CurrentRow ==1) {row_1_endcard++;rest_card[1][row_1_endcard] = card_order[i];}//符合row1
            if (temp_CurrentRow ==2) {row_2_endcard++;rest_card[2][row_2_endcard] = card_order[i];}//符合row2
            if (temp_CurrentRow ==3) {row_3_endcard++;rest_card[3][row_3_endcard] = card_order[i];}//符合row3
            if (temp_CurrentRow ==4) {row_4_endcard++;rest_card[4][row_4_endcard] = card_order[i];}//符合row4
            //都比個row小的話
            if (temp_CurrentRow ==0) {
                a=1;
                choice = getChoice(player_order[i]);
                while (1) {
                    player_point[player_order[i]] = player_point[player_order[i]]+a;
                    if (choice==1 && row_1_endcard==a) {row_1_endcard=1;break;};
                    if (choice==2 && row_2_endcard==a) {row_2_endcard=1;break;};
                    if (choice==3 && row_3_endcard==a) {row_3_endcard=1;break;};
                    if (choice==4 && row_4_endcard==a) {row_4_endcard=1;break;};
                    a++;
                }
                rest_card[choice][1] = card_order[i];
            }
            
        }
    }
    //比牌面小的話，玩家要拿走哪ㄧrow
    int getChoice(int player_order){
        
        int choice =0;
        cout << "\nFor Player: "<< player_order <<"\nEnter your choice(number of table row 1,2,3 or 4) to eliminate:" << endl;
        cin  >> choice ;
        return choice;
        
    }
    //玩家選牌後，排序
    void sort(int totalplayer,int card_order[],int player_order[]){
        
        int temp_card,temp_player;
        for(int i=1;i<(totalplayer+1);i++)//采用一般的冒泡排序方法
            for(int j=1;j<(totalplayer+1)-i;j++)
                if(card_order[j]>card_order[j+1])
                {
                    temp_card=card_order[j];
                    temp_player=player_order[j];
                    card_order[j]=card_order[j+1];
                    player_order[j]=player_order[j+1];
                    card_order[j+1]=temp_card;
                    player_order[j+1]=temp_player;
                    
                }
        
    }
    void Recovery(){
        
        row_1_endcard =1;
        row_2_endcard =1;
        row_3_endcard =1;
        row_4_endcard =1;
        
        for (int i=0; i<1005; i++) {
            checkcard[i]=0;
        };
        
    }
    
    
};
    
    
    


class player_Game_1
{
private:
    
    
    
public:
    
    int getChoice(){
        
        int choice =0;
        cout << "Enter your choice\n(the number of the order of our card//NOT THE POINT OF OUR CARD!):" << endl;
        cin  >> choice ;
        return choice;
        
    }
    //出牌後，自己牌排序
    void ArrangeCard(int player,int choice,int card[][MaxNumCard]){
        
        int i=0;
        while (1) {
            card[player][choice+i] = card[player][choice+i+1];
            if (card[player][choice+i+1]==0)break;
            i++;
        }
        
        
    }
    //顯示自己的牌組
    void ShowCard(int player,int card[][MaxNumCard]){
        
        cout << "\n\n";
        cout << "\tCard of Player " << player << endl;
        cout << "\t\t\t";
        for (int i =1; i<11; i++) {if(card[player][i]==0)break;cout << "----- ";};
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<11; i++) {
            if(card[player][i]==0)break;
            if((card[player][i]/10) !=0)cout << "|"<< card[player][i]<<" | ";//給兩位數以上
            if((card[player][i]/10) ==0)cout << "|"<< card[player][i]<<"  | ";//給個位數
        }
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<11; i++) {if(card[player][i]==0)break;cout << "|   | ";}
        cout << "\n";
        
        cout << "\t\t\t";
        for (int i =1; i<11; i++) {if(card[player][i]==0)break;cout << "----- ";}
        cout << "\n\n";
        
    }
    
    
    
    
    
    
    
};
//初始化個row
int background_Game_1 :: row_1_endcard =1;
int background_Game_1 :: row_2_endcard =1;
int background_Game_1 :: row_3_endcard =1;
int background_Game_1 :: row_4_endcard =1;

////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////Class for Game 2////////////////////////////////////////////

class background_Game_2{
    
protected:
    
    static char ranking[100];//9種種族的順序
    char rankingtemp[100];//9種種族的順序的暫存
    int checkRanking[1000];//檢查是否有重複
    char MissonRandSpecies[4];//三種種族當任務卡片
    int checkMission[1000];//檢查是否有重複
    
    
public:
    background_Game_2(int numberofspecies){
        int check;
        for (int i=0;i<100 ; i++) {
            ranking[i]=0;
        }
        for (int i=0;i<1000 ; i++) {
            checkRanking[i]=0;
            checkMission[i]=0;
        }
        for (int i=1; i<4; i++) {
            MissonRandSpecies[i]=check=rand()%numberofspecies+1+64;
            if (checkMission[check]==1){i=i-1;continue;
            }
            else checkMission[check]=1;
            
        }
    };
    //設定9種種族的順序
    void SetRanking(int numberofspecies){
        
        int temp;
        for (int i =1; i<numberofspecies+1; i++) {
            ranking[i]=temp=rand()%numberofspecies+1+64;//rand 設定ＡＢＣ...順序
            if (checkRanking[temp]==1){i=i-1;continue;
            }
            else checkRanking[temp]=1;
            
        }
        
    }
    
    //輸出原始順序
    void PrintInitialSpeciesOrder(){
        cout << "\nThe initial order of the species:\n";
        cout << "\t";
        for (int i =1; i<10; i++) {
            cout << ranking[i] << "\t";
            
        }
        cout << "\n";
    }
    
    void Recovery(int numberofspecies){
    
            int check;
            for (int i=0;i<100 ; i++) {
                ranking[i]=0;
            }
            for (int i=0;i<1000 ; i++) {
                checkRanking[i]=0;
                checkMission[i]=0;
            }
            for (int i=1; i<4; i++) {
                MissonRandSpecies[i]=check=rand()%numberofspecies+1+64;
                if (checkMission[check]==1){i=i-1;continue;
                }
                else checkMission[check]=1;
                
            }
    
    }
    
};

class player_Game_2 : public background_Game_2{
    
private:
    int totalpoint;//玩家總分
    int remaining_first_card;//剩餘卡片ㄧ的張數
    int remaining_second_card;//剩餘卡片二的張數
    int remaining_third_card;//剩餘卡片三的張數
    int remaining_last_card;//剩餘卡片四的張數
    int remaining_eliminate_card;//剩餘卡片五的張數
    int temp;
    
public:
    
    player_Game_2(int numberofspecies):background_Game_2(numberofspecies){
        totalpoint=0;
        remaining_first_card=2;
        remaining_second_card=1;
        remaining_third_card=1;
        remaining_last_card=1;
        remaining_eliminate_card=2;
        temp = numberofspecies;//存放現在場上有幾個species
        
    };
    void Recovery(int numberofspecies){
        
        totalpoint=0;
        remaining_first_card=2;
        remaining_second_card=1;
        remaining_third_card=1;
        remaining_last_card=1;
        remaining_eliminate_card=2;
        temp = numberofspecies;//存放現在場上有幾個species
    
    }
    void Delay(int a){
        int c,d;
        for ( c = 1 ; c <= 12767*a ; c++ )
            for ( d = 1 ; d <= 16767*a ; d++ )
            {};
        
    }
    void SetRanking(int numberofspecies){
        for (int i =1; i<numberofspecies+1; i++) {
            rankingtemp[i] = ranking[i];
        }
    }
    char Intruction(){
        char CardChoice;
        cout << "Enter the number of the card which you want to use:" << "\n\n";
        cout << "1 : exchange the selected species to the first place" << "\n";
        cout << "2 : exchange the selected species to the second place" << "\n";
        cout << "3 : exchange the selected species to the third place" << "\n";
        cout << "4 : exchange the selected species to the last place" << "\n";
        cout << "5 : eliminate the species which is at the last place" << "\n";
        cin  >> CardChoice ;
        return CardChoice;
        
    }
    //種族選擇
    int SpeciesChoice(char CardChoice,int computermode){
        
        int specieschoice;
        if (CardChoice == 49) {
            if (remaining_first_card != 0) {
                cout << "\nEnter the order of the species which you want to exchange(1~9):" << "\n";
                if (computermode !=1) {
                    cin >> specieschoice ;
                }else{
                    specieschoice = rand()%temp+1;
                }
                remaining_first_card--;
                return specieschoice;
            }
            else{
                cout << "No more remaining card!!" << "\n";
                Delay(1);
                return 1;
            }
        }
        if (CardChoice == 50) {
            if (remaining_second_card != 0) {
                cout << "\nEnter the order of the species which you want to exchange(1~9):" << "\n";
                if (computermode !=1) {
                    cin >> specieschoice ;
                }else{
                    specieschoice = rand()%temp+1;
                }
                remaining_second_card--;
                return specieschoice;
            }
            else{
                cout << "No more remaining card!!" << "\n";
                Delay(1);
                return 1;
            }
        }
        if (CardChoice == 51) {
            if (remaining_third_card != 0) {
                cout << "\nEnter the order of the species which you want to exchange(1~9):" << "\n";
                if (computermode !=1) {
                    cin >> specieschoice ;
                }else{
                    specieschoice = rand()%temp+1;
                }
                remaining_third_card--;
                return specieschoice;
            }
            else{
                cout << "No more remaining card!!" << "\n";
                Delay(1);
                return 1;
            }
        }
        if (CardChoice == 52) {
            if (remaining_last_card != 0) {
                cout << "\nEnter the order of the species which you want to exchange(1~9):" << "\n";
                if (computermode !=1) {
                    cin >> specieschoice ;
                }else{
                    specieschoice = rand()%temp+1;
                }
                remaining_last_card--;
                return specieschoice;
            }
            else{
                cout << "No more remaining card!!" << "\n";
                Delay(1);
                return 1;
            }
        }
        if (CardChoice == 53) {
            if (remaining_eliminate_card != 0) {
                
                remaining_eliminate_card--;
                
            }
            else{
                cout << "No more remaining card!!" << "\n";
                Delay(1);
                return 1;
            }
            
        }
        return 0;
    }
    //檢查卡是否都用完
    char Determine_remaining_card(){
        if (remaining_first_card ==0 && remaining_second_card ==0 && remaining_third_card ==0 &&remaining_third_card ==0 && remaining_last_card ==0 &&
            remaining_eliminate_card ==0) {
            cout << "NO MORE REMAINING CARD FOR CARD(1~5)!!" << "\n";
            Delay(1);
            return 'n';
        }else{
            return 'y';
        }
    }
    void Exchange_to_first(int choice){
        int temp;
        if (choice != 1) {
            temp = rankingtemp[1];
            rankingtemp[1] = rankingtemp[choice];
            rankingtemp[choice] = temp;
        }
    }
    void Exchange_to_second(int choice){
        int temp;
        if (choice != 1) {
            temp = rankingtemp[2];
            rankingtemp[2] = rankingtemp[choice];
            rankingtemp[choice] = temp;
            
        }
    }
    void Exchange_to_third(int choice){
        int temp;
        if (choice != 1) {
            temp = rankingtemp[3];
            rankingtemp[3] = rankingtemp[choice];
            rankingtemp[choice] = temp;
            
        }
    }
    void Exchange_to_last(int choice){
        int temp_ranking;
        if (choice != 1) {
            temp_ranking = rankingtemp[choice];
            for (int i = choice; i<temp; i++) {
                rankingtemp[i] = rankingtemp[i+1];
            }
            rankingtemp[temp] = temp_ranking;
        }
    }
    void Eliminate_the_last_card(int choice){
        
        if (choice != 1) {
            rankingtemp[temp] = 0;
            temp--;
        }
    }
    //算最後總分
    int Determine(){
        
        if (rankingtemp[1] == MissonRandSpecies[1])totalpoint = totalpoint+3;
        if (rankingtemp[2] == MissonRandSpecies[1] || rankingtemp[2] == MissonRandSpecies[2])totalpoint = totalpoint+2;
        if (rankingtemp[3] == MissonRandSpecies[1] || rankingtemp[3] == MissonRandSpecies[2] || rankingtemp[3] == MissonRandSpecies[3])totalpoint = totalpoint+1;
        return totalpoint;
    }
    //輸出玩家現在的順序
    void print(){
        cout << "\n\t";
        for (int i =1; i<10; i++) {
            cout << rankingtemp[i] << "\t";
        }
        cout << "\n\n";
        cout << "\n\nMissionCard\n";
        for (int i =1; i<4; i++) {
            cout << MissonRandSpecies[i];
            if (i==1) {
                cout << "    At the (1,2,3)place get (+3,+2,+1)point" << "\n";
            }
            if (i==2) {
                cout << "    At the (2,3)place get (+2,+1)point" << "\n";
            }
            if (i==3) {
                cout << "    At the (3)place get (+1)point" << "\n";
            }
            
        }
        cout << "\n\n";
        
    }
};

void Delay(int a){
    int c,d;
    for ( c = 1 ; c <= 12767*a ; c++ )
        for ( d = 1 ; d <= 16767*a ; d++ )
        {};
    
}


char background_Game_2::ranking[100] = {0};

//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    
    background_Menu Menu;
    char GameChoice;
    
    /////////////////////////////Variable for Game 1 ////////////////////////////////////
    
    int card[MaxNumPlayer][MaxNumCard]={0},rest_card[4]={0},card_order[MaxNumCard]={0},player_order[MaxNumPlayer]={0},choice,player_point[MaxNumPlayer];
    static int totalplayer;
    int Mininum;
    
    background_Game_1 Game_1;
    player_Game_1 player_Game_1;
    
    /////////////////////////////////////////////////////////////////////////////////////
    
    ///////////////////////////Variable for Game 2///////////////////////////////////////
    
    int player_totalpoint,computer_totalpoint,computer_yesorno,computer_CardChoice,computer_specieschoice,c=80;
    char CardChoice,specieschoice,leftorno;
    background_Game_2 Game_2(9);
    player_Game_2 player_Game_2(9),computer_Game_2(9);
    srand(time(NULL));

    /////////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////Menu////////////////////////////////////////////////

    Menu.SetAccount();
    Menu.ShowMenu();
    
    /////////////////////////////////////////////////////////////////////////////////////
    
while (1) {
    
    GameChoice = Menu.getGameChoice();
    if (GameChoice == 'e') {break;};
    if (GameChoice == 'm') {
        Menu.ShowMenu();
    }
    
    ////////////////////////////////////GAME 1/////////////////////////////////////////////
    
    
    //Start to play Game 1
    if (GameChoice == '1') {

        totalplayer = Game_1.setPlayer();
        Game_1.setCard(totalplayer,card);
        
        Game_1.ShowCard();
        Game_1.ShowPlayerPoint(totalplayer,player_point);
        
        for (int count=0; count<10; count++) {
            
            for (int i=1; i<totalplayer+1 ; i++) {
                
                player_Game_1.ShowCard(i,card);
                
                choice = player_Game_1.getChoice();
                card_order[i] = card[i][choice];
                player_order[i] = i;
                
                player_Game_1.ArrangeCard(i,choice,card);
                
            }
            
            Game_1.sort(totalplayer,card_order,player_order);
            Game_1.ShowCardOrder(totalplayer,card_order,player_order);
            Game_1.Determine(totalplayer,card_order,player_order,player_point);
            Game_1.ShowCard();
            Game_1.ShowPlayerPoint(totalplayer,player_point);
            
        }
        for (int i = 2; i<totalplayer+1; i++) {
            (player_point[1] < player_point[i]) ? Mininum = player_point[1] : Mininum = player_point[i];
        }
        
        if (player_point[1]==Mininum) {
            cout << "YOU WIN!!!YOU GOT ONE POINT!!!" << endl;
            Delay(2);
            Menu.WinLose(1);
            Menu.ShowRanking();
            Game_1.Recovery();
            for (int i = 1; i<totalplayer+1; i++) {player_point[i] =0;}
            
        }else{
            cout << "YOU LOSE!!" << endl;
            Delay(2);
            Menu.ShowRanking();
            Game_1.Recovery();
            for (int i = 1; i<totalplayer+1; i++) {player_point[i] =0;}

            
        }
        
    }
    
    /////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////GAME 2/////////////////////////////////////////
    
    if (GameChoice == '2') {
        
        Game_2.SetRanking(9);//設定順序有9個種族
        Game_2.PrintInitialSpeciesOrder();
        
        //玩家模式
        leftorno = 'y';
        player_Game_2.SetRanking(9);
        while (leftorno == 'y') {
            system("clear");
            for (int i =0; i<c; i++) {cout << "-" ;}cout<<"\n";
            cout << "Player:" << "\n";
            player_Game_2.print();
            CardChoice = player_Game_2.Intruction();
            specieschoice = player_Game_2.SpeciesChoice(CardChoice,0);
            if (CardChoice == 49) player_Game_2.Exchange_to_first(specieschoice);
            if (CardChoice == 50) player_Game_2.Exchange_to_second(specieschoice);
            if (CardChoice == 51) player_Game_2.Exchange_to_third(specieschoice);
            if (CardChoice == 52) player_Game_2.Exchange_to_last(specieschoice);
            if (CardChoice == 53) player_Game_2.Eliminate_the_last_card(specieschoice);
            leftorno = player_Game_2.Determine_remaining_card();
            for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        }
        
        system("clear");
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        cout << "Player:" << "\n";
        player_Game_2.print();
        player_totalpoint=player_Game_2.Determine();
        cout << "The final score for player:" << player_totalpoint << "\n";
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        
        
        //電腦模式
        leftorno = 'y';
        computer_Game_2.SetRanking(9);
        while (leftorno == 'y') {
            system("clear");
            for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
            cout <<"\n\n"<<"Computer:" << "\n";
            computer_Game_2.print();
            computer_CardChoice = rand()%5+1+48;
            computer_specieschoice = computer_Game_2.SpeciesChoice(computer_CardChoice,1);
            if(computer_CardChoice == 49){computer_Game_2.Exchange_to_first(computer_specieschoice);}
            if(computer_CardChoice == 50){computer_Game_2.Exchange_to_second(computer_specieschoice);}
            if(computer_CardChoice == 51){computer_Game_2.Exchange_to_third(computer_specieschoice);}
            if(computer_CardChoice == 52){computer_Game_2.Exchange_to_last(computer_specieschoice);}
            if(computer_CardChoice == 53){computer_Game_2.Eliminate_the_last_card(computer_specieschoice);}
            
            leftorno = computer_Game_2.Determine_remaining_card();
            for (int i =0; i<c; i++) {cout << "-" ;}cout<<"\n";
        }
        
        system("clear");
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        cout << "\n\n"<<"Computer:" << "\n";
        computer_Game_2.print();
        computer_totalpoint=computer_Game_2.Determine();
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        
        //輸出總結果
        system("clear");
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        cout << "\n\n"<<"Computer:" << "\n";
        computer_Game_2.print();
        cout << "Player:" << "\n";
        player_Game_2.print();
        
        cout << "The final score for player:" << player_totalpoint << "\n";
        cout << "The final score for computer:" << computer_totalpoint << "\n";
        for (int i =0; i<c; i++) {cout << "-";}cout<<"\n";
        
        if (player_totalpoint > computer_totalpoint) {
            cout << "The Player win!!!" << "\n";
            Delay(3);
            Menu.WinLose(1);
            Menu.ShowRanking();
            Game_2.Recovery(9);
            player_Game_2.Recovery(9);
            computer_Game_2.Recovery(9);
        }
        else if (player_totalpoint == computer_totalpoint){
            cout << "Tie!!!" << "\n";
            Delay(3);
            Menu.ShowRanking();
            Game_2.Recovery(9);
            player_Game_2.Recovery(9);
            computer_Game_2.Recovery(9);
        }
        else{
            cout << "The computer win!!!" << "\n";
            Delay(3);
            Menu.ShowRanking();
            Game_2.Recovery(9);
            player_Game_2.Recovery(9);
            computer_Game_2.Recovery(9);
        }
    }
}
    return EXIT_SUCCESS;

}

