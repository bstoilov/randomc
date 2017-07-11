#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <ctime>
#include <stdio.h>

using namespace std;

// Used as property separator for the dat files
static const char DELIMER = '&';

// The colors
enum Color { Red, Black, Blue, White, Green, Empty };

// File paths for the dat files
static const string PROFILES_PATH = "c:/Data/players.dat";
static const string CARDS_PATH = "c:/Data/cards.dat";
static const string DECKS_PATH = "c:/Data/decks.dat";

// Converts Color to string. Red -> "Red"
string colorToString(Color color) {
  switch (color) {
    case Red:
      return "Red";
    case Black:
      return "Black";
    case Blue:
      return "Blue";
    case White:
      return "White";
    case Green:
      return "Green";
    default:
      return "Empty";
  }
};

// Converts String to color. "Red" -> Red
Color stringToColor(string colorStr) {
  if (colorStr == "Red") {
    return Red;
  } else if (colorStr == "Black") {
    return Black;
  } else if (colorStr == "Blue") {
    return Blue;
  } else if (colorStr == "White") {
    return White;
  } else if (colorStr == "Green") {
    return Green;
  } else {
    return Empty;
  }
};

// Counts the number of 'searched' in target
int countChars(string target, char searched) {
  int count = 0;

  for (unsigned int i = 0; i < target.length(); i++) {
    if (target[i] == searched) {
      count++;
    }
  }
  return count;
};

// Converts int to string
string convertToString(int num) {
  stringstream ss;
  ss << num;
  return ss.str();
};

// Splits the string and saves the result in 'result'.
// The string to split is 'target' and its splited at 'delimer'
void splitString(string target, string* result, char delimer) {
  string dataSplit[countChars(target, delimer) + 1];
  int splitIndex = 0;
  int last = 0;
  for (unsigned int i = 0; i < target.length(); i++) {
    if (target[i] == DELIMER) {
      dataSplit[splitIndex] = target.substr(last, i - last);
      splitIndex++;
      last = i + 1;
    }
  }
  dataSplit[splitIndex] = target.substr(last, target.length() - last);

  for (int i = 0; i <= splitIndex; i++) {
    cout << "Assigning " << dataSplit[i] << " to " << i << endl;
    result[i] = dataSplit[i];
  }
};

// Class to represent player
class Player {
 private:
  string id;
  string name;

 public:
  Player() {
    id = "";
    name = "";
  };
  Player(string id, string name) {
    this->id = id;
    this->name = name;
  };

  // Creates the player form data string
  Player(string dataString) {
    string dataSplit[countChars(dataString, DELIMER) + 1];
    splitString(dataString, dataSplit, DELIMER);

    this->id = dataSplit[0];
    this->name = dataSplit[1];
  };

  string getName() { return name; };
  string getId() { return id; };
  void setId(string id) { this->id = id; }
  void setName(string name) { this->name = name; }
  void printInfo() { cout << "Name " << name << " ID " << id << endl; }
  string toDataString() { return id + DELIMER + name; };
};

// Class to represent Card
class Card {
 private:
  string id;
  string name;
  Color color;

 public:
  Card() {
    id = "";
    name = "";
    color = Empty;
  }
  Card(string id, string name, Color color) {
    this->color = color;
    this->id = id;
    this->name = name;
  }
  Card(string dataString) {
    string dataSplit[countChars(dataString, DELIMER) + 1];
    splitString(dataString, dataSplit, DELIMER);

    this->id = dataSplit[0];
    this->name = dataSplit[1];
    this->color = stringToColor(dataSplit[2]);
  }
  string toDataString() {
    return id + DELIMER + name + DELIMER + colorToString(color);
  }
  string getId() { return id; }
  string getName() { return name; }
  Color getColor() { return color; }
};

// Class to represent Deck
class Deck {
 private:
  string cardIds;
  string ownerId;
  Color color;

 public:
  Deck() {
    cardIds = "";
    ownerId = "";
    color = Empty;
  }
  Deck(string ownerId, string cardIds, Color color) {
    this->ownerId = ownerId;
    this->cardIds = cardIds;
    this->color = color;
  }
  Deck(string dataString) {
    string dataSplit[countChars(dataString, DELIMER) + 1];
    splitString(dataString, dataSplit, DELIMER);

    this->ownerId = dataSplit[0];
    this->cardIds = dataSplit[1];
    this->color = stringToColor(dataSplit[2]);
  }
  string toDataString() {
    return ownerId + DELIMER + cardIds + DELIMER + colorToString(color);
  }
  string getOwnerId() { return ownerId; }
  string getCardIds() { return cardIds; }
};

