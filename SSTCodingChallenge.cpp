// SSTCodingChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string> 
#include <fstream>

int getInputInRange(int maxRange);
int getFavoredFaceForDice(int dieNumber);
int getFactorForFaceOfDice(int dieNumber);
void clearInputStream();
int getInput();
int rollTheDice(int favoredFace, int factor);
void storeResultsInFile(const std::vector<std::string>& results, const std::string& filename);

int main()
{
    std::cout << "Simpson Strong-Tie Programming and Design Project\n";

	std::cout << "Enter a number of times the dice should be rolled: ";
	const int rollCount = getInput();

	std::vector<std::string> results;
	const int numberOfDice = 2;

	for (int i = 1; i <= numberOfDice; i++)
	{
		int favoredFaceDice = getFavoredFaceForDice(i);
		int factorFaceDice = getFactorForFaceOfDice(i);

		std::string resultString = "Dice " + std::to_string(i) + " result: ";

		for (int i = 0; i < rollCount; ++i)
		{
			int resultDice = rollTheDice(favoredFaceDice, factorFaceDice);

			resultString += std::to_string(resultDice);

			// We don't want to add a comma after the last roll
			bool isLastRoll = i == rollCount - 1;
			if (!isLastRoll)
			{
				resultString += ", ";
			}
		}

		results.push_back(resultString);
	}

	for (const std::string& result : results) {
		std::cout << result << std::endl;
	}

	storeResultsInFile(results, "results.txt");

	return 0;
}

int rollTheDice(int favoredFace, int factor) 
{
	std::vector<int> faces = { };

	// This will increase the probability of the favored face being rolled
	for (int i = 0; i < factor; ++i)
	{
		faces.push_back(favoredFace);
	}

	const int diceFaces = 6;
	for (int i = 1; i <= diceFaces; i++) 
	{
		// Skip the favored face as it has already been added to the faces vector
		if (i == favoredFace)
		{
			continue;
		}
		faces.push_back(i);
	}

	// Generate a random index from 0 to faces.size() - 1 to simulate rolling the dice
	int index = std::rand() % faces.size();

	return faces[index];
}

int getInput() 
{
	int input;

	// We will keep asking the user for input until they provide a valid number
	do
	{
		std::cin >> input;

		bool isInvalidInput = std::cin.fail();

		if (isInvalidInput)
		{
			// clear the error state so that the user can input again
			clearInputStream();

			std::cout << "Invalid input. Please try again.\n";
		}
		else
		{
			break;
		}

	} while (true);

	return input;
}

int getInputInRange(int maxRange) 
{
	int input;

	// We will keep asking the user for input until they provide a valid number within the specified range
	do
	{
		std::cout << "Enter a number between 1 and " << maxRange << ": ";
		std::cin >> input;

		bool isInvalidInput = std::cin.fail();

		if (isInvalidInput)
		{
			// clear the error state so that the user can input again
			clearInputStream();

			std::cout << "Invalid input. Please try again.\n";
		}
		else if (input < 1 || input > maxRange)
		{
			std::cout << "Input out of range. Please try again.\n";
		}
		else
		{
			break;
		}
	} while (true);

	return input;
}

int getFavoredFaceForDice(int dieNumber)
{
	std::cout << "Please specify the face to be favored for dice " << dieNumber << ": \n";

	const int diceFaces = 6;

	return getInputInRange(diceFaces);
}

int getFactorForFaceOfDice(int dieNumber)
{
	std::cout << "Please specify the factor of the favored face for dice " << dieNumber << ": \n";

	const int maxFactor = 5;

	return getInputInRange(maxFactor);
}

void clearInputStream() {
	std::cin.clear(); // Clear the error flag set on cin
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any invalid input
}

void storeResultsInFile(const std::vector<std::string>& results, const std::string& filename) {
	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		for (std::string result : results) {
			outFile << result << std::endl;
		}
		outFile.close();
		std::cout << "Results stored in " << filename << std::endl;
	}
	else {
		std::cerr << "Unable to open file " << filename << std::endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
