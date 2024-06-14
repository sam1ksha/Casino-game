#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class CasinoGame 
{
	private:
		std::string playerName;
		int balance;
		int bettingAmount;
		int guess;
		int dice;

	public:
		CasinoGame() 
		{
			srand(time(0));
			balance = 0;
		}

		void handleInputError()
		{
			std::cin.clear(); // Clear error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			std::cout << "Invalid input! Please enter a valid number\n";
		}

		void displayRules() const 
		{
			system("cls");
			std::cout << "\t\t======CASINO NUMBER GUESSING RULES!======\n";
			std::cout << "\t1. Choose a number between 1 to 10\n";
			std::cout << "\t2. Winner gets 10 times the money bet\n";
			std::cout << "\t3. Wrong bet, and you lose the amount you bet\n\n";
		}

		void getPlayerInfo() 
		{
			std::cout << "\n\nWhat's your Name: ";
			std::getline(std::cin, playerName);
			std::cout << "\nEnter the starting balance to play the game: Rs. ";
			std::cin >> balance;
			std::cout << endl;
		}

		void takeUserInput() 
		{
			std::cout << "Hey, " << playerName << ", enter the amount to bet: Rs. ";
			while (!(std::cin >> bettingAmount) || bettingAmount <= 0 || bettingAmount > balance)
			{
				handleInputError();
				std::cout << "Re-enter a positive value within your balance amount: Rs. ";
			}
			std::cout << endl;
		}

		void takeUserGuess()
		{
			std::cout << "Guess any betting number between 1 & 10: ";
			while (!(std::cin >> guess) || guess <= 0 || guess > 10)
			{
				handleInputError();
				std::cout << "Re-enter your number: ";
			}
			std::cout << endl;
		}

		void playGame() 
		{
			dice = rand() % 10 + 1;
			if (dice == guess) 
			{
				std::cout << "\n\nYou are in luck!! You have won Rs." << bettingAmount * 10;
				balance += bettingAmount * 10;
			} 
			else 
			{
				std::cout << "Oops, better luck next time!! You lost Rs. " << bettingAmount << "\n";
				balance -= bettingAmount;
			}
			std::cout << "\nThe winning number was: " << dice << "\n";
			std::cout << "\n" << playerName << ", You have a balance of Rs. " << balance << "\n";
		}

		bool continuePlaying() const 
		{
			if (balance == 0)
			{
				std::cout << "\n\n------------------Your balance is Rs. 0! GAME OVER!------------------\n\n";
				return false;
			}
			char choice;
			std::cout << "\n\n-->Do you want to play again (y/n)? ";
			std::cin >> choice;
			return (choice == 'Y' || choice == 'y');
		}

		bool hasSufficientBalance() const 
		{
			return (balance > 0);
		}

		void saveToFile() const 
		{
			std::ofstream outFile("casino_data.txt");

			if (outFile.is_open()) 
			{
				outFile << "Player Name: " << playerName << "\n";
				outFile << "Final Balance: Rs. " << balance << "\n";
				// You can add more information to save as needed

				outFile.close();
				std::cout << "Game data saved to 'casino_data.txt'\n";
			} 
			else 
			{
				std::cout << "Unable to open the file for saving.\n";
			}
		}
};

int main() 
{
    CasinoGame game;
    game.displayRules();
    game.getPlayerInfo();

    do 
    {
        game.takeUserInput();
        game.takeUserGuess();
        game.playGame();
    } while (game.continuePlaying() && game.hasSufficientBalance());

    game.saveToFile(); 

    //std::cout << "\n\nThanks for playing the game. Your final balance is Rs. " << (game.hasSufficientBalance() ? game.balance() : 0) << "\n\n";
	std::cout << "\n\nThanks for playing the game. Your final balance is Rs. " << (game.hasSufficientBalance() ? game.hasSufficientBalance() : 0) << "\n\n";

    return 0;
}