// This is the actual logic we provide
class Game {
 private:
  // Reads the card from file by id
  Card getCard(string id) {
    string line;
    ifstream myfile(CARDS_PATH.c_str());

    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        Card card(line);
        if (card.getId() == id) {
          return card;
          myfile.close();
        }
      }
      myfile.close();
    }
    Card defaultResult;
    return defaultResult;
  }
  // Reads the Player from file by id
  Player getPlayer(string id) {
    string line;
    ifstream myfile(PROFILES_PATH.c_str());
    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        Player player(line);
        if (player.getId() == id) {
          return player;
          myfile.close();
        }
      }
      myfile.close();
    }
    Player defaultResult;
    return defaultResult;
  }
  // Reads the Deck from file by id
  Deck getDeck(string ownerId) {
    string line;
    ifstream myfile(DECKS_PATH.c_str());
    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        Deck deck(line);
        if (deck.getOwnerId() == ownerId) {
          return deck;
          myfile.close();
        }
      }
      myfile.close();
    }
    Deck defaultResult;
    return defaultResult;
  }
  // By a given ',' separated list in string of cards, finds the most used
  // color.
  Color findMostCommonColor(string cardIds) {
    int blackCount = 0;
    int whiteCount = 0;
    int greenCount = 0;
    int redCount = 0;
    int blueCount = 0;

    int size = countChars(cardIds, ',') + 1;
    string cardIdArr[size];
    splitString(cardIds, cardIdArr, ',');
    for (int i = 0; i < size; i++) {
      Card card = getCard(cardIdArr[i]);
      switch (card.getColor()) {
        case Red:
          redCount++;
          break;
        case Black:
          blackCount++;
          break;
        case Blue:
          blueCount++;
          break;
        case White:
          whiteCount++;
          break;
        case Green:
          greenCount++;
          break;
        default:
          //
          break;
      }
    }

    int maxValue = max(
        blackCount, max(whiteCount, max(greenCount, max(redCount, blueCount))));

    if (maxValue == blackCount) {
      return Black;
    } else if (maxValue == whiteCount) {
      return White;
    } else if (maxValue == greenCount) {
      return Green;
    } else if (maxValue == redCount) {
      return Red;
    } else if (maxValue == blueCount) {
      return Blue;
    } else {
      return Empty;
    }
  }
  // Prints the deck with the ids of data replaced by their names
  void printDeck(Deck deck) {
    int size = countChars(deck.getCardIds(), ',') + 1;
    string cardIds[size];
    splitString(deck.getCardIds(), cardIds, ',');
    Player owner = getPlayer(deck.getOwnerId());

    cout << "Owner " << owner.getName() << "Cards ";
    for (int i = 0; i < size; i++) {
      Card card = getCard(cardIds[i]);
      cout << card.getName();
    }
    cout << endl;
  }

 public:
  // Creates deck
  void createDeck(string cardIds, string ownerId) {
    Color color = findMostCommonColor(cardIds);
    Deck deck(ownerId, cardIds, color);
    ofstream outfile;
    outfile.open(DECKS_PATH.c_str(), ios_base::app);
    outfile << deck.toDataString() << endl;
  }
  // Creates a player with ID current timestamp and saves it to file
  void createPlayer(string playerName) {
    Player player(convertToString(time(0)), playerName);
    ofstream outfile;
    outfile.open(PROFILES_PATH.c_str(), ios_base::app);
    outfile << player.toDataString() << endl;
  }
  // Creates a Card with ID current timestamp and saves it to file
  void createCard(string name, string color) {
    Card card(convertToString(time(0)), name, stringToColor(color));
    ofstream outfile;
    outfile.open(CARDS_PATH.c_str(), ios_base::app);
    outfile << card.toDataString() << endl;
  }
  // Prints all defined deck using 'printDeck()'
  void printAllDecks() {
    string line;
    ifstream myfile(DECKS_PATH.c_str());

    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        Deck deck(line);
        printDeck(deck);
      }
      myfile.close();
    }
  }
};

int main(int argc, char* argv[]) {
  Game game;
  // Parse input args
  if (argc <= 0) {
    return -1;
  } else {
    if (strcmp(argv[0], "cc") == 0) {
      game.createCard(argv[1], argv[2]);
      cout << "Created Card" << endl;
    } else if (strcmp(argv[0], "cd") == 0) {
      game.createDeck(argv[1], argv[2]);
      cout << "Created Deck" << endl;
    } else if (strcmp(argv[0], "cp") == 0) {
      game.createPlayer(argv[1]);
      cout << "Created player" << endl;
    } else if (strcmp(argv[0], "report") == 0) {
      game.printAllDecks();
    } else {
      cout << "Unsupported command" << endl;
      return -1;
    }
  }

  return 0;
}
