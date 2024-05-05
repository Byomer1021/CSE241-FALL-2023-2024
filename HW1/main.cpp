// main.cpp
#include "chess.h"

int main()
{

	srand(static_cast<unsigned>(time(0)));
	chessBoard_ chess;
	string move;
	bool okudum = false, valid = false;
	cout << "Welcome to the Chess Game !" << endl;

	try
	{
		while (true)
		{
			chess.displayBoard();
			chess.writeBoardToFile("output.txt");

			std::cout << endl;
			std::cout << "\n\033[48;2;100;0;100m[White's Turn]\033[0m\n\n\033[AEnter your move (e.g., e2e4): ";

			// Check if the white user's move is valid
			do
			{
				move = whiteInput(chess);
				valid = chess.isValidMove(move[1] - '1', move[0] - 'a', move[3] - '1', move[2] - 'a');
				if (valid == false && move.length() == 0)
					valid = true;
				if (valid == false)
					std::cout << "Invalid move. Please enter a valid move." << std::endl;
			} while (valid == false);

			if (whiteMove(chess, move) == false)
				break;

			chess.displayBoard();
			chess.writeBoardToFile("output.txt");

			std::cout << endl;
			std::cout << "\n\033[48;2;150;100;0m[Black's Turn]\033[0m\n\n\033[AEnter your move (e.g., d7d5): ";

			// Check if the black user's move is valid
			do
			{
				move = blackInput(chess);
				valid = chess.isValidMove(move[1] - '1', move[0] - 'a', move[3] - '1', move[2] - 'a');
				if (valid == false && move.length() == 0)
					valid = true;
				if (valid == false)
					std::cout << "Invalid move. Please enter a valid move." << std::endl;
			} while (valid == false);

			if (blackMove(chess, move) == false)
				break;
		}
		// cout << "\nxd\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}

string whiteInput(chessBoard_ &chess)
{
	bool okudum = false;
	string move = "";
	int c;
	while ((c = std::cin.get()) != '\n')
	{
		okudum = true;
		move += c;
	}
	if (move.length() != 4)
		okudum = false;
	if (okudum == false)
		move = chess.generateYourMove();
	std::cout << "White's move: " << move << std::endl;
	chess.writeWMovesToFile("output.txt", move);
	return move;
}

string blackInput(chessBoard_ &chess)
{
	bool okudum = false;
	string move = "";
	int c;
	while ((c = std::cin.get()) != '\n')
	{
		okudum = true;
		move += c;
	}
	if (move.length() != 4)
		okudum = false;
	if (okudum == false)
		move = chess.generateComputerMove();
	std::cout << "Black's move: " << move << std::endl;
	chess.writeBMovesToFile("output.txt", move);
	return move;
}

bool whiteMove(chessBoard_ &chess, const string move)
{
	cout << "\n   W\tB\n";
	cout << "  " << chess.calculateWhiteScore() << "\t" << chess.calculateBlackScore() << "\n";
	chess.writeScoresToFile("output.txt");
	if (chess.makeMove(move) == false)
	{
		chess.displayBoard();
		chess.writeBoardToFile("output.txt");

		if (chess.isCheckmate(true))
			cout << "\nCheckmate!"
				 << " Black has won!\n";
		else
			cout << "\nStalemate!\n";
		return false;
	}

	if (chess.isStalemate())
	{
		chess.displayBoard();
		cout << "\nStalemate!\n";
		return false;
	}
	return true;
}

bool blackMove(chessBoard_ &chess, const string move)
{
	cout << "\n   W\tB\n";
	cout << "  " << chess.calculateWhiteScore() << "\t" << chess.calculateBlackScore() << "\n";
	chess.writeScoresToFile("output.txt");
	if (chess.makeMove(move) == false)
	{
		chess.displayBoard();
		chess.writeBoardToFile("output.txt");

		if (chess.isCheckmate(false))
			cout << "\nCheckmate!"
				 << " White has won!\n";
		else
			cout << "\nStalemate!\n";
		return false;
	}

	if (chess.isStalemate())
	{
		chess.displayBoard();
		cout << "\nStalemate!\n";
		return false;
	}
	return true;
}
