#include "hangman.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cctype>

Hangman::Hangman()
{
  //initializing all private attributes on the class
  
  gamesWon = 0;
  gamesLost = 0;
  numWordsRead = 0;
  numWordsAvailable = 0;
  correctChars = 0;
  badGuesses = 0;
  
  alphabet[0].letter =  'A';
  alphabet[1].letter =  'B';
  alphabet[2].letter =  'C';
  alphabet[3].letter =  'D';
  alphabet[4].letter =  'E';
  alphabet[5].letter =  'F';
  alphabet[6].letter =  'F';
  alphabet[7].letter =  'H';
  alphabet[8].letter =  'I';
  alphabet[9].letter =  'J';
  alphabet[10].letter =  'K';
  alphabet[11].letter =  'L';
  alphabet[12].letter =  'M';
  alphabet[13].letter =  'N';
  alphabet[14].letter =  'O';
  alphabet[15].letter =  'P';
  alphabet[16].letter =  'Q';
  alphabet[17].letter =  'R';
  alphabet[18].letter =  'S';
  alphabet[19].letter =  'T';
  alphabet[20].letter =  'U';
  alphabet[21].letter =  'V';
  alphabet[22].letter =  'W';
  alphabet[23].letter =  'X';
  alphabet[24].letter =  'Y';
  alphabet[25].letter =  'Z';
  

  // initialize hangman body array
  
  body[0].firstLine = "    ----\n";                                              
  body[1].firstLine = "    |  |\n";                                              
  body[2].firstLine = "       |\n";                                              
  body[2].secondLine = "    O  |\n";                                             
  body[3].firstLine = "       |\n";                                              
  body[3].secondLine = "    |  |\n";                                             
  body[4].firstLine = "       |\n";                                              
  body[4].secondLine = "   -|  |\n";                                             
  body[4].thirdLine = "   -|- |\n";                                              
  body[5].firstLine = "       |\n";                                              
  body[5].secondLine = "    |  |\n";                                             
  body[6].firstLine = "       |\n";                                              
  body[6].secondLine = "   /   |\n";                                             
  body[6].thirdLine = "   / \\ |\n";                                             
  body[7].firstLine = "       |\n";                                              
  body[8].firstLine = "_______|___\n";
}

//reads words from file and stores into array for game, returns false if there
//is a file problem

bool Hangman::initializeFile(string filename){

  ifstream file;
  file.open(filename);
  if (file.fail()) {
    return false;
  }
  string word;
  while (file >> words[numWordsRead].word) {
    words[numWordsRead++].isAvailable = true;
    numWordsAvailable++;
  }
  file.close();
  return true;
}



void Hangman::displayStatistics()
{
  cout << "Wins: " << gamesWon << endl;
  cout << "Losses: " << gamesLost << endl;
  cout << "Total words: " << numWordsRead << endl;
  cout << "Words available: " << numWordsAvailable << endl;
  
}

bool Hangman::newWord()
{
//randomly chooses new word from list of words, returns false if no more words
//available
  for (int i = 0; i < BODY_SIZE; i++) {
    body[i].displaySecond = false;
    body[i].displayThird = false;
  }
  for (int i = 0; i < ALPHA_SIZE; i++)
    {
      alphabet[i].isAvailable = false;
    }
  correctChars = 0;
  badGuesses = 0;
  if(numWordsAvailable == 0){
    return false;
  }
  srand(time(NULL));
  currentWord = rand() % numWordsAvailable;
  numWordsAvailable--;
  return true;
}

void Hangman::displayGame()
{
  //displays the appropriate body parts (i.e. body array),
  //words (with underscores as needed), and the letters still
  //available
  
  displayBody();
  cout << endl << endl;
  displayWord();
  cout << endl << endl;
  displayAlpha();
  cout << endl << endl;
}

bool Hangman::guess(char letter, bool& done, bool& won)
{
  //processes the user's guess, returns false if letter chosen was not available,
  //done will return true when user is out of guesses, won will return true when
  //user has correctly guessed the word
  
  if (alphabet[toupper(letter) - BEGIN].isAvailable == true) {
    unsigned correct = 0;
    char guessChar = toupper(letter);
    alphabet[guessChar - BEGIN].isAvailable = false;
    for (unsigned i = 0; i < words[currentWord].word.length(); i++) {
      // cout << "3" << endl;
      if(words[currentWord].word.at(i) == guessChar) {
        // cout << "4" << endl;
        correct++;
      }
    }
    
	// cout << "6" << endl;
    if(correct == 0) {
      badGuesses++;
      if(badGuesses <= 3) {
        body[badGuesses+1].displaySecond = true;
      } else if(badGuesses == 5 || badGuesses == 6) {
        body[badGuesses].displaySecond = true;
      } else if(badGuesses == 4){
        body[4].displayThird = true;
      } else if(badGuesses == 7) {
        done = true;
        gamesLost++;
        body[6].displayThird = true;
      }
    } else {
      correctChars += correct;
      if(correctChars==words[currentWord].word.length()) {
        gamesWon++;
        won = true; }
    }
    return true;
  } else {
    return false;
  }
}

void Hangman::revealWord()
{
  //displays the word with all letters
  int blanks = (SCREEN_WIDTH - (words[currentWord].word.length()));
  for (int i = 0; i < blanks; i++)
    cout << SPACE;
  for (unsigned i = 0; i < words[currentWord].word.length(); i++)
    cout << words[currentWord].word.at(i) << SPACE;
  cout << endl;
}	

void Hangman::displayBody()
{
  for (int i = 0; i < 9; i++) {
    if (body[i].displayThird)
      cout << body[i].thirdLine;
    else if (body[i].displaySecond)
      cout << body[i].secondLine;
    else
      cout << body[i].firstLine;
  }
}

void Hangman::displayWord()
{
  int blanks = (SCREEN_WIDTH - (words[currentWord].word.length() * 2)) / 2;
  for (int i = 0; i < blanks; i++)
    cout << SPACE;
  for (unsigned i = 0; i < words[currentWord].word.length(); i++) {
    if (alphabet[words[currentWord].word.at(i) - BEGIN].isAvailable)
      cout << words[currentWord].word.at(i) << SPACE;
    else
      cout << UNDERSCORE << SPACE;
  }
}

void Hangman::displayAlpha()
{
  int blanks = (SCREEN_WIDTH - (ALPHA_SIZE * 2 - 1)) / 2;
  for (int i = 0; i < blanks; i++)
    cout << SPACE;
  for (int i = 0; i < ALPHA_SIZE; i++)
    {
      if (!alphabet[i].isAvailable) {
        cout << alphabet[i].letter << SPACE;
      }
      else
        cout << SPACE << SPACE;
    }
}
