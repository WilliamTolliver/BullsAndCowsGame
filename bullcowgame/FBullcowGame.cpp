#pragma once
#include "FBullCowGame.h"

using int32 = int;
const FString HIDDEN_WORD = "person";
FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5}, {5,5}, {6,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}
void FBullCowGame::Reset()
{

	bGameIsWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

 FString FBullCowGame::GetHiddenWord() const
{
	return HIDDEN_WORD;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess)) // If guess isnt isogram
	{

		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // If guess isnt all lowercase
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // If the guess length is wrong
	{
		return EWordStatus::Invalid_Length;
	}
	else // Return okay
	{
		return EWordStatus::OK;
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the HiddenWord
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 hWChar = 0; hWChar < HiddenWordLength; hWChar++) {
		// compare letters against the Guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[hWChar]) {
				if (hWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}

	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// Treat 0 or 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // Create a map and add each letter

	for (auto Letter : Word)  // For all letters of the word
	{
		Letter = tolower(Letter); // Make sure all letters are lowercase
		if (LetterSeen[Letter]) { // We do not have an isogram
			return false;
		}
		else { // Add letter to the map
			LetterSeen[Letter] = true;
		}
	}

}

bool FBullCowGame::IsLowercase(FString Word) const {

	for (auto Letter : Word)  // For all letters of the word
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}