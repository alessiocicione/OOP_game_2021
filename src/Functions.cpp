#include"Gamelib.h"

using namespace std;

// Ridimensiono la finestra del terminale
console con(120, 40);

string ReturnRating(Rating Value)
{
	switch(Value)
	{
		case Rating::E:
			return "E";
			break;
		case Rating::D:
			return "D";
			break;
		case Rating::C:
			return "C";
			break;
		case Rating::B:
			return "B";
			break;
		case Rating::A:
			return "A";
			break;
		case Rating::S:
			return "S";
			break;
		default:
			return "unkonwn";
			break;
	}
}

string ReturnAttribute(Attribute Value)
{
	switch(Value)
	{
		case Attribute::Str:
			return "STR";
			break;
		case Attribute::Per:
			return "PER";
			break;
		case Attribute::End:
			return "END";
			break;
		case Attribute::Cha:
			return "CHA";
			break;
		case Attribute::In:
			return "INT";
			break;
		case Attribute::Agi:
			return "AGI";
			break;
		case Attribute::Lck:
			return "LCK";
			break;
		case Attribute::NO:
			return "N/A";
			break;
		default:
			return "unkonwn";
			break;
	}
}

// overloading degli operatori di stream
ostream& operator<<(ostream &ofs, Player Character)
{
	ofs<<Character.def<<","<<Character.atk<<","<<Character.name<<","<<Character.BOT<<","<<Character.str<<","<<Character.per<<","<<Character.end<<","<<Character.cha<<","<<Character.in<<","<<Character.agi<<","<<Character.lck<<","<<Character.HpCap<<","<<Character.crit_mult<<","<<Character.GuardStr<<","<<Character.HealCap<<","<<Character.Coins<<","<<Character.HealMult<<";"<<endl;
	return ofs;	
}

istream& operator>>(istream &ifs, Player &Character)
{
	string text;
	getline(ifs,text,',');
	Character.def = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.atk = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.name = text;
	
	getline(ifs,text,',');
	Character.BOT = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.str = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.per = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.end = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.cha = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.in = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.agi = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.lck = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.HpCap = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.crit_mult = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.GuardStr = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.HealCap = atoi(text.c_str());
	
	getline(ifs,text,',');
	Character.Coins = atoi(text.c_str());
	
	getline(ifs,text,';');
	Character.HealMult = atof(text.c_str());
	return ifs;	
}

