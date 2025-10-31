#ifndef Gamelib
#define Gamelib

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<thread>
#include<windows.h>
#include<stdexcept>
#include<time.h>
#include<math.h>
#include<string>
#include<ciso646>

using namespace std;
/// Enum per la qualita' dello scaling
enum Rating : char {E, D, C, B, A, S};
/// Enum per gli attributi principali del giocatore
enum Attribute : char {Str, Per, End, Cha, In, Agi, Lck, NO};

static int FloorCount = 1;
static int SpriteNum = 6;
const int LineSize = 40;
/// Livello base dei nemici generati
static int EnemyBaseLvl = 1;

void Delay(int Seconds);
void DrawLine(char LineTok, int Length);
void DrawText(string Text, int Mode, int Size);
void DrawSprite(string filename, WORD Color = 0x07);
string ReturnRating(Rating Value);
string ReturnAttribute(Attribute Value);

/** 
* \class console
* \brief Questa struttura contiene le funzioni necessarie al ridimensionamento
* della finestra del terminale e al cambio colore delle scritte a schermo
* \date 28/08/2021  
*/
struct console	
  {
  console( unsigned width, unsigned height )
    {
    SMALL_RECT r;
    COORD c;
    hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hConOut, &csbi))
      throw runtime_error( "You must be attached to a human." );

    r.Left = 0;
    r.Top = 0;
    r.Right = width -1;
    r.Bottom = height -1;
    SetConsoleWindowInfo(hConOut, TRUE, &r);

    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize(hConOut, c);
    }

  ~console()
    {
    SetConsoleTextAttribute(hConOut, csbi.wAttributes );
    SetConsoleScreenBufferSize(hConOut, csbi.dwSize);
    SetConsoleWindowInfo(hConOut, TRUE, &csbi.srWindow);
    }
	/*
	NOTA TIPO WORD:
	A 16-bit unsigned integer. The range is 0 through 65535 decimal.

	This type is declared in WinDef.h as follows:

	typedef unsigned short WORD;
	*/
  void color(WORD color = 0x07)
    {
    SetConsoleTextAttribute(hConOut, color);
    }

  HANDLE hConOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  };
  
/** 
* \class Object
* \brief Questa classe contiene gli oggetti.
* Le classi derivate Weapon e Armor conterranno i metodi per alterare il giocatore in base alle
* caratteristiche specifiche della singola arma o armatura.
* \author Alessio Cicione
* \date 28/08/2021 
*/
class Object
{
	protected:
		string Name = "unnamed";
		/// Rappresenta di quanto un attributo del giocatore verra' incrementato o decrementato
		int VarAmount = 1;
		/// Rappresenta l'attributo che l'oggetto andra' a modificare
		Attribute VarType = NO;
	public:
		virtual void ApplyEffect(){};
		virtual void SetStats(){};
		virtual void ShowStats(){};
};

/** 
* \class Weapon
* \brief Questa classe rappresenta la categoria di oggetti "Arma" e contiene i metodi necessari ad
* assegnarne le caratteristiche ed alterare il giocatore 
* \author Alessio Cicione
* \date 28/08/2021 
*/
template<class P>
class Weapon : public Object
{
	private:
		/// rappresenta il valore di attacco dell'arma
		int VarAtk = 1;
		/** Rappresenta la classe di scaling dell'arma, in ordine sono: E, D, C, B, A, S.
		* Determina la rarita' dell'arma e la qualita' dell'incremento del valore di attacco
		* all'aumentare dell'attributo sul quale si effettua lo scaling
		*/
		Rating ScaleClass = E;
		/**
		* Rappresenta l'attributo sul quale l'arma effettua lo "scaling".
		* Il valore di attacco dell'arma incrementera' all'aumentare di questo attributo.
		*/
		Attribute ScaleAttribute = NO;
		/// Colore del nome visualizzato
		WORD NameColor;
	public:
		/// Modifica il giocatore in base alle caratteristiche dell'arma
		void ApplyEffect(P &User, bool Removing = false);
		/// Assegna le caratteristiche dell'arma
		void SetStats(string Vname, int Vatk, int Vamount, Attribute Vtype, Rating ScaleCl, Attribute ScaleAttr, WORD Color = 0x07);
		/// Mostra le caratteristiche dell'arma
		void ShowStats();
};

/** 
* \class Armor
* \brief Questa classe rappresenta la categoria di oggetti "Armatura" e contiene i metodi necessari ad
* assegnarne le caratteristiche ed alterare il giocatore 
* \author Alessio Cicione
* \date 28/08/2021 
*/
template<class P>
class Armor : public Object
{
	private:
		/// rappresenta il valore di difesa dell'armatura
		int VarDef = 1;
		/// Colore del nome visualizzato
		WORD NameColor;
	public:
		/// Modifica il giocatore in base alle caratteristiche dell'armatura
		void ApplyEffect(P &User, bool Removing = false);
		/// Assegna le caratteristiche dell'armatura
		void SetStats(string Vname, int Vdef, int Vamount, Attribute Vtype, WORD Color = 0x07);
		/// Mostra le caratteristiche dell'armatura
		void ShowStats();
};

/** 
* \class LevelSys
* \brief Questa classe contiene il livello del giocatore ed i metodi necessari a
* gestirne l'incremento.
* \author Alessio Cicione
* \date 28/08/2021 
*/
class LevelSys
{
	private:
		/// Livello attuale
		unsigned int CurrentLvl;
		/// Esperienza (XP) necessaria per avanzare al prossimo livello
		int XpToNext;
		/// Esperienza attuale
		int CurrentXp;
	public:
		// Costruttore
		LevelSys();
		/// Avanza di livello
		void AdvLvl();
		/// Aggiunge esperienza
		bool XpAdd(int XpAmount);
		/// Mostra la barra di avanzamento del livello attuale
		void ShowPercBar();
		/// Resituisce il livello attuale
		int GetLevel(){return CurrentLvl;}
		/// Imposta il livello
		void SetLevel(int Level){if(Level >= 0) CurrentLvl = Level;}
		/// Imposta l'esperienza accumulata
		void SetCurrentXp(int Value){if(Value >= 0 and Value < XpToNext) CurrentXp = Value;}
};

/** 
* \class Player
* \brief Questa classe rappresenta il giocatore e ne contiene le caratteristiche. 
* \author Alessio Cicione
* \date 28/08/2021 
*/
class Player
{
	private:
		/// Nome del giocatore
		string name;
		/// Punti ferita attuali del giocatore
		int hp;
		/// Punti ferita massimi del giocatore (soggetti a modifica all'aumentare del livello)
		int HpCap = 100;
		/// Numero di cure disponibili al giocatore
		int HealCount;
		/// Difesa del giocatore
		int def;
		/// Attacco del giocatore
		int atk;
		/// Attributo "forza" del giocatore
		int str;
		/// Attributo "percezione" del giocatore
		int per;
		/// Attributo "resistenza" del giocatore
		int end;
		/// Attributo "carisma" del giocatore
		int cha;
		/// Attributo "intelligenza" del giocatore
		int in;
		/// Attributo "agilita'" del giocatore
		int agi;
		/// Attributo "fortuna" del giocatore
		int lck;
		/// Moltiplicatore danni critici
		int crit_mult;
		/// Indica se l'istanza e' viva (hp>0)
		bool Alive;
		/// Indica se l'istanza e' un BOT oppure e' controllata dal giocatore
		bool BOT;
		/// Indica se l'istanza si trova in una posizione di guardia
		bool InGuard;
		/// Indica la forza della guardia
		int GuardStr;
		/// Indica il numero massimo di cure disponibili al giocatore
		int HealCap;
		/// Indica le monete attuali del Giocatore
		int Coins;
		/// Indica l'efficacia delle cure
		float HealMult;
	public:
		// Costruttore
		Player(int Vdef, int Vatk, string Vname, bool Auto = false, int Vstr=1, int Vper=1, int Vend=1, int Vcha=1, int Vin=1, int Vagi=1, int Vlck=1);
		/// Restituisce il valore di attacco
		int GetAtk(){return atk;}
		/// Restituisce il valore di difesa
		int GetDef(){return def;}
		/// Restituisce il valore dei punti ferita
		int GetHp(){return hp;}
		/// Mostra le statistiche del giocatore / NPC
		void ShowStats();
		/// Indica se il giocatore / NPC e' ancora in vita
		bool IsAlive(){return Alive;}
		/// Effettua un attacco
		void Attack(Player &Target);
		/// Attiva lo stato di guardia incrementando la difesa
		void Guard();
		/// Restituisce il nome
		string GetName(){return name;}
		/// Indica se il giocatore / NPC si trova in guardia
		bool GetGuard(){return InGuard;}
		/// Imposta lo stato di guardia
		void SetGuard(bool Guard){InGuard = Guard;}
		/// Restituisce la forza della guardia
		int GetGuardStr();
		/// Indica se l'istanza e' un BOT
		bool IsBot(){return BOT;}
		/// Stampa la barra dei punti ferita
		void DrawHpBar();
		/// Effettua una scelta automatica dell'azione da eseguire durante un turno
		char AutoChoice(Player TargetPlayer, Player CurrentPlayer);
		/// Imposta il numero delle cure
		void SetHealCount(int Vcount){HealCount = Vcount;}
		/// Imposta il numero massimo delle cure
		void SetHealCap(int Vcount){HealCap = Vcount;}
		/// Restituisce il numero delle cure
		int GetHealCount(){return HealCount;}
		/// Restituisce il numero massimo delle cure
		int GetHealCap(){return HealCap;}
		/// Cura il Giocatore / NPC
		void Heal(int Amount){hp + Amount > HpCap ? hp = HpCap : hp += Amount;}
		/// Restituisce il numero massimo di punti ferita
		int GetHpCap(){return HpCap;}
		/// Imposta i punti ferita attuali
		void SetHp(int Value){if(Value<=HpCap) hp = Value;}
		/// Imposta il numero massimo di punti ferita
		void SetHpCap(int Value){if(Value>0) HpCap = Value; hp = HpCap;}
		/// Imposta "Alive"
		void SetAlive(bool Value){if(Value == true or Value == false) Alive = Value;}
		/// Aggiunge monete
		void AddCoins(int Value){Coins+=Value;}
		/// Restituisce il numero di monete possedute
		int GetCoins(){return Coins;}
		/// Restituisce il valore del moltiplicatore delle cure
		float GetHealMult(){return HealMult;}
		/// Imposta il valore del moltiplicatore delle cure
		void SetHealMult(float Value){if(Value > 0) HealMult = Value;}
		/// Salva su file il personaggio
		friend void SaveToFile(Player Character);
		/// Carica da file il personaggio
		friend Player LoadFromFile(string CharacterName, bool &Found);
		friend ostream& operator<<(ostream &ofs, Player Character);
		friend istream& operator>>(istream &ifs, Player &Character);
		/// Gestisce il livello del giocatore
		LevelSys PlayerLevel;
		/// Arma attuale del giocatore
		Weapon<Player> CurrentWeapon;
		/// Armatura attuale del giocatore
		Armor<Player> CurrentArmor;
		/// Imposta l'arma attuale del giocatore
		void SetCurrentWeapon(Weapon<Player> NewWeapon);
		/// Imposta l'armatura attuale del giocatore
		void SetCurrentArmor(Armor<Player> NewArmor);
		/// Restituisce il valore di un attributo
		int GetAttributeValue(Attribute attr);
		/// Imposta l'attacco
		void SetAtk(int Vatk){atk = Vatk;}
		/// Imposta la difesa
		void SetDef(int Vdef){def = Vdef;}
		/// Imposta il valore di un attributo
		void SetAttributeValue(Attribute attr, int Vattr);
		
};

/// Carica un personaggio da file
Player LoadFromFile(string CharacterName, bool &Found);
/// Salva il personaggio su file
void SaveToFile(Player Character);
/// Genera un istanza della classe player automatica (BOT)
Player GenerateNPC();
/// Genera un arma
Weapon<Player> GenerateWeapon(int EntLvl = 0);
/// Genera un armatura
Armor<Player> GenerateArmor(int EntLvl = 0);

/** 
* \class Turn
* \brief Questa classe rappresenta un turno
* \author Alessio Cicione
* \date 28/08/2021 
*/
class Turn
{
	public:
		// Costruttore
		Turn(Player &CurrentPlayer, Player &TargetPlayer);
		/** Consente al giocatore di scegliere l'azione da eseguire durante il turno, 
		* per i giocatori indicati come NPC, ovvero i BOT tale scelta e' automatica
		*/
		void GetAction(Player &CurrentPlayer, Player &TargetPlayer);
};

/** 
* \class Floor
* \brief Questa classe rappresenta un piano in cui avra' luogo un combattimento.
* Le caratteristiche del nemico da affrontare dipendono dal piano.
* \author Alessio Cicione
* \date 28/08/2021 
*/
class Floor
{
	private:
		/// conta il numero di turni trascorsi nel piano
		int TurnCount;
		/// Viene generato il nemico con il quale il giocatore dovra' combattere
		Player EnemyNPC = GenerateNPC();
	public:
		// Costruttore
		Floor();
		/// Inizializza il combattimento
		void Fight(Player &player1);
		/// Restituisce il numero di turni trascorsi
		int GetTurn(){return TurnCount;}
		/// Stampa a schermo le informazioni di interesse al giocatore
		void DrawWindow(Player playerP,Player playerN);
};

/** 
* \class Game
* \brief Questa classe rappresenta la partita.
* \author Alessio Cicione
* \date 28/08/2021 
*/
class Game
{
	private:
		bool Continue = true;
	public:
		// Costruttore
		Game();
		/// Inizia la partita
		void Start(Player &player1);
		/// Termina la partita
		void GameOver(Player &player1);
};

/// Permette al giocatore di creare il proprio personaggio
Player CreatePlayer();
#endif
