#include"Gamelib.h"

using namespace std;

int main()
{
bool Continue = true;
while(Continue)
{
	
	Player CurrentPlayer(0,0,"undefined");
	
	bool ValidChoice = false;
	while(!ValidChoice)
	{
		system("cls");
		//con.color(0x04);
		DrawSprite("Title.txt", 0x0C);
		//con.color(0x07);
		cout<<endl<<endl;
		cout<<"[1] NUOVA PARTITA"<<endl;
		cout<<"[2] CARICA PERSONAGGIO"<<endl;
		
		char Choice;
		string UserChoice;
		cin>>UserChoice;
		if(UserChoice.length()!=1)
			Choice = '0';
		else Choice = UserChoice[0];
		
		switch(Choice)
		{
			case '1':
			{
				system("cls");
				CurrentPlayer = CreatePlayer();
				ValidChoice = true;
				break;
			}
			case '2':
			{
				system("cls");
				bool Found;
				cout<<"Inserisci il nome del personaggio:"<<endl;
				string PlayerName;
				cin>>PlayerName;
				CurrentPlayer = LoadFromFile(PlayerName, Found);
				if(Found)
				{
					char CharChoice;
					bool Valid = false;
					while(!Valid)
					{
						system("cls");
						CurrentPlayer.ShowStats();
						cout<<endl<<"Iniziare nuova partita con questo personaggio? [Y/N]"<<endl<<endl;
						string UserChoice;
						cin>>UserChoice;
						if(UserChoice.length()!=1)
							CharChoice = '0';
						else CharChoice = UserChoice[0];
						switch(CharChoice)
						{
							case 'y':
								Valid = true;
								ValidChoice = true;
								break;
							case 'n':
								Valid = true;
								break;
							default:
								cout<<"Non valido!"<<endl;
								Delay(1);
								break;
						}
					}
				}
				else
				{
					cout<<"Personaggio non trovato"<<endl;
					Delay(1);
				}
				break;
			}
			default:
			{
				cout<<"Non valido!"<<endl;
				Delay(1);
				break;
			}	
		}
	}
	
		Game NewGame_1;
		system("cls");
		NewGame_1.Start(CurrentPlayer);
		Delay(3);


		char Choice;
		string UserChoice;
		
		bool Valid = false;
		
		while(!Valid)
		{
			system("cls");
			DrawText("Iniziare una nuova partita? [Y/N]", 4, 120);
			cin>>UserChoice;
			if(UserChoice.length()!=1)
				Choice = '0';
			else Choice = UserChoice[0];
			
			switch(Choice)
			{
				case 'y':
					Valid = true;
					Continue = true;
					break;
				case 'n':
					Valid = true;
					Continue = false;
					break;
				default:
					cout<<"Scelta non valida"<<endl;
					break;
			}
		}
	
}



system("pause");
return 0;
}