/*!
* \fn      	SaveToFile(Player Character)
* \brief    Salva su file tutti i parametri di interesse di un personaggio
* \param    Player Character
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void SaveToFile(Player Character)
{
	string Filename = Character.name + ".txt";
	ofstream ofs (Filename);
	if(ofs.good())
		ofs<<Character;
}

/*!
* \fn      	LoadFromFile(string CharacterName, bool &Found)
* \brief    Carica da file un personaggio
* \param    string CharacterName
* \param	bool &Found
* \return   Player
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Player LoadFromFile(string CharacterName, bool &Found)
{
	ifstream ifs;
	string Filename = CharacterName + ".txt";
	Player TempCharacter(0,0,"undefined");
	ifs.open(Filename);
	if(ifs.good())
	{
		// personaggio trovato
		Found = true;
		ifs>>TempCharacter;
		// Creo l'arma iniziale
		Weapon<Player> StarterWeapon;
		StarterWeapon.SetStats("[STARTER] Spada spezzata", 5, 0, NO, E, NO);
		// Creo l'armatura iniziale
		Armor<Player> StarterArmor;
		StarterArmor.SetStats("[STARTER] Vecchia Tunica", 4, 0, NO);
		// Assegno l'arma iniziale
		TempCharacter.SetCurrentWeapon(StarterWeapon);
		// Assegno l'armatura iniziale
		TempCharacter.SetCurrentArmor(StarterArmor);
		
		return TempCharacter;
	}
}

/*!
* \fn      	Weapon<Player> GenerateWeapon(int EntLvl = 0)
* \brief    Genera un arma randomicamente
* \param    int EntLvl
* \return   Weapon<Player>
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Weapon<Player> GenerateWeapon(int EntLvl)
{
	// EntLvl rappresenta il livello del nemico sconfitto
	string name, rarity, type, skill;
	Rating LootScaleClass;
	Attribute ScaleAttr, SkillAttr;
	int SkillBuff;
	int value;
	// Piu' alta la rarita' dell'arma, maggiore l'attacco
	float DmgMult = 1;
	WORD Color;
	srand(time(NULL));
	// Genero un valore casuale per determinare la rarita' dell'arma trovata
	value = rand()%100 + 1;
	// Nemici di livello maggiore avranno piu' possibilita' di rilasciare un arma di rarita' maggiore
	value += EntLvl*2;
	if(value< 45 and value>=1)
	{
		// Armi comuni
		LootScaleClass = E;
		rarity = "[COMMON]";
		Color = 0x0F;
		// Buff ad attributo
		SkillBuff = 1;
	}
	else if(value< 75 and value>=45)
		 {
		 	// Armi non comuni
		 	LootScaleClass = D;
		 	rarity = "[UNCOMMON]";
		 	Color = 0x0A;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+1;
		 	// Moltiplicatore danno
		 	DmgMult = 1.3;
		 }
	else if(value< 87 and value>=75)
		 {
		 	LootScaleClass = C;
		 	rarity = "[RARE]";
		 	Color = 0x09;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+3;
		 	DmgMult = 1.5;
		 }
	else if(value< 95 and value>=87)
		 {
		 	LootScaleClass = B;
		 	rarity = "[RELIC]";
		 	Color = 0x04;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+5;
		 	DmgMult = 1.7;
		 }
	else if(value< 98 and value>=95)
		 {
		 	LootScaleClass = A;
		 	rarity = "[LEGENDARY]";
		 	Color = 0x05;
		 	srand(time(NULL));
		 	SkillBuff = rand()%2+7;
		 	DmgMult = 1.9;
		 }
	else if(value>=98)
		 {
		 	LootScaleClass = S;
		 	rarity = "[EXOTIC]";
		 	Color = 0x06;
		 	SkillBuff = 9;
		 	DmgMult = 2.1;
		 }
	srand(time(NULL));
	// Scelgo casualmente l'attributo a cui l'arma conferira' un buff
	int Value = rand()%7+1;
	switch(Value)
	{
		case 1:
			ScaleAttr = Str;
			type = "Mazza Flangiata";
			break;	
		case 2:
			ScaleAttr = Per;
			type = "Arco";
			break;
		case 3:
			ScaleAttr = End;
			type = "Lancia";
			break;
		case 4:
			ScaleAttr = Cha;
			type = "Fioretto";
			break;
		case 5:
			ScaleAttr = In;
			type = "Bastone";
			break;
		case 6:
			ScaleAttr = Agi;
			type = "Pugnale";
			break;
		case 7:
			ScaleAttr = Lck;
			type = "Spada da Caccia";
			break;
	}
	
	// Scelgo casualmente l'attributo sul quale effettuare lo scaling dell'arma
	Value = rand()%7+1;
	switch(Value)
	{
		case 1:
			SkillAttr = Str;
			skill = " della forza";
			break;	
		case 2:
			SkillAttr = Per;
			skill = " della percezione";
			break;
		case 3:
			SkillAttr = End;
			skill = " della resistenza";
			break;
		case 4:
			SkillAttr = Cha;
			skill = " del carisma";
			break;
		case 5:
			SkillAttr = In;
			skill = " della saggezza";
			break;
		case 6:
			SkillAttr = Agi;
			skill = " della destrezza";
			break;
		case 7:
			SkillAttr = Lck;
			skill = " della fortuna";
			break;
	}
	// Compongo il nome
	name = rarity+" "+type+skill;
	// Genero il valore di attacco in base al livello del nemico sconfitto
	int Vatk = (6*EntLvl) + rand()%EntLvl;
	Vatk *= DmgMult;
	// Genero l'arma
	Weapon<Player> GeneratedLoot;
	GeneratedLoot.SetStats(name,Vatk,SkillBuff,SkillAttr,LootScaleClass,ScaleAttr, Color);
	return GeneratedLoot;
	
}

/*!
* \fn      	Armor<Player> GenerateArmor(int EntLvl = 0)
* \brief    Genera un arma randomicamente
* \param    int EntLvl
* \return   Armor<Player>
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Armor<Player> GenerateArmor(int EntLvl)
{
	// Funzionamento analogo a GenerateWeapon
	string name, rarity, skill;
	Attribute SkillAttr;
	int SkillBuff;
	int value;
	float DefMult = 1;
	WORD Color;
	srand(time(NULL));
	value = rand()%100 + 1;
	value += EntLvl*2;
	if(value< 45 and value>=1)
	{
		rarity = "[COMMON]";
		Color = 0x0F;
		SkillBuff = 1;
	}
	else if(value< 75 and value>=45)
		 {
		 	rarity = "[UNCOMMON]";
		 	Color = 0x0A;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+1;
		 	DefMult = 1.3;
		 }
	else if(value< 87 and value>=75)
		 {
		 	rarity = "[RARE]";
		 	Color = 0x09;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+3;
		 	DefMult = 1.5;
		 }
	else if(value< 95 and value>=87)
		 {
		 	rarity = "[RELIC]";
		 	Color = 0x04;
		 	srand(time(NULL));
		 	SkillBuff = rand()%3+5;
		 	DefMult = 1.7;
		 }
	else if(value< 98 and value>=95)
		 {
		 	rarity = "[LEGENDARY]";
		 	Color = 0x05;
		 	srand(time(NULL));
		 	SkillBuff = rand()%2+7;
		 	DefMult = 1.9;
		 }
	else if(value>=98)
		 {
		 	rarity = "[EXOTIC]";
		 	Color = 0x06;
		 	SkillBuff = 9;
		 	DefMult = 2.1;
		 }
	
	srand(time(NULL));
	int Value = rand()%7+1;
	switch(Value)
	{
		case 1:
			SkillAttr = Str;
			skill = "Armatura a Piastre";
			break;	
		case 2:
			SkillAttr = Per;
			skill = "Vesti da Ranger";
			break;
		case 3:
			SkillAttr = End;
			skill = "Brigantina Rivettata";
			break;
		case 4:
			SkillAttr = Cha;
			skill = "Abiti del Bardo";
			break;
		case 5:
			SkillAttr = In;
			skill = "Vesti dell'Incantatore";
			break;
		case 6:
			SkillAttr = Agi;
			skill = "Armatura Imbottita";
			break;
		case 7:
			SkillAttr = Lck;
			skill = "Abito Elegante";
			break;
	}
	name = rarity+" "+skill;
	int Vdef = (8*EntLvl) + rand()%EntLvl;
	Vdef *= DefMult;
	Armor<Player> GeneratedLoot;
	GeneratedLoot.SetStats(name,Vdef,SkillBuff,SkillAttr, Color);
	return GeneratedLoot;
	
}

/*!
* \fn      	Delay(int Seconds)
* \brief    Permette di effettuare delle pause durante l'esecuzione del programma
* \param    int Seconds
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Delay(int Seconds)
{
	this_thread::sleep_for(chrono::milliseconds(Seconds*1000));
}

/*!
* \fn      	DrawLine(char LineTok, int Length)
* \brief    Stampa una linea di lunghezza e caratteri fissati
* \param    char LineTok
* \param    int Length
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void DrawLine(char LineTok, int Length)
{
	for(int i=0; i<Length; i++)
		cout<<LineTok;
}

/*!
* \fn      	DrawText(string Text, int Mode, int Size = LineSize)
* \brief    Permette di stampare del testo con varie impostazioni grafiche
* \param    string Text
* \param    int Mode
* \param 	int Size
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void DrawText(string Text, int Mode, int Size = LineSize)
{ 
	Text = " " + Text + " ";
	int limit = (Size-Text.length())/2;
	
	switch(Mode)
	{
		case 1:
			{
			//Testo centrato fra due linee
			DrawLine(char(0x0DF),Size);
			cout<<endl;
			
			for(int i = 0; i < limit; i++)
				Text = char(0xFF)+Text+char(0xFF);
			cout<<Text<<endl;
				
			DrawLine(char(0x0DC),Size);
			cout<<endl;
			break;
			}
		case 2:
			{
				//Testo in al centro di una linea
				for(int i = 0; i < limit; i++)
					Text = char(0xDB)+Text+char(0xDB);
				cout<<Text<<endl;
				break;
			}
		case 3:
			{
				//Text-In-A-Box™
				cout<<char(0x0DB);
				DrawLine(char(0x0DF),Size-2);
				cout<<char(0x0DB)<<endl;
				
				cout<<char(0x0DB);
				for(int i = 0; i < limit-1; i++)
					Text = char(0xFF)+Text+char(0xFF);
				cout<<Text;
				if(Text.length()%2!=0)
					cout<<char(0xFF);
				cout<<char(0x0DB)<<endl;
				
				cout<<char(0x0DB);
				DrawLine(char(0x0DC),Size-2);
				cout<<char(0x0DB)<<endl;
				break;
			}
		case 4:
			{
				//Testo centrato
				for(int i = 0; i < limit; i++)
					Text = char(0xFF)+Text+char(0xFF);	
				cout<<endl;	
			}
		default:
			//Testo normale
			cout<<Text<<endl;
			break;
	}
}

/*!
* \fn      	DrawSprite(string filename, WORD Color)
* \brief    Permette di stampare una sprite in ASCII-art da file
* \param    string filename
* \param    WORD Color
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void DrawSprite(string filename, WORD Color)
{
	// Assegno il colore della sprite cambiando il colore del testo stampato
	con.color(Color);
	ifstream ifs;
	string line = "";
	ifs.open(filename);
	while(getline(ifs,line))
		cout<<line<<endl;
	// Reset del colore
	con.color(0x07);
}

/*!
* \fn      	CreatePlayer()
* \brief    Permette la creazione del personaggio da parte del giocatore
* \return   Player
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Player CreatePlayer()
{
	bool Valid = false;
	string TempName;
	int TempStr;
	int TempPer;
	int TempEnd;
	int TempCha;
	int TempIn;
	int TempAgi;
	int TempLck;
	while(!Valid)
	{
		cout<<"Inserire un nome (max 16 caratteri): ";
		cin.ignore();
		getline(cin,TempName);
		// Controllo che il nome inserito non superi i 16 caratteri
		if(TempName.length()>16)
			cout<<"nome non valido"<<endl;
		else Valid = true;
		system("cls");
	}
	Valid = false;
	while(!Valid)
	{
		TempStr = 1;
		TempPer = 1;
		TempEnd = 1;
		TempCha = 1;
		TempIn = 1;
		TempAgi = 1;
		TempLck = 1;
		TempEnd = 1;
		int PA = 25;
		while(PA!= 0)
		{
			system("cls");
			con.color(0x0B);
			DrawText(TempName, 2, 120);
			cout<<endl;
			DrawText("Assegna i tuoi punti abilita'", 4, 120);
			DrawText("\"What makes you S.P.E.C.I.A.L. ?\"", 4, 120);
			con.color(0x07);
			cout<<endl<<endl;
			cout<<"[S] Strength:         "<<TempStr<<endl;
			cout<<"[P] Perception:       "<<TempPer<<endl;
			cout<<"[E] Endurance:        "<<TempEnd<<endl;
			cout<<"[C] Charisma:         "<<TempCha<<endl;
			cout<<"[I] Intelligence:     "<<TempIn<<endl;
			cout<<"[A] Agility:          "<<TempAgi<<endl;
			cout<<"[L] Luck:             "<<TempLck<<endl<<endl;
			cout<<"PA disponibili: "<<PA<<endl;
			char Choice;
			string UserChoice;
			// Se l'utente inserisce piu' di un carattere la scelta viene considerata non valida
			cin>>UserChoice;
			if(UserChoice.length()!=1)
				Choice = '0';
			else Choice = UserChoice[0];
			// Limito il livello massimo degli attributi a 10 durante l'inserimento	
			switch(Choice)
			{
				case 's':
					{
						if(TempStr<10)
						{
							TempStr++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'p':
					{
						if(TempPer<10)
						{
							TempPer++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'e':
					{
						if(TempEnd<10)
						{
							TempEnd++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'c':
					{
						if(TempCha<10)
						{
							TempCha++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'i':
					{
						if(TempIn<10)
						{
							TempIn++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'a':
					{
						if(TempAgi<10)
						{
							TempAgi++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				case 'l':
					{
						if(TempLck<10)
						{
							TempLck++;
							PA--;
						}else
						{
							cout<<"hai gia raggiunto il livello massimo!"<<endl;
							Delay(1);
						}
						break;
					}
				default:
					{
						cout<<"scelta non valida!"<<endl;
						Delay(1);
						break;
					}
			}
		}
		char Choice;
		bool Valid_2 = false;
		while(!Valid_2)
		{
			system("cls");
			con.color(0x0B);
			DrawText(TempName, 2, 120);
			cout<<endl;
			DrawText("Assegna i tuoi punti abilita'", 4, 120);
			DrawText("\"What makes you S.P.E.C.I.A.L. ?\"", 4, 120);
			con.color(0x07);
			cout<<endl<<endl;
			cout<<"[S] Strength:         "<<TempStr<<endl;
			cout<<"[P] Perception:       "<<TempPer<<endl;
			cout<<"[E] Endurance:        "<<TempEnd<<endl;
			cout<<"[C] Charisma:         "<<TempCha<<endl;
			cout<<"[I] Intelligence:     "<<TempIn<<endl;
			cout<<"[A] Agility:          "<<TempAgi<<endl;
			cout<<"[L] Luck:             "<<TempLck<<endl<<endl;
			cout<<"PA disponibili: "<<PA<<endl;
			Delay(1);
			cout<<"Confermare la selezione? [Y/N]"<<endl;
			cin>>Choice;
			switch(Choice)
			{
				case 'y':
					Valid_2 = true;
					Valid = true;
					break;
				case 'n':
					Valid_2 = true;
					cout<<"reset..."<<endl;
					break;
				default:
					cout<<"Scelta non valida!"<<endl;
					break;
			}
		}
	}
	int BaseDef = 0;
	int BaseAtk = 0;
	// Creo il giocatore
	Player TempPlayer(BaseDef,BaseAtk,TempName,false,TempStr,TempPer,TempEnd,TempCha,TempIn,TempAgi,TempLck);
	
	// Creo e assegno l'arma e l'armatura base
	Weapon<Player> weapon2;
	weapon2.SetStats("[STARTER] Spada spezzata", 4, 0, NO, E, NO);
	Armor<Player> armor2;
	armor2.SetStats("[STARTER] Vecchia Tunica", 4, 0, NO);
	TempPlayer.SetCurrentWeapon(weapon2);
	TempPlayer.SetCurrentArmor(armor2);
	SaveToFile(TempPlayer);
	
	return TempPlayer;
}

/*!
* \fn      	GenerateNPC()
* \brief    Permette la generazione automatica di un personaggio gestito dal computer (NPC)
* \return   Player
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Player GenerateNPC()
{
	if(FloorCount%5==0)
		EnemyBaseLvl++;
		
	int Vstr, Vper, Vend, Vcha, Vin, Vagi, Vlck;
	int Lb, Sp;
	int hp, Vatk, Vdef;
	srand(time(NULL));
	// Genero i valori degli attributi, di attacco e difesa del nemico in base al livello base
	if(EnemyBaseLvl<=10)
	{
		if(EnemyBaseLvl == 1)
			Lb = 1;
		else Lb = EnemyBaseLvl/2;
		
		Sp = EnemyBaseLvl-Lb+1;
	}else if(EnemyBaseLvl>10 and EnemyBaseLvl <= 19)
	{
		Lb = 7+((EnemyBaseLvl-10)/4);
		Sp = 10-Lb+1;
	}else
	{
		Lb = 10;
		Sp = 1;
	}
	/** Il numero di punti vita del nemico dipende anch'esso dal livello,
	* i nemici rispetto al giocatore salgono di livello con minore frequenza ma aumentano piu' rapidamente i propri punti ferita
	*/
	hp = 100*EnemyBaseLvl/2;
	
		Vatk = 8*EnemyBaseLvl+rand()%EnemyBaseLvl;
		Vdef = 9*EnemyBaseLvl+rand()%EnemyBaseLvl;
		Vstr = rand() % Sp + Lb;
		Vper = rand() % Sp + Lb;
		Vend = rand() % Sp + Lb;
		Vcha = rand() % Sp + Lb;
		Vin = rand() % Sp + Lb;
		Vagi = rand() % Sp + Lb;
		Vlck = rand() % Sp + Lb;
		
		Player TempNPC(Vdef, Vatk, "Enemy NPC", true, Vstr, Vper, Vend, Vcha, Vin, Vagi, Vlck);
		// Imposto il cap dei punti ferita
		TempNPC.SetHpCap(hp);
		TempNPC.SetHp(TempNPC.GetHpCap());
		TempNPC.PlayerLevel.SetLevel(EnemyBaseLvl);
		return TempNPC;
	
}

//----------PLAYER--------------------------------------------

/*!
* \fn      	Player::Player(int Vdef, int Vatk, string Vname, bool Auto, int Vstr, int Vper, int Vend, int Vcha, int Vin, int Vagi, int Vlck)
* \brief    Costruttore della classe Player. Inizializza le variabili.
* \param 	int Vdef
* \param 	int Vatk
* \param 	string Vname
* \param 	bool Auto
* \param 	int Vstr
* \param 	int Vper
* \param 	int Vend
* \param 	int Vcha
* \param 	int Vin
* \param 	int Vagi
* \param 	int Vlck
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Player::Player(int Vdef, int Vatk, string Vname, bool Auto, int Vstr, int Vper, int Vend, int Vcha, int Vin, int Vagi, int Vlck)
{
	Alive = true;
	name = Vname;
	hp = 100;
	def = Vdef;
	atk = Vatk;
	str = Vstr;
	per = Vper;
	end = Vend;
	cha = Vcha;
	in = Vin;
	agi = Vagi;
	lck = Vlck;
	GuardStr = 100;
	BOT = Auto;
	InGuard = false;
	HealCap = 5;
	HealCount = HealCap;
	Coins = 0;
	HealMult = 0.1;
	crit_mult = 2;
}

/*!
* \fn      	Player::ShowStats()
* \brief    Mostra le statistiche del giocatore / NPC
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Player::ShowStats()
{
	DrawText(name, 3, LineSize);
	cout<<"HP: "<<(hp < 0 ? 0 : hp)<<endl;
	cout<<"DEF: "<<def<<endl;
	cout<<"ATK: "<<atk<<endl;
	cout<<"str: "<<str<<endl;
	cout<<"per: "<<per<<endl;
	cout<<"end: "<<end<<endl;
	cout<<"cha: "<<cha<<endl;
	cout<<"in:  "<<in<<endl;
	cout<<"agi: "<<agi<<endl;
	cout<<"lck: "<<lck<<endl;
	DrawLine(char(0x0DC), LineSize);
	cout<<endl;
}

/*!
* \fn      	Player::Attack(Player &Target)
* \brief    Permette di effettuare un attacco. Calcola il danno in uscita e controlla se il bersaglio e' ancora in vita dopo essere stato attaccato
* \param	Player &Target
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Player::Attack(Player &Target)
{
	float attack_DMG;
	// Calcolo il danno
	attack_DMG = atk*(100.0/(100.0+Target.def*5));
	srand(time(NULL));
	// Genero un valore per la probabilità di colpo critico
	int crit_ch = rand() % 15 + 1;
	// In base alla percezione viene deciso se effettuare o no il colpo critico
	if(crit_ch < per)
	{
		// Moltiplico il danno per il moltiplicatore del critico
		// Aumento il moltiplicatore del critico in base al carisma
		attack_DMG *= crit_mult + cha;
		cout<<"Colpo critico! Danno x"<<crit_mult + cha<<"!"<<endl;	
	}
	// Il danno viene ridotto in base alla resistenza
	float dmg_red = (10.0-Target.end/2.0)/10.0;
	attack_DMG *= dmg_red;
	attack_DMG = (int)attack_DMG;
	
	// La probabilità di colpire e' generata casualmente ed incrementata in base alla fortuna	
	int hit_ch = (rand() % 20 + 1) + (lck/2);
	// In base all'agilita' viene deciso se il nemico schiva l'attacco
	if(hit_ch < Target.agi)
	{
		attack_DMG = 0;
		cout<<Target.GetName()<<" schiva l'attacco!"<<endl;
	}else cout<<"Inflitti "<<attack_DMG<<" danni a "<<Target.GetName()<<"!"<<endl;
		
	attack_DMG > 0 ? Target.hp -= attack_DMG : Target.hp -= 0;
	// Controllo se dopo l'attacco i punti ferita dell'avversario sono stati azzerati
	if(Target.hp <= 0)
		Target.Alive = false;

}

/*!
* \fn      	Player::Guard()
* \brief    Modifica la difesa del personaggio in guardia
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Player::Guard()
{
	// Se il personaggio e' in guardia incremento la difesa, altrimenti la decremento
	if(GetGuard())
		def += GetGuardStr();
	else if(!GetGuard())
		def -= GetGuardStr();
}

/*!
* \fn      	Player::GetGuardStr()
* \brief    Calcola l'incremento alla difesa dato dallo stato di guardia
* \return   float
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
int Player::GetGuardStr()
{
	int Value;
	// L'incremento alla difesa dato dalla guardia dipende dalla resistenza e dal livello del personaggio
	Value = (GuardStr + end * 10) * PlayerLevel.GetLevel();
	return Value;
}

/*!
* \fn      	Player::DrawHpBar()
* \brief    Stampa a schermo la barra dei punti ferita di un giocatore / NPC
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Player::DrawHpBar()
{
	int i;
	// Calcolo la percentuale di riempimento della barra
	int Perc = hp*100/HpCap;
	cout<<"      HP: "<<char(186)<<" ";
	con.color(0x0C);
	for(i=0;i<Perc;i++)
		cout<<char(219);
	con.color(0x07);
	for(i;i<100;i++)
		cout<<char(176);
	cout<<" "<<char(186);
	cout<<endl<<endl;
}

/*!
* \fn      	Player::AutoChoice(Player TargetPlayer, Player CurrentPlayer)
* \brief    Permette di effettuare in maniera automatica la scelta dell'azione da eseguire durante un turno
* \param	Player TargetPlayer
* \param	Player CurrentPlayer
* \return   char
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
char Player::AutoChoice(Player TargetPlayer, Player CurrentPlayer)
{
	// Se il nemico e' sopra il 20% dei punti ferita massimi...
	if(TargetPlayer.GetHp() >= TargetPlayer.GetHpCap()*0.2)
	{
		// ... Se ci si trova oltre il 40% dei punti ferita massimi...
		if(CurrentPlayer.GetHp() >= CurrentPlayer.GetHpCap()*0.4)
		// ...attacca
			return '1';
		// Altrimenti se ci si trova oltre il 20% dei punti ferita massimi...
		else if(CurrentPlayer.GetHp() >= CurrentPlayer.GetHpCap()*0.2)
				{
					srand(time(NULL));
					int Value = rand()%2;
					if(Value == 1)
					// ... difenditi
						return '2';
					// ... oppure attacca
					else return '1';
				 // Altrimenti se hai ancora delle pozioni...	
				}else if(CurrentPlayer.GetHealCount() > 0)
					  // ... curati
							return '3';
						// Altrimenti difenditi
						else return '2';
	}else return '1';// Altrimenti attacca
	
}

void Player::SetCurrentWeapon(Weapon<Player> NewWeapon)
{
	// Rimuovo gli effetti dell'arma precedente
	CurrentWeapon.ApplyEffect(*this, true);
	// Assegno la nuova arma
	CurrentWeapon = NewWeapon;
	// Applico gli effetti della nuova arma
	CurrentWeapon.ApplyEffect(*this, false);	
}

void Player::SetCurrentArmor(Armor<Player> NewArmor)
{
	// Rimuovo gli effetti dell'armatura precedente
	CurrentArmor.ApplyEffect(*this, true);
	// Assegno la nuova armatura
	CurrentArmor = NewArmor;
	// Applico gli effetti della nuova armatura
	CurrentArmor.ApplyEffect(*this, false);	
}

/*!
* \fn      	Player::GetAttributeValue(Attribute attr)
* \brief    Restituisce il valore di un attributo
* \return   int
* \param	Attribute attr
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
int Player::GetAttributeValue(Attribute attr)
{
	switch(attr)
	{
		case Attribute::Str:
			return str;
			break;
		case Attribute::Per:
			return per;
			break;
		case Attribute::End:
			return end;
			break;
		case Attribute::Cha:
			return cha;
			break;
		case Attribute::In:
			return in;
			break;
		case Attribute::Agi:
			return agi;
			break;
		case Attribute::Lck:
			return lck;
			break;
		default:
			return 0;
			break;	
	}
}

/*!
* \fn      	Player::SetAttributeValue(Attribute attr, int Vattr)
* \brief    Imposta il valore di un attributo
* \param	Attribute attr
* \param	int Vattr
* \return   int
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Player::SetAttributeValue(Attribute attr, int Vattr)
{
		switch(attr)
		{
			case Attribute::Str:
				if(str+Vattr>=10)
					str = 10;
				else
					str += Vattr;
				break;
			case Attribute::Per:
				if(per+Vattr>=10)
					per = 10;
				else
					per += Vattr;
				break;
			case Attribute::End:
				if(end+Vattr>=10)
					end = 10;
				else
					end += Vattr;
				break;
			case Attribute::Cha:
				if(cha+Vattr>=10)
					cha = 10;
				else
					cha += Vattr;
				break;
			case Attribute::In:
				if(in+Vattr>=10)
					in = 10;
				else
					in += Vattr;
				break;
			case Attribute::Agi:
				if(agi+Vattr>=10)
					agi = 10;
				else
					agi += Vattr;
				break;
			case Attribute::Lck:
				if(lck+Vattr>=10)
					lck = 10;
				else
					lck += Vattr;
				break;
			default:
				break;	
		}
}

//--------------------TURN----------------------

/*!
* \fn      	Turn::Turn(Player &CurrentPlayer, Player &TargetPlayer)
* \brief    Costruttore della classe Turn. Stampa il nome del giocatore attivo e prende in input l'azione da eseguire
* \param	Player &CurrentPlayer
* \param	Player &TargetPlayer
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Turn::Turn(Player &CurrentPlayer, Player &TargetPlayer)
{
	DrawText(CurrentPlayer.GetName(),2,120);
	GetAction(CurrentPlayer, TargetPlayer);
}

/*!
* \fn      	Turn::GetAction(Player &CurrentPlayer, Player &TargetPlayer)
* \brief    Permette al giocatore di scegliere l'azione da eseguire durante il turno e la esegue.
* \param	Player &CurrentPlayer
* \param	Player &TargetPlayer
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Turn::GetAction(Player &CurrentPlayer, Player &TargetPlayer)
{
	char Choice;
	// Controllo se il personaggio non e' un BOT
	if(!CurrentPlayer.IsBot())
	{
		bool Valid = false;
		string Text;
		// Stampo le statistiche del personaggio
		Text = "LV: " + to_string(CurrentPlayer.PlayerLevel.GetLevel());
		DrawText(Text, 4,120);
		Text = "ATK: " + to_string(CurrentPlayer.GetAtk()) + " - DEF: " + to_string(CurrentPlayer.GetDef()) + " - HP: " + to_string(CurrentPlayer.GetHp());
		DrawText(Text, 4,120);
		Text = "S: " + to_string(CurrentPlayer.GetAttributeValue(Str)) + " - P: "+ to_string(CurrentPlayer.GetAttributeValue(Per)) + " - E: "+ to_string(CurrentPlayer.GetAttributeValue(End)) + " - C: "+ to_string(CurrentPlayer.GetAttributeValue(Cha)) + " - I: " + to_string(CurrentPlayer.GetAttributeValue(In)) + " - A: " + to_string(CurrentPlayer.GetAttributeValue(Agi)) +" - L: " + to_string(CurrentPlayer.GetAttributeValue(Lck));
		DrawText(Text, 4,120);
		cout<<endl;
		CurrentPlayer.DrawHpBar();
		// Stampo il menu azione
		Text = "[1] Attacca    [2] Difenditi    [3] Curati (x" + to_string(CurrentPlayer.GetHealCount()) + ")";
		DrawText(Text, 1,120);
		string UserChoice;
		// Ripeto l'input finche' la scelta non e' valida
		while(!Valid)
		{
			cin>>UserChoice;
			if(UserChoice.length()!=1)
			Choice = '0';
			else Choice = UserChoice[0];
			if(Choice != '1' and Choice != '2' and Choice != '3' and Choice != '4')
			{
				cout<<"Scelta non valida!"<<endl;
			}
			else Valid = true;
		}
		cout<<endl;
		
	}else if(CurrentPlayer.IsBot())
		Choice = (char)CurrentPlayer.AutoChoice(TargetPlayer, CurrentPlayer);
		
	switch(Choice)
	{
		case '1':
			{
				cout<<CurrentPlayer.GetName()<<" Attacca ---> "<<TargetPlayer.GetName()<<" ! "<<endl<<endl;
				// Effettuo l'attacco
				CurrentPlayer.Attack(TargetPlayer);
				// Se l'avversario e' in guardia...
				if(TargetPlayer.GetGuard())
				{
					// ...imposto la guardia a false...
					TargetPlayer.SetGuard(false);
					// ...e chiamo la funzione Guard per decrementare la difesa
					TargetPlayer.Guard();
				}
				break;
			}
		case '2':
			{
				cout<<CurrentPlayer.GetName()<<" alza la guardia!"<<endl;
				// Se non ci si trova in guardia...
				if(!CurrentPlayer.GetGuard())
				{
					// ...imposto la guardia a true...
				CurrentPlayer.SetGuard(true);
				// ... e chiamo la funzione Guard per incrementare la difesa
				CurrentPlayer.Guard();
				}
				break;
			}
		case '3':
			{
				// Controllo se il numero di pozioni disponibili e' maggiore di zero
				if(CurrentPlayer.GetHealCount()>0)
				{
					cout<<CurrentPlayer.GetName()<<" si cura usando una pozione!"<<endl;
					// Curo l'utilizzatore
					CurrentPlayer.Heal(CurrentPlayer.GetHpCap()*CurrentPlayer.GetHealMult());
					// Decremento il numero di pozioni di cura disponibili
					CurrentPlayer.SetHealCount(CurrentPlayer.GetHealCount()-1);
				}else cout<<CurrentPlayer.GetName()<<" ha terminato le pozioni!"<<endl;
				break;
			}
		default:
			{
				cout<<"Scelta non Valida!"<<endl;
				break;
			}
				
	}

	
}

//-----------------------FLOOR---------------------------------

/*!
* \fn      	Floor::Floor()
* \brief    Costruttore della classe Floor. Inizializza il conteggio dei turni.
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Floor::Floor()
{
	SpriteNum = rand()%3+6;
	TurnCount = 1;
}

/*!
* \fn      	Floor::Fight(Player &player1)
* \brief    Gestisce il combattimento ed il rilascio degli oggetti, monete ed esperienza.
* \param	Player &player1
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Floor::Fight(Player &player1)
{	
	// Il combattimento continua finche' il giocatore o l'NPC sono in vita
	while(player1.IsAlive() and EnemyNPC.IsAlive())
	{
		// Stampo la finestra di gioco
		DrawWindow(EnemyNPC,player1);
		cout<<endl<<endl;
		// Incremento il conteggio dei turni
		TurnCount++;
		// I turni pari sono del giocatore, quelli dispari dell'NPC
		TurnCount % 2 == 0 ? Turn(player1, EnemyNPC) : Turn(EnemyNPC, player1);
		
		Delay(2);
	}
	DrawWindow(EnemyNPC,player1);
	
	int Xp;
	// Livello dell'NPC
	int Mlev = EnemyNPC.PlayerLevel.GetLevel();
	// Livello del giocatore
	int Clev = player1.PlayerLevel.GetLevel();
	// Calcolo le monete rilasciate del nemico in base al suo livello
	if(player1.IsAlive())
	{
		// Calcolo i punti esperienza base lasciati dal nemico
		int BaseXp = 0.4 * pow(Mlev,3) + 0.8 * pow(Mlev,2) + 2 * Mlev;
		// Calcolo la differenza di livello fra il giocatore ed il nemico
		int Diff;
		if(Mlev-Clev>=0)
			Diff = Mlev-Clev;
		else Diff=0;
		// Calcolo l'esperienza ottenuta incrementandola se il giocatore e' di livello inferiore al nemico
		Xp = (BaseXp/2)*(1+0.05*(Diff));
		Xp *= (1+player1.GetAttributeValue(In)/10);
		cout<<"Ottenuti "<<Xp<<" XP da "<<EnemyNPC.GetName()<<"!"<<endl;
		int CoinDrop;
		CoinDrop = 100 * EnemyNPC.PlayerLevel.GetLevel();
		cout<<"Ottenute "<<CoinDrop<<" Monete da "<<EnemyNPC.GetName()<<"!"<<endl;
		player1.AddCoins(CoinDrop);
		cout<<"Monete totali: "<<player1.GetCoins();
		con.color(0x0E);
		cout<<" G"<<endl;
		con.color(0x07);
		
		bool Adv = false;
		Adv = player1.PlayerLevel.XpAdd(Xp);
		player1.PlayerLevel.ShowPercBar();
		// Se il giocatore avanza di livello incremento il limite dei punti ferita e re imposto i punti ferita
		if(Adv)
			player1.SetHpCap(player1.GetHpCap()+player1.GetHpCap()*player1.PlayerLevel.GetLevel()/20);
	}
		
	// Calcolo la probabilita' di trovare un arma o un armatura
	int Value;
	srand(time(NULL));
	Value = rand()%101;
	int DropR;
	// Incremento la probabilita' di trovare un arma o un armatura in base alla fortuna
	DropR = 40 + (player1.GetAttributeValue(Lck) * 2);
	if(Value <= DropR and player1.IsAlive())
	{
		// Scelgo se generare un arma o un armatura
		int Type = rand()%2;
		if(Type == 1)
		{
			Weapon<Player> NewWeapon = GenerateWeapon(Mlev);
			cout<<"Hai trovato un arma!"<<endl<<endl;
			NewWeapon.ShowStats();
			cout<<endl<<endl<<"Arma attuale:"<<endl<<endl;
			player1.CurrentWeapon.ShowStats();
			cout<<endl<<"Equipaggiare la nuova arma? [Y/N]"<<endl;
			char Choice;
			string UserChoice;
			bool valid = false;
			while(!valid)
			{
				cin>>UserChoice;
				if(UserChoice.length()!=1)
				Choice = '0';
				else Choice = UserChoice[0];
			
				switch(Choice)
				{
					case 'y':
						player1.SetCurrentWeapon(NewWeapon);
						cout<<"switched"<<endl;
						valid = true;
						break;
					case 'n':
						cout<<"not switched"<<endl;
						valid = true;
						break;
					default:
						cout<<"scelta non valida!"<<endl;
						break;
				}
			}	
		}else if(Type == 0)
		{
			Armor<Player> NewArmor = GenerateArmor(Mlev);
			cout<<"Hai trovato un armatura!"<<endl;
			NewArmor.ShowStats();
			cout<<endl<<endl<<"Armatura attuale:"<<endl<<endl;
			player1.CurrentArmor.ShowStats();
			cout<<endl<<"Equipaggiare la nuova armatura? [Y/N]"<<endl;
			char Choice;
			string UserChoice;
			bool valid = false;
			while(!valid)
			{
				cin>>UserChoice;
				if(UserChoice.length()!=1)
				Choice = '0';
				else Choice = UserChoice[0];
			
				switch(Choice)
				{
					case 'y':
						player1.SetCurrentArmor(NewArmor);
						cout<<"Cambio effettuato"<<endl;
						valid = true;
						break;
					case 'n':
						cout<<"Cambio non effettuato"<<endl;
						valid = true;
						break;
					default:
						cout<<"scelta non valida!"<<endl;
						break;
				}
			}	
		}
	}
	
	// Incremento il piano
	FloorCount++;
}

/*!
* \fn      	Floor::DrawWindow(Player playerP, Player playerN)
* \brief    Stampa a schermo le informazioni di interesse al giocatore
* \param	Player playerP
* \param	Player playerN
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Floor::DrawWindow(Player playerP, Player playerN)
{
	system("cls");
	string RoomText;
	con.color( 0x0B );
	// Stampo il piano e il turno attuale
	RoomText = "PIANO: " + to_string(FloorCount) + " ,TURNO: " + to_string(TurnCount); 
	DrawText(RoomText, 2, 120);
	con.color( 0x07 );
	cout<<endl<<endl;
	DrawText(playerP.GetName(),3, 120);
	string SpriteName;
	// Stampo la sprite del nemico
	SpriteName = "Sprite" + to_string(SpriteNum) + ".txt";
	DrawSprite(SpriteName, 0x0A);
	cout<<endl<<endl;
	playerP.DrawHpBar();
}

//----------GAME----------------------

/*!
* \fn      	Game::Game()
* \brief    Costruttore della classe Game. Inizializza il conteggio dei piani
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
Game::Game(){FloorCount = 1;}// Re imposto il conteggio dei piani

/*!
* \fn      	Game::Start(Player &player1)
* \brief    Elabora il negozio pre partita e la partita.
* \param	Player &player1
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Game::Start(Player &player1)
{	
	bool GetOut = false;
	char Selected;
	while(!GetOut)
	{
			system("cls");
			// I prezzi dei potenziamenti vengono scontati in base al carisma
			float Discount = player1.GetAttributeValue(Cha)/20.0;
			// Prezzi
			int Prices[3] = {(int)(300-300*Discount), (int)(450-450*Discount), (int)(3000-3000*Discount)};
			DrawSprite("Shop.txt", 0x06);
			con.color(0x06);
			DrawText("Spendi qui le tue monete per potenziare "+player1.GetName(),4,120);
			con.color(0x0F);
			cout<<endl<<endl;
			cout<<"[1] Potenzia cura                       - "<<Prices[0]<<" ";
			con.color(0x0E);
			cout<<"G"<<endl;
			con.color(0x0F);
			cout<<"[2] Incrementa cure disponibili         - "<<Prices[1]<<" ";
			con.color(0x0E);
			cout<<"G"<<endl;
			con.color(0x0F);
			cout<<"[3] Acquista un PA                      - "<<Prices[2]<<" ";
			con.color(0x0E);
			cout<<"G"<<endl;
			con.color(0x0F);
			cout<<"[";
			con.color(0x04);
			cout<<"X";
			con.color(0x0F);
			cout<<"] ESCI"<<endl;
			cout<<"MONETE: "<<player1.GetCoins();
			con.color(0x0E);
			cout<<" G"<<endl;
			con.color(0x0F);
			
			string UserChoice;
			cin>>UserChoice;
			if(UserChoice.length()!=1)
				Selected = '0';
			else Selected = UserChoice[0];
			
			switch(Selected)
			{
				case '1':
					{
						if(player1.GetCoins()>=Prices[0] and player1.GetHealMult() < 1.0)
						{
							// Decrememnto le monete
							player1.AddCoins(-Prices[0]);
							// Modifico il moltiplicatore delle cure
							player1.SetHealMult(player1.GetHealMult()+0.1);
							cout<<"Moltiplicatore delle cure: "<<player1.GetHealMult()<<endl;
						}else if(player1.GetHealMult() >= 1.0)// Il moltiplicatore non puo' andare oltre 1
						{
							cout<<"Hai gia raggiunto il livello massimo! "<<player1.GetHealMult()<<endl;
						}else if(player1.GetCoins()<Prices[0])
						{
							cout<<"Monete insufficienti!"<<endl;
						}
						break;
					}
				case '2':
					{
						if(player1.GetCoins()>=Prices[1])
						{
							player1.AddCoins(-Prices[1]);
							// Modifico il numero massimo delle cure
							player1.SetHealCap(player1.GetHealCap()+1);
							cout<<"Pozioni: "<<player1.GetHealCap()<<endl;
						}else cout<<"Monete insufficienti!"<<endl;
						break;
					}
				case '3':
					{
						if(player1.GetCoins()>=Prices[2])
						{
							system("cls");
							cout<<endl<<endl;
							con.color(0x0B);//B-6
							DrawText("Scegli un attributo da migliorare",2,120);
							con.color(0x0F);
							cout<<endl;
							cout<<"[S] Strength,       attuale: "<<player1.GetAttributeValue(Str)<<endl;
							cout<<"[P] Perception,     attuale: "<<player1.GetAttributeValue(Per)<<endl;
							cout<<"[E] Endurance,      attuale: "<<player1.GetAttributeValue(End)<<endl;
							cout<<"[C] Charisma,       attuale: "<<player1.GetAttributeValue(Cha)<<endl;
							cout<<"[I] Intelligence,   attuale: "<<player1.GetAttributeValue(In)<<endl;
							cout<<"[A] Agility,        attuale: "<<player1.GetAttributeValue(Agi)<<endl;
							cout<<"[L] Luck,           attuale: "<<player1.GetAttributeValue(Lck)<<endl<<endl;
							
							// Input dell'attributo da migliorare
							char Choice;
							string UserChoice;
							cin>>UserChoice;
							if(UserChoice.length()!=1)
								Choice = '0';
							else Choice = UserChoice[0];
							
							switch(Choice)
							{
								case 's':
									{
										// Controllo che l'attributo non sia gia' a valore 10
										if(player1.GetAttributeValue(Str)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(Str, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'p':
									{
										if(player1.GetAttributeValue(Per)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(Per, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'e':
									{
										if(player1.GetAttributeValue(End)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(End, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'c':
									{
										if(player1.GetAttributeValue(Cha)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(Cha, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'i':
									{
										if(player1.GetAttributeValue(In)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(In, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'a':
									{
										if(player1.GetAttributeValue(Agi)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(Agi, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								case 'l':
									{
										if(player1.GetAttributeValue(Lck)<10)
										{
											player1.AddCoins(-Prices[2]);
											player1.SetAttributeValue(Lck, 1);
										}else
										{
											cout<<"hai gia raggiunto il livello massimo!"<<endl;
											Delay(1);
										}
										break;
									}
								default:
									{
										cout<<"scelta non valida!"<<endl;
										Delay(1);
										break;
									}
							}
						}else cout<<"Monete insufficienti!"<<endl;
						break;
					}
				case 'x':
					{
						GetOut = true;
						break;
					}
				default:
					{
						cout<<"Scelta non valida!"<<endl;
						Delay(1.5);
						break;
					}
			}
			// Salvo il personaggio su file...
			SaveToFile(player1);
			Delay(2);
	}
	bool Reloaded = false;
	// ... e lo ricarico
	player1 = LoadFromFile(player1.GetName(), Reloaded);
	if(!Reloaded)
		cout<<"ERRORE"<<endl;
	// Reimposto le pozioni disponibili al massimo (cure aumentate al negozio?)
	player1.SetHealCount(player1.GetHealCap());
	
	// Finche' il personaggio controllato dal giocatore e' in vita e fintanto che si desidera continuare la partita procede
	while(Continue and player1.IsAlive())
	{
		// Genero un nuovo piano...
		Floor NewFloor;
		// ...ed avvio il combattimento
		NewFloor.Fight(player1);
		
		if(player1.IsAlive())
		{
			bool Valid = false;
			char Choice;
			string UserChoice;
			
			while(!Valid)
			{
				Delay(2);
				system("cls");
				cout<<endl<<"PROCEDERE AL PROSSIMO PIANO? [Y/N]"<<endl;
				cin>>UserChoice;
				if(UserChoice.length()!=1)
					Choice = '0';
				else Choice = UserChoice[0];
				
				switch(Choice)
				{
					case 'y':
						{
							Continue = true;
							Valid = true;
							break;
						}
					case 'n':
						{
							Continue = false;
							Valid = true;
							break;
						}
					default:
						{
							cout<<"Scelta non valida!"<<endl;
							break;
						}
				}
			}
		}
	}
	
	Delay(0.5);
	
	// Pulisco la schermata ed attuo il GameOver
	system("cls");
	GameOver(player1);
}

/*!
* \fn      	Game::GameOver(Player &player1)
* \brief    Gestisce il reset dei parametri di interesse del giocatore al termine della partita
* \param	Player &player1
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void Game::GameOver(Player &player1)
{
	// Reset di tutte le statistiche di interesse del giocatore e reimposto l'equipaggiamento iniziale
	system("cls");
	player1.SetHpCap(100);
	player1.SetHp(player1.GetHpCap());
	player1.SetHealCount(player1.GetHealCap());
	player1.SetAlive(true);
	player1.PlayerLevel.SetCurrentXp(0);
	player1.PlayerLevel.SetLevel(0);
	player1.PlayerLevel.AdvLvl();
	Weapon<Player> weapon2;
	weapon2.SetStats("[STARTER] Spada Spezzata", 4, 0, NO, E, NO);
	Armor<Player> armor2;
	armor2.SetStats("[STARTER] Vecchia Tunica", 4, 0, NO);
	player1.SetCurrentWeapon(weapon2);
	player1.SetCurrentArmor(armor2);
	SaveToFile(player1);
	EnemyBaseLvl = 1;
	DrawSprite("GameOver.txt", 0x04);
}

//--------------------------------------------LEVELSYS----------------------------------------------------

/*!
* \fn      	LevelSys::LevelSys()
* \brief    Costruttore della classe LevelSys. Inizializza i parametri.
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
LevelSys::LevelSys()
{
	CurrentLvl = 1;
	CurrentXp = 0;
	// Calcolo l'esperienza necessaria ad avanzare al prossimo livello
	XpToNext = 0.4 * pow(CurrentLvl,3) + 0.8 * pow(CurrentLvl,2) + 2 * CurrentLvl;
}

/*!
* \fn      	LevelSys::AdvLvl()
* \brief    Gestisce l'avanzamento di livello
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void LevelSys::AdvLvl()
{
	// Avanza di livello e ri calcola la soglia per il prossimo livello
	CurrentLvl++;
	XpToNext = 0.4 * pow(CurrentLvl,3) + 0.8 * pow(CurrentLvl,2) + 2 * CurrentLvl;
	// Azzero l'esperienza corrente
	CurrentXp = 0;
}

/*!
* \fn      	LevelSys::XpAdd(int XpAmount)
* \brief    Gestisce l'acquisizione di esperienza
* \param	int XpAmount
* \return   bool
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
bool LevelSys::XpAdd(int XpAmount)
{
	bool Adv = false;
	bool Overflow = true;
	// Se l'esperienza ottenuta va oltre quella necessaria a salire di livello piu' volte ripeto l'avanzamento
	while(Overflow)
	{
		if(XpAmount + CurrentXp > XpToNext)
		{
			XpAmount = (XpAmount + CurrentXp) - XpToNext;
			AdvLvl();
			//restituisco true se si e' avanzati di livello almeno una volta
			Adv = true;
		}else
		{
			CurrentXp += XpAmount;
			Overflow = false;
		}
	}
	return Adv;
}

/*!
* \fn      	LevelSys::ShowPercBar()
* \brief    Mostra la barra di avanzamento del livello attuale
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
void LevelSys::ShowPercBar()
{
	int Perc = CurrentXp*100/XpToNext;
	cout<<" LV: "<<CurrentLvl<<"  "<<char(17)<<" ";
	con.color(0x0B);
	for(int i = 0; i<Perc; i++)
		cout<<char(254);
	con.color(0x07);
	for(int i = 0; i<100-Perc;i++)
		cout<<" ";
		cout<<" "<<char(16)<<endl;
}

//---------------------------------------WEAPON----------------------------------------

/*!
* \fn      	Weapon<P>::ApplyEffect(P &User, bool Removing)
* \brief    Applica gli effetti dell'arma al giocatore
* \param	P &User
* \param	bool Removing
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Weapon<P>::ApplyEffect(P &User, bool Removing)
{
	int ctrl = 0;
	// Rimuovere gli effetti equivale ad applicare gli effetti opposti
	if(Removing)
		ctrl = -1;
	else if(!Removing)
			ctrl = 1;
	
	int UserAttributeValue = User.GetAttributeValue(VarType);
	if(UserAttributeValue + ctrl*VarAmount >= 10)
		VarAmount = 10 - UserAttributeValue;

	User.SetAttributeValue(VarType, ctrl*VarAmount);
	
		
	int AttrVal = User.GetAttributeValue(ScaleAttribute);
	int AttackRating = VarAtk;
	// Calcolo il valore di attacco in base allo scaling
	AttackRating += VarAtk*AttrVal/(8.0 - (0.167*(ScaleClass+1)));
	AttackRating *= (1+User.GetAttributeValue(Str)/10.0);
	AttackRating = (int)AttackRating;
	User.SetAtk(AttackRating);
}

/*!
* \fn      	Weapon<P>::SetStats(string Vname, int Vatk, int Vamount, Attribute Vtype, Rating ScaleCl, Attribute ScaleAttr, WORD Color)
* \brief    Imposta le statistiche dell'arma
* \param	string Vname
* \param	int Vatk
* \param	int Vamount
* \param	Attribute Vtype
* \param	Rating ScaleCl
* \param	Attribute ScaleAttribute
* \param	WORD Color
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Weapon<P>::SetStats(string Vname, int Vatk, int Vamount, Attribute Vtype, Rating ScaleCl, Attribute ScaleAttr, WORD Color)
{
	Name = Vname;
	VarAtk = Vatk;
	VarAmount = Vamount;
	VarType = Vtype;
	ScaleClass = ScaleCl;
	ScaleAttribute = ScaleAttr;
	NameColor = Color;
}

/*!
* \fn      	Weapon<P>::ShowStats()
* \brief    Mostra le statistiche dell'arma
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Weapon<P>::ShowStats()
{
	cout<<"------------------------------"<<endl;
	con.color(NameColor);
	cout<<Name<<endl;
	con.color(0x07);
	cout<<"ATK: "<<VarAtk<<endl;
	cout<<"+"<<VarAmount<<" BOOST A: "<<ReturnAttribute(VarType)<<endl;
	cout<<"SCALA: "<<ReturnRating(ScaleClass)<<" SU "<<ReturnAttribute(ScaleAttribute)<<endl;
	cout<<"------------------------------"<<endl;
}

//---------------------------------------ARMOR------------------------------------------------------------

/*!
* \fn      	Weapon<P>::ApplyEffect(P &User, bool Removing)
* \brief    Applica gli effetti dell'arma al giocatore
* \param	P &User
* \param	bool Removing
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Armor<P>::ApplyEffect(P &User, bool Removing)
{
	int ctrl = 0;
	
	if(Removing)
		ctrl = -1;
	else if(!Removing)
			ctrl = 1;
	
	int UserAttributeValue = User.GetAttributeValue(VarType);
	if(UserAttributeValue + ctrl*VarAmount >= 10)
		VarAmount = 10 - UserAttributeValue;

	User.SetAttributeValue(VarType, ctrl*VarAmount);
	
		
	int DefRating = VarDef;
	DefRating *= (1+User.GetAttributeValue(End)/10.0);
	DefRating = (int)DefRating;
	User.SetDef(DefRating);
}

/*!
* \fn      	Armor<P>::SetStats(string Vname, int Vdef, int Vamount, Attribute Vtype, WORD Color)
* \brief    Imposta le statistiche dell'arma
* \param	string Vname
* \param	int Vdef
* \param	int Vamount
* \param	Attribute Vtype
* \param	WORD Color
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Armor<P>::SetStats(string Vname, int Vdef, int Vamount, Attribute Vtype, WORD Color)
{
	Name = Vname;
	VarDef = Vdef;
	VarAmount = Vamount;
	VarType = Vtype;
	NameColor = Color;
}

/*!
* \fn      	Armor<P>::ShowStats()
* \brief    Mostra le statistiche dell'arma
* \return   void
* \date     28/08/2021
* \author   Alessio Cicione
* \file     Functions.cpp
*/
template<class P>
void Armor<P>::ShowStats()
{
	cout<<"------------------------------"<<endl;
	con.color(NameColor);
	cout<<Name<<endl;
	con.color(0x07);
	cout<<"DEF: "<<VarDef<<endl;
	cout<<"+"<<VarAmount<<" BOOST A: "<<ReturnAttribute(VarType)<<endl;
	cout<<"------------------------------"<<endl;
}
