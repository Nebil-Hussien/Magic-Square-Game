/*
    Magic Square Game

    Done by : - Liuel Shimelis      NSR/9269/10
                Mukhtar Saeed       NSR/3425/10
                Nebil Abdulsemed    NSR/1355/10
                Sebhatleab Mekbib   NSR/    /10
                Yitayesh Asabu      NSR/    /10
                Yoakin H/Gebriel    NSR/9650/10
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

//Linked list data structures
struct MagicSquare {
    int data;
    MagicSquare *next,*previous,*down,*up;
}
*head=NULL,*tail=NULL;

int sum_row=0,sum_column=0;     //Those variables will be used to sum up rows with columns

int score=0;        //This Variable will be used to score highscore

bool check_win();	//This function checks if the user won or not

void Interface();	//Interface of the game board

void Initialize();	//Initializes the square with random numbers and makes sure the numbers are not the same

void delete_Game();	//Deletes the game after winning

void Change_numbers(int num,int key);	//changes the numbers accordingly from the user

void setHighscore(int highscore);       //Saves highscore to storage

void getHighscore();    //extracts highscore from storage

void setTimer(time_t tFinal, time_t tInitial);         //Uses time for ranking

int main()
{
    int number,key;     //These are variables to change numbers with, and pass it as a parameter
    char ch,choice; //loop control variables
    do{
        SetConsoleTitle("Magic Square Game");
	    system("color 5f");
    	cout<<setw(67)<<"Magic Square Game"<<endl<<endl<<endl;
    	cout<<"\t\tooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
    	cout<<"\t\to                                                                 o"<<endl;
    	cout<<"\t\to                                                                 o"<<endl;
    	cout<<"\t\to                            1: To play game                      o"<<endl;
    	cout<<"\t\to                            2: To read Instruction               o"<<endl;
    	cout<<"\t\to                            3: To display Highscore              o"<<endl;
    	cout<<"\t\to                            4: About Us                          o"<<endl;
    	cout<<"\t\to                            Press ESC to Exit                    o"<<endl;
    	cout<<"\t\to                                                                 o"<<endl;
    	cout<<"\t\tooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
    	choice=getch();
    	switch(choice)
    	{
            case '1':
    		    system("cls");

                do{
                    Initialize();
                    cout<<"Game started, Go!!!"<<endl;
                    time_t tInitial = time(0);        //time initialized on tInitial
                    while(!check_win())
                    {
                        Interface();
                        cout<<"\nChange number: ";6
                        cin>>key;
                        while(key<1||key>9)
                        {
                            cout<<"You cannot enter a number greater than 9 or less than 1!"
                                <<"Please enter a valid number: "<<endl;
                            cin>>key;
                        }
                        cout<<"\nwith?: ";
                        cin>>number;
                        while(number<1||number>9)
                        {
                            cout<<"You cannot enter a number greater than 9 or less than 1!"
                                <<"Please enter a valid number: "<<endl;
                            cin>>number;
                        }
                        Change_numbers(number,key);
                        score++;
                        Interface();
                    }
                    time_t tFinal=time(0);
                    cout<<"\tCongratulation, You Won!"<<endl;
                    cout<<"\tYou did it in "<<score<<" moves and "<<difftime(tFinal,tInitial)<<" seconds"<<endl;
                    setHighscore(score);
                    setTimer(tFinal,tInitial);
                    system("pause");
                    delete_Game();
                    cout<<"do you want to play again (press ESC to get back to Main menu) ?"<<endl;
                    ch=getch();
                    }while(ch!=27);     //As 27 is the ASCII value for 'ESC' key
                break;
			case '2':
				system("cls");
				cout<<"This game is about Entering Numbers in the according squares"<<endl;
				cout<<"the entered numbers must be from 1 to 9"<<endl;
				cout<<"If you want to win, Then you must fulfil those rules"<<endl;
				system("pause");
				cout<<"Rule 1: The sum of the rows must equal the sum of the column"<<endl;
				cout<<"Rule 2: You cannot repeat numbers"<<endl;
				cout<<"Further if you win with accordingly within those time limits,"<<endl;
				cout<<"it will reward you with stars"<<endl;
				cout<<"\t 1 Star (*)      < 180 sec"<<endl;
				cout<<"\t 2 Star (**)     < 90 sec"<<endl;
				cout<<"\t 3 Star (***)    < 45 sec"<<endl;
				cout<<"\t 4 Star (****)   < 30 sec"<<endl;
				cout<<"\t 5 Star (*****)  < 15 sec"<<endl;
				system("pause");
                break;
            case '3':
                system("cls");
                getHighscore();
                break;
            case '4':
                system("cls");
                cout<<"\t\t\tDevelopers"<<endl;
                cout<<"\t\tooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
                cout<<"\t\to                                                                 o"<<endl;
                cout<<"\t\to                                                                 o"<<endl;
                cout<<"\t\to               1: LIUEL SHIMELES     NSR/9269/10                 o"<<endl;
                cout<<"\t\to               2: MUKHTAR SAEED      NSR/3425/10                 o"<<endl;
                cout<<"\t\to               3: NEBIL ABDULSEMED   NSR/1355/10                 o"<<endl;
                cout<<"\t\to               4: Sebhatleab Mekbib  NSR/5824/10                 o"<<endl;
                cout<<"\t\to               5: YITAYISH ASABU     NSR/9947/10                 o"<<endl;
                cout<<"\t\to               6: YOAKIN H/GEBRIEL   NSR/9650/10                 o"<<endl;
                cout<<"\t\tooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
                break;
			case 27:
			cout<<"Thank you!"<<endl;
				exit(0);
				break;
			default:
				cout<<"Invalid Input!"<<endl;
			}
			}while(1);

			return 0;
}
bool check_win()
{
	bool Check_columns=false;
	bool Check_rows=false;
    int row=0,column=0;
    MagicSquare *temp_row=head,*temp_column=head;       //these pointers are used to access the list accordingly
    for(int i=0;i<3;i++)
    {
        temp_column=temp_row;
        while(temp_column!=NULL)
        {
            sum_column+=temp_column->data;
            temp_column=temp_column->down;
        }
        if(sum_column==15)
        {
        	column++;       //the sum of column is 15
		}
		sum_column=0;
		temp_row=temp_row->next;
    }
    if(column==3)
    {
    	Check_columns=true;     //All columns have sum = 15
	}
	temp_row=head;
	while(temp_row!=NULL)
	{
		for(int i=0;i<3;i++)
		{
			sum_row+=temp_row->data;
			temp_row=temp_row->next;
		}
		if(sum_row==15)
		{
			row++;
		}
		sum_row=0;
	}
	if(row==3)
	{
		Check_rows=true;        //All rows sum is 15
	}
	if(Check_rows&&Check_columns)
	{
		return true;        //All rows sum and columns sum is 15
	}
	else
	{
		return false;
	}
}
void Interface()
{
	system("cls");
	cout<<setw(67)<<"Magic Square Game"<<endl;
    sum_column=0;		//Output of row sum
    sum_row=0;			//Output of column sum
    if(head==NULL)
    {
        cout<<"List is empty"<<endl;
    }
    else
    {
        int ctr=0;
        MagicSquare *temp=head;
        cout<<endl<<endl;
        cout<<setw(45);
        while(temp!=NULL)
        {
            cout<<"|___"<<temp->data<<"___|";
            ctr++;
            sum_row+=temp->data;
            if(ctr==3||ctr==6||ctr==9)
            {
                cout<<" = "<<sum_row;
                sum_row=0;
                cout<<endl;
                cout<<setw(45);
            }
            temp=temp->next;
        }
        temp=head;
        cout<<" ";
        for(int i=0;i<3;i++)
        {
            sum_column+=temp->data+temp->down->data+temp->down->down->data;
            cout<<sum_column<<"       ";
            sum_column=0;
            temp=temp->next;
        }
        cout<<endl;
    }
}
bool check_repeat(int ToBeChecked)
{
    if(head==NULL)
        return false;
    else
    {
        MagicSquare *temp=head;
        while(temp!=NULL)
        {
            if(temp->data==ToBeChecked)
                return true;
            temp=temp->next;
        }
        return false;
    }
}
void Initialize()
{
    srand(time(NULL));      //Random number Generator
    for(int i=1;i<=9;i++)
    {
        MagicSquare *newSquare = new MagicSquare;
        newSquare->next=NULL;
        newSquare->down=NULL;
        newSquare->up=NULL;
        do{
            newSquare->data=rand()%10;
        }while(newSquare->data==0||check_repeat(newSquare->data));
        if(head==NULL)
        {
            newSquare->next=NULL;
            newSquare->down=NULL;
            newSquare->up=NULL;
            head=newSquare;
            tail=newSquare;
        }
        else
            {
                newSquare->previous=tail;
                tail->next=newSquare;
                tail=newSquare;
                newSquare->up=NULL;
                if(i>3)     //That means there is upper node and from here the square will have relation with its upper node
                {
                    newSquare->up=newSquare->previous->previous->previous;//Accessing the node above them
                    newSquare->previous->previous->previous->down=newSquare;//Accessing the node below them
                    newSquare->down=NULL;
                }
            }
    }
}
void delete_Game()
{
    head=NULL;
    tail=NULL;
}
void Change_numbers(int num,int key)
{
    if(head==NULL)
    {
        cout<<"List is empty";
    }
    else
    {
        MagicSquare *temp1=head,*temp2=head;
        while(temp1->data!=key)
        {
            if(temp1->next==NULL)
            {
                cout<<"Given node is not found in the list!"<<endl;
                return;
            }
            temp1=temp1->next;
        }
        if(temp1->data==key)
        {
            while(temp2->data!=num)
            {
                if(temp2->next==NULL)
                {
                    cout<<"Number is not found in the square";
                    return;
                }
                temp2=temp2->next;
            }
            if(temp2->data==num)    //Swapping the elements
            {
                int Swap=temp1->data;
                temp1->data=temp2->data;
                temp2->data=Swap;
            }
        }
    }
}


void setHighscore(int score)
{
    ofstream high;
    ifstream higher;
    int highscore=0;
    higher.open("Highscores.txt",ios::in|ios::app);
    while(!higher.eof())
    {
        higher>>highscore;
    }

    if(score<highscore)
    {
    high.open("Highscores.txt",ios::out);
    if(high.fail())
    {
        cerr<<"Error!"<<endl;
        return;
    }
    cout<<"New highscore!!"<<endl;
    high<<score;
    high.close();
    }
    higher.close();
}


void getHighscore()
{
    ifstream Gethigh;
    char highscore[3];
    Gethigh.open("Highscores.txt",ios::in);
    if(Gethigh.fail())
    {
        cerr<<"No highscores currently"<<endl;
        return;
    }
    while(!Gethigh.eof())
    {
        Gethigh>>highscore;
    }
    cout<<"Highscore = "<<atoi(highscore)<<endl;
    Gethigh.close();
}
void setTimer(time_t tFinal, time_t tInitial)
{
    if((int)difftime(tFinal,tInitial)>=180)
    {
        cout<<"Slow"<<endl;
        cout<<"*"<<endl;
    }
    else if ((int)difftime(tFinal,tInitial)>=60&&(int)difftime(tFinal,tInitial)<180)
    {
        cout<<"Not bad "<<endl;
        cout<<"**"<<endl;
    }
    else if ((int)difftime(tFinal,tInitial)>=30&&(int)difftime(tFinal,tInitial)<60)
    {
        cout<<"That was good"<<endl;
        cout<<"***"<<endl;
    }
    else if ((int)difftime(tFinal,tInitial)>=10&&(int)difftime(tFinal,tInitial)<30)
    {
        cout<<"Excellent"<<endl;
        cout<<"****"<<endl;
    }
    else
    {
        cout<<"Awesome !!!"<<endl;
        cout<<"*****"<<endl;
    }
}


