// p2.cpp
// TODO: add documentation

#include "hangman.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
  //declare variables
  Hangman testGame;
  char letter;
  bool gameOver = false;
  bool gameWon = false;
  string filename;
  char inputChar;
   cout << "Welcome to hangman the game!Would you like to play? (y/n) ";
   cin >> inputChar;
   if(inputChar == 'y') {
     Hangman game = Hangman();
     cout << "Enter a filename: ";
     cin >> filename;
     
     if (!testGame.initializeFile(filename)){
       cout << "file problem...exiting program" << endl;
       return 0;
     }else{
       bool startGame = testGame.newWord();
       while(startGame){
         gameWon = false;
         gameOver = false;
         testGame.displayGame();
         while(!gameOver || !gameWon){
           cout << "guess a letter: ";
           cin >> letter;
           bool valid = game.guess(inputChar, gameOver, gameWon);
           testGame.displayGame();
           if(valid){
             if(gameOver) {
               cout << "sorry, you ran out of guesses" << endl << endl;
               testGame.revealWord();
             } else if(gameWon) {
               cout << "congrats, you won!" << endl << endl;
             }
           } else {
             cout << "error: invalid guess..." << endl;
           }
         }
         testGame.displayStatistics();
         if(testGame.newWord()) {
           cout << "would you like to play again?(y/n)";
           cin >> inputChar;
           if(inputChar=='n') {
             startGame = false;
           }
         } else {
           startGame = false;
       } }
     }
     cout << "[Thanks for playing!]" << endl;
   }

}
