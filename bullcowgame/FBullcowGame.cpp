
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "money";
	bGameIsWon = false;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}
EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (false) // If guess isnt isogram
	{
		return EWordStatus::Not_Isogram;
	}
	else if (false) // If guess isnt all lowercase
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
