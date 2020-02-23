// Students: Kemper, Michael, Ryan Clode
// RedIDs: 822 86 7065

#include "dictionary.h"

using namespace std;

//The root node of the dictionary
dictentry *dictRoot = new dictentry();

/*
 * find - A function to traverse the dictionary tree to see if a character pointer word passed in exists in the tree already.
 * if the word has characters outside a-z, A-Z, or ', then BADCHARS enum will be returned'.
 */
dictentry::ResultType dictentry::find(const char *word, const char *targetword) {
  //set the currect dictionary node at the root
  dictentry* currentDictEntry = dictRoot;

  //for each character in the word passed in, traverse down the tree to see if the character exists as a branch
  for(int i = 0; i < strlen(word); i++) {
    //convert the character from its ASCII value down to the 0-26 range that we preallocated in the header file
    int finalCharIndexInArray;
    int targetwordCharAsInt = (int)targetword[i];
    if(targetwordCharAsInt == 39) {
      finalCharIndexInArray = 26;
    } else if ((targetwordCharAsInt > 96) && (targetwordCharAsInt < 123)) {
      finalCharIndexInArray = targetwordCharAsInt - 97;
    } else if ((targetwordCharAsInt > 64) && (targetwordCharAsInt < 91)) {
      finalCharIndexInArray = targetwordCharAsInt - 65;
    } else {
      //if character is outside the range, return BADCHARS enum
      cout << "BAD CHARACTERS. word is: \'" << targetword << "\' char is: \'" << targetword[i] << "\'" << (int)targetword[i] << endl;
      return dictentry::ResultType::BADCHARS;
    }
    //if the current character I am looping through exists in the tree, then I jump down to it and move where the current node pointer is at.
    if (currentDictEntry->next[finalCharIndexInArray] != NULL) {
      currentDictEntry = currentDictEntry->next[finalCharIndexInArray];
    } else {
      //if it doesn't exist, return MISSPELLED enum
      cout << targetword << endl;
      return dictentry::ResultType::MISSPELLED;
    }
  }
  //if the final node I end at has the isEndOfWord boolean set to true, I know it is the final character of a word and can return the CORRECT enum.
  //otherwise, return the MISSPELLED enum.
  if (currentDictEntry->isEndOfWord) {
    //
    return dictentry::ResultType::CORRECT;
  } else {
    cout << targetword << endl;
    return dictentry::ResultType::MISSPELLED;
  }
};

/*
 * insert - A function to insert words into a dictionary tree character by character, branching off the previous letters and marking the final character.
 * if the word has characters outside a-z, A-Z, or ', then BADCHARS enum will be returned'.
 */
dictentry::ResultType dictentry::insert(const char *characters, const char *targetword) {
  //set the currect dictionary node at the root
  dictentry* currentDictEntry = dictRoot;

  //for each character in the word passed in, traverse down the tree to see if the character exists as a branch
  //if it doesn't exist, add a branch off of the current character for it
  //also sets the final character in each word inserted's boolean isEndOfWord value equal to true
    for(int i = 0; i < strlen(targetword); i++) {
      //convert the character from its ASCII value down to the 0-26 range that we preallocated in the header file
      int finalCharIndexInArray;
      int targetwordCharAsInt = (int)targetword[i];
      if(targetwordCharAsInt == 39) {
        finalCharIndexInArray = 26;
      } else if ((targetwordCharAsInt > 96) && (targetwordCharAsInt < 123)) {
        finalCharIndexInArray = targetwordCharAsInt - 97;
      } else if ((targetwordCharAsInt > 64) && (targetwordCharAsInt < 91)) {
        finalCharIndexInArray = targetwordCharAsInt - 65;
      } else {
        //if character is outside the range, return BADCHARS enum
        cout << "BAD CHARACTERS. word is: \'" << targetword << "\' char is: \'" << targetword[i] << "\'" << targetwordCharAsInt << endl;
        return dictentry::ResultType::BADCHARS;
      }
      if (currentDictEntry->next[finalCharIndexInArray] != NULL) {
        //if the current character we are looping through exists in the tree, then jump down to it and move where the current node pointer is at.
        currentDictEntry = currentDictEntry->next[finalCharIndexInArray];
      } else {
        //if the current character we are looping through DOESN'T exist in the tree,
        //then create a new branch for it and move where the current node pointer is at.
        currentDictEntry->next[finalCharIndexInArray] = new dictentry();
        currentDictEntry = currentDictEntry->next[finalCharIndexInArray];
        //if I am at the final character in the tree, set its isEndOfWord boolean value to true to mark it as the end of a word.
        if(i == strlen(targetword)-1) {
          currentDictEntry->isEndOfWord = true;
        }
      }
    }
    return dictentry::ResultType::ADDED;
};
