// hangman.h
#include <string>
using namespace std;

#ifndef HANGMAN_H
#define HANGMAN_H

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

class Hangman {
public:
  Hangman();
  bool initializeFile(string filename);
  void displayStatistics();
  bool newWord();
  void displayGame();
  bool guess(char letter, bool& done, bool& won);
  void revealWord();

  
private:	
  static const int BODY_SIZE = 9;
  static const int LIST_SIZE = 100;
  static const int ALPHA_SIZE = 26;
  static const char BEGIN = 'A';
  static const char SPACE = ' ';
  static const char UNDERSCORE = '_';
  static const int SCREEN_WIDTH = 80;
  static const int MAX_BAD_GUESSES = 7;
  static const int HEAD = 1;
  static const int NECK = 2;
  static const int LT_ARM = 3;
  static const int RT_ARM = 4;
  static const int TORSO = 5;
  static const int LT_LEG = 6;
  static const int RT_LEG = 7;
  
  
  
  struct BodyPart{
    string firstLine;
    string secondLine;
    string thirdLine;
    bool displaySecond;
    bool displayThird; 
  };
  
  struct WordInfo {
    string word;
    bool isAvailable;
  };
  
  struct AlphaInfo {
    char letter;
    bool isAvailable;
  };
  
  
  BodyPart body[BODY_SIZE];
  WordInfo words[LIST_SIZE]; 	
  AlphaInfo alphabet[ALPHA_SIZE];
  
  int currentWord;
  int gamesWon;
  int gamesLost;
  int numWordsRead;
  int numWordsAvailable;
  unsigned correctChars;
  unsigned badGuesses;


  void displayBody();
  void displayAlpha();
  void displayWord();
};

#endif
