#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

// all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// Enums
enum class EWordStatus
{
	OK,
	Not_Isogram,
	Invalid_Length,
	Invalid,
	Not_Lowercase

};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor
		
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	void Reset();
	FString GetHiddenWord() const;
	// TODO make a more rich return value.
	EWordStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.
	FBullCowCount SubmitGuess(FString);

	// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsLowercase(FString Word) const;
	bool IsIsogram(FString) const;

};