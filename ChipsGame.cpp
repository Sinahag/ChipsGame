#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

ofstream output;
struct player
{
    int numWs;
    string name;
};
string FindPlayerName(player[], bool playerTurn);
int askMove(bool player1Turn, int chipsInPile, player[]);
void getUserNames (player[]);
void addWins(player[], bool);
int i = 1;
const float MAX_TURN = .5;
const int MAX_CHIPS = 100;

int main()
{
  bool player1Turn = true;
  
  bool gameOver = false;
  
  int chipsInPile = 0;
  int chipsTaken = 0;
  
  char userChoice;
  player players[2];
  
  //seed the random number generator
   srand(time(0));
  
  //ask the players for their names, then store in an array
    getUserNames(players);
  //start the game with a random number of chips in the pile
  do
  {
    chipsInPile = (rand() % MAX_CHIPS) + 1;
    int moves = 0;
    cout << "This round will start with " << chipsInPile << " chips in the pile\n";
    gameOver = false;
    while (gameOver == false)
    {
     chipsTaken = askMove(player1Turn, chipsInPile, players);
     chipsInPile = chipsInPile - chipsTaken;
     cout << "There are " << chipsInPile << " left in the pile\n";
     player1Turn = !player1Turn;
     moves++;
     if (chipsInPile == 0)
     {
         gameOver = true;
        cout << FindPlayerName(players, player1Turn) << ", congratulations you won\n";
        output.open("Winners", ios::app);
        output << FindPlayerName(players, player1Turn) << " has won round: " << i << " in " << moves << " moves\n";
        addWins(players,player1Turn);
     }
    }
    cout << "Do you wish to play again? (Y/N)\n";
    cin >> userChoice;
    userChoice = toupper(userChoice);
      
      i++;
   }while (userChoice == 'Y');
    cout << players[0].name << " has had " << players[0].numWs << " total wins this game.\n";
    cout << players[1].name << " has had " << players[1].numWs << " total wins this game.\n";
    output.close();
  return 0;
}
////////////////////////////////
//
string FindPlayerName(player players[], bool playerTurn)
{
    if (playerTurn == true)
        return players[0].name;
    else
        return players[1].name;
}

/////////////////////////////////////////////////////////////////////////////////
int askMove(bool player1Turn, int chipsInPile,player players[])
{
    int chipsTaken;
    int maxPerTurn = MAX_TURN * chipsInPile;
     do
     {
          cout << FindPlayerName(players, player1Turn) << " How many chips would  you like?\n";
        
        cout << "You can take up to ";
        if (( maxPerTurn ) == 0)
        {
            cout << " 1\n";
        }
        else
        {
            cout << maxPerTurn << endl;
        }
        if ( FindPlayerName(players, player1Turn) == "AI")
        {
            if(maxPerTurn == 0)
                chipsTaken = 1;
            else
                chipsTaken = (rand() % maxPerTurn) + 1;
        }else
            cin >> chipsTaken;
            cout << endl;
     } while ((chipsTaken > maxPerTurn )  && (chipsInPile > 1));
    return chipsTaken;
}

////////////////////////////////////////////////////////////////////////////////
void getUserNames (player players[])
{
    cout << "Player 1, please enter your name: ";
    cin >> players[0].name;
    cout << "\nThanks and good luck!" << endl << "Player 2, please enter your name (if you would like to play against a computer, enter AI:";
    cin >> players[1].name;
    cout << "\nThanks and good luck! \n";
    players[0].numWs = 0;
    players[1].numWs = 0;
    
}

void addWins(player players[], bool player1turn)
{
    if(player1turn)
        players[0].numWs++;
    else
        players[1].numWs++;

}
