// chess.cpp

#include "chess.h"

#define maxAttempts 1000000 // Max attempts to find a valid move

chessBoard_::chessBoard_()
{
	board.resize(8, vector<piece_>(8, piece_('.', 0))); // Initialize with empty squares

	// Initialize pawns
	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = piece_('P', 1); // White pawns
		board[6][i] = piece_('p', 1); // Black pawns
	}

	// Initialize other pieces
	board[0][0] = piece_('R', 5); // White rooks
	board[0][7] = piece_('R', 5);
	board[7][0] = piece_('r', 5); // Black rooks
	board[7][7] = piece_('r', 5);

	board[0][1] = piece_('N', 3); // White knights
	board[0][6] = piece_('N', 3);
	board[7][1] = piece_('n', 3); // Black knights
	board[7][6] = piece_('n', 3);

	board[0][2] = piece_('B', 3); // White bishops
	board[0][5] = piece_('B', 3);
	board[7][2] = piece_('b', 3); // Black bishops
	board[7][5] = piece_('b', 3);

	board[0][3] = piece_('Q', 9); // White queen
	board[7][3] = piece_('q', 9); // Black queen

	board[0][4] = piece_('K', 10); // White king
	board[7][4] = piece_('k', 10); // Black king
}

void chessBoard_::displayBoard() const
{
	for (int i = 7; i >= 0; --i)
	{
		cout << i + 1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			if (isPieceAttacking(i, j) && board[i][j].symbol != '.')
				cout << "\033[38;2;0;255;0m" << board[i][j].symbol << " \033[0m"; // green
			else if (isPieceUnderAttack(i, j) && board[i][j].symbol != '.')
				cout << "\033[38;2;255;0;0m" << board[i][j].symbol << " \033[0m"; // red
			else
				cout << board[i][j].symbol << " ";
		}
		cout << endl;
	}

	cout << "-----------------------" << endl;
	for (int i = 0; i < 8; ++i)
	{
		if (i < 1)
		{
			cout << "  ";
		}
		// Assuming you want to print 'a' through 'h'
		char current_char = 'a' + i;
		cout << current_char << " ";
	}
}

bool chessBoard_::makeMove(const string &move)
{
	if (move.length() != 4)
		return false;
	// throw invalid_argument("Invalid move format. Must be in the form 'e2e4'.");

	// Extract coordinates from the move string
	int fromRow = move[1] - '1';
	int fromCol = move[0] - 'a';
	int toRow = move[3] - '1';
	int toCol = move[2] - 'a';

	// Check if the coordinates are within the board bounds
	if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
		toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
	{
		throw out_of_range("Invalid move. Coordinates out of bounds.");
	}

	// Check if there is a piece at the starting position
	if (board[fromRow][fromCol].symbol == '.')
	{
		throw invalid_argument("Invalid move. No piece at the specified starting position.");
	}

	if (board[fromRow][fromCol].symbol == 'p' && toRow == 0)
	{
		board[fromRow][fromCol].symbol = 'q';
		board[fromRow][fromCol].value = 9;
	}
	else if (board[fromRow][fromCol].symbol == 'P' && toRow == 7)
	{
		board[fromRow][fromCol].symbol = 'Q';
		board[fromRow][fromCol].value = 9;
	}
	// Move the piece to the destination
	board[toRow][toCol] = board[fromRow][fromCol];
	board[fromRow][fromCol] = piece_('.', 0); // Empty the source square

	return true;
}

// Function to check if a move is valid
bool chessBoard_::isValidMove(int fromRow, int fromCol, int toRow, int toCol) const
{
	//  Check if the move is within the board bounds
	if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
		toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
	{
		return false;
	}

	// cout << "asdasd" << endl;

	// cout << (char)(fromCol + 'a') << fromRow + 1 << (char)(toCol + 'a') << toRow + 1 << "\n";

	char piece = board[fromRow][fromCol].symbol;
	char targetPiece = board[toRow][toCol].symbol;

	// cout << "From Piece: " << piece << /*"  " << val <<*/ "  , To Piece: " << targetPiece << endl;

	// cout << "222asdasd" << endl;

	// Check if the destination square is occupied by a friendly piece
	if (targetPiece != '.' && isSameColor(piece, targetPiece))
	{
		return false;
	}

	// Check if there is any piece in the path (excluding the starting and ending squares)

	// cout << "3333asdasd" << endl;
	// if (!isClearPath(fromRow, fromCol, toRow, toCol))
	// {
	// 	return false;
	// }
	// cout << "\nxd\n";

	// if(piece != 'p' && piece != 'P')
	// 	return false;

	if (isBlackPiece(piece) && piece != 'p')
		piece -= 'a' - 'A';

	// Check specific rules for each piece type
	switch (piece)
	{
	case 'P': // White pawn
		// Pawn can move forward one square
		if (fromCol == toCol && toRow == fromRow + 1 && targetPiece == '.')
		{
			return true;
		}
		// Pawn can move forward two squares from the starting position
		else if (fromCol == toCol && fromRow == 1 && toRow == 3 && targetPiece == '.' &&
				 board[toRow - 1][toCol].symbol == '.')
		{
			return true;
		}
		// Pawn can capture diagonally
		else if (abs(toCol - fromCol) == 1 && toRow == fromRow + 1 && isBlackPiece(targetPiece))
		{
			return true;
		}
		return false;

	case 'p': // Black pawn
		// Pawn can move forward one square
		if (fromCol == toCol && toRow == fromRow - 1 && targetPiece == '.')
		{
			return true;
		}
		// Pawn can move forward two squares from the starting position
		else if (fromCol == toCol && fromRow == 6 && toRow == 4 && targetPiece == '.' &&
				 board[toRow - 1][toCol].symbol == '.')
		{
			return true;
		}
		// Pawn can capture diagonally
		else if (abs(toCol - fromCol) == 1 && toRow == fromRow - 1 && isWhitePiece(targetPiece))
		{
			return true;
		}
		return false;

		// Add rules for other pieces (R, N, B, Q, K) here...
	case 'R': // Rook
		// Rook can move horizontally or vertically any number of squares
		if ((fromRow == toRow && isClearHorizontalPath(fromCol, toCol, fromRow)) ||
			(fromCol == toCol && isClearVerticalPath(fromRow, toRow, fromCol)))
		{
			return true;
		}
		return false;
	case 'N': // Knight
		// Knight can move in an L-shape: two squares in one direction and one square in a perpendicular direction
		if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) ||
			(abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
		{
			return true;
		}
		return false;
	case 'B': // Bishop
		// Bishop can move diagonally any number of squares
		if (abs(toRow - fromRow) == abs(toCol - fromCol) &&
			isClearDiagonalPath(fromRow, fromCol, toRow, toCol))
		{
			return true;
		}
		return false;
	case 'Q': // Queen
		// Queen can move horizontally, vertically, or diagonally any number of squares
		if ((fromRow == toRow && isClearHorizontalPath(fromCol, toCol, fromRow)) ||
			(fromCol == toCol && isClearVerticalPath(fromRow, toRow, fromCol)) ||
			(abs(toRow - fromRow) == abs(toCol - fromCol) &&
			 isClearDiagonalPath(fromRow, fromCol, toRow, toCol)))
		{
			return true;
		}
		return false;
	case 'K': // King
		// King can move one square in any direction
		if (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1)
		{
			return true;
		}
		return false;
	default:
		return false;
	}
}

// Function to generate a random legal move for the computer
string chessBoard_::generateComputerMove()
{
	int kingY, kingX;
	findKingPosition(false, kingY, kingX);
	bool kingIsUnderAttack = isPieceUnderAttack(kingY, kingX);
	string result;

	if (kingIsUnderAttack)
	{
		if (blockBlackRoutes(result))
			return result;
		else
			result = pushBlackKing(kingY, kingX);
	}
	else
		result = randomBlackMove(kingY, kingX);
	// If no valid move is found after maxAttempts, return an empty string or handle the case accordingly
	return result;
}

string chessBoard_::pushBlackKing(int kingY, int kingX)
{
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{

		// Generate random coordinates for the computer's move
		int fromRow = kingY;
		int fromCol = kingX;
		int toRow = rand() % 8;
		int toCol = rand() % 8;

		// cout << (char)(fromCol + 'a') << fromRow + 1 << (char)(toCol + 'a') << toRow + 1 << "\n";

		// Check if the generated move is valid
		if (board[fromRow][fromCol].symbol != '.' &&
			isValidMove(fromRow, fromCol, toRow, toCol) &&
			isBlackPiece(board[fromRow][fromCol].symbol))
		{
			piece_ temp = board[toRow][toCol];
			board[toRow][toCol] = board[kingY][kingX];
			board[kingY][kingX] = piece_('.', 0);
			if (isPieceUnderAttack(toRow, toCol) != true)
			{
				board[toRow][toCol] = temp;
				board[kingY][kingX] = piece_('k', 10);
				return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
			}
			board[kingY][kingX] = piece_('k', 10);
			board[toRow][toCol] = temp;
		}
	}
	return "";
}

string chessBoard_::randomBlackMove(int kingY, int kingX)
{
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{

		// Generate random coordinates for the computer's move
		int fromRow = rand() % 8;
		int fromCol = rand() % 8;
		int toRow = rand() % 8;
		int toCol = rand() % 8;

		// cout << (char)(fromCol + 'a') << fromRow + 1 << (char)(toCol + 'a') << toRow + 1 << "\n";

		// Check if the generated move is valid

		if (board[fromRow][fromCol].symbol != '.' &&
			isValidMove(fromRow, fromCol, toRow, toCol) &&
			isBlackPiece(board[fromRow][fromCol].symbol))
		{
			if (kingY == fromRow &&
				kingX == fromCol)
			{
				piece_ temp = board[toRow][toCol];
				board[toRow][toCol] = board[kingY][kingX];
				board[kingY][kingX] = piece_('.', 0);
				if (isPieceUnderAttack(toRow, toCol) != true)
				{
					board[toRow][toCol] = temp;
					board[kingY][kingX] = piece_('k', 10);
					return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
				}
				board[kingY][kingX] = piece_('k', 10);
				board[toRow][toCol] = temp;
			}
			else
				return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
		}
	}

	return "";
}

bool chessBoard_::blockBlackRoutes(string &result)
{
	vector<vector<int>> pawns(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> knights(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> bishops(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> rooks(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> queens(vector<vector<int>>(0, vector<int>(2)));
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			piece_ piece = board[y][x];
			if (piece.symbol == 'p')
				pawns.push_back({y, x});
			if (piece.symbol == 'n')
				knights.push_back({y, x});
			if (piece.symbol == 'b')
				bishops.push_back({y, x});
			if (piece.symbol == 'r')
				rooks.push_back({y, x});
			if (piece.symbol == 'q')
				queens.push_back({y, x});
		}
	}

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			for (vector<int> piece : pawns)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isBlackKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : knights)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isBlackKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : bishops)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isBlackKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : rooks)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isBlackKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : queens)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isBlackKingSafe(piece[0], piece[1], y, x, result))
					return true;
		}
	}
	return false;
}

bool chessBoard_::isBlackKingSafe(int fromRow, int fromCol, int toRow, int toCol, string &result)
{
	int kingY, kingX;
	findKingPosition(false, kingY, kingX);
	piece_ temp = board[toRow][toCol];
	board[toRow][toCol] = board[fromRow][fromCol];
	piece_ temp2 = board[fromRow][fromCol];
	board[fromRow][fromCol] = piece_('.', 0);
	if (isPieceUnderAttack(kingY, kingX) != true)
	{
		board[toRow][toCol] = temp;
		board[fromRow][fromCol] = temp2;
		result = string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
		return true;
	}
	board[toRow][toCol] = temp;
	board[fromRow][fromCol] = temp2;

	return false;
}

// Function to generate a random legal move for you
string chessBoard_::generateYourMove()
{
	int kingY, kingX;
	findKingPosition(true, kingY, kingX);
	bool kingIsUnderAttack = isPieceUnderAttack(kingY, kingX);
	string result;

	if (kingIsUnderAttack)
	{
		if (blockWhiteRoutes(result))
			return result;
		else
			result = pushWhiteKing(kingY, kingX);
	}
	else
		result = randomWhiteMove(kingY, kingX);
	// If no valid move is found after maxAttempts, return an empty string or handle the case accordingly
	return result;
}

string chessBoard_::pushWhiteKing(int kingY, int kingX)
{
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{

		// Generate random coordinates for the computer's move
		int fromRow = kingY;
		int fromCol = kingX;
		int toRow = rand() % 8;
		int toCol = rand() % 8;

		// cout << (char)(fromCol + 'a') << fromRow + 1 << (char)(toCol + 'a') << toRow + 1 << "\n";

		// Check if the generated move is valid
		if (board[fromRow][fromCol].symbol != '.' &&
			isValidMove(fromRow, fromCol, toRow, toCol) &&
			isWhitePiece(board[fromRow][fromCol].symbol))
		{
			piece_ temp = board[toRow][toCol];
			board[toRow][toCol] = board[kingY][kingX];
			board[kingY][kingX] = piece_('.', 0);
			if (isPieceUnderAttack(toRow, toCol) != true)
			{
				board[toRow][toCol] = temp;
				board[kingY][kingX] = piece_('K', 10);
				return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
			}
			board[kingY][kingX] = piece_('K', 10);
			board[toRow][toCol] = temp;
		}
	}
	return "";
}

string chessBoard_::randomWhiteMove(int kingY, int kingX)
{
	for (int attempt = 0; attempt < maxAttempts; ++attempt)
	{

		// Generate random coordinates for the computer's move
		int fromRow = rand() % 8;
		int fromCol = rand() % 8;
		int toRow = rand() % 8;
		int toCol = rand() % 8;

		// cout << (char)(fromCol + 'a') << fromRow + 1 << (char)(toCol + 'a') << toRow + 1 << "\n";

		// Check if the generated move is valid

		if (board[fromRow][fromCol].symbol != '.' &&
			isValidMove(fromRow, fromCol, toRow, toCol) &&
			isWhitePiece(board[fromRow][fromCol].symbol))
		{
			if (kingY == fromRow &&
				kingX == fromCol)
			{
				piece_ temp = board[toRow][toCol];
				board[toRow][toCol] = board[kingY][kingX];
				board[kingY][kingX] = piece_('.', 0);
				if (isPieceUnderAttack(toRow, toCol) != true)
				{
					board[toRow][toCol] = temp;
					board[kingY][kingX] = piece_('K', 10);
					return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
				}
				board[kingY][kingX] = piece_('K', 10);
				board[toRow][toCol] = temp;
			}
			else
				return string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
		}
	}

	return "";
}

bool chessBoard_::blockWhiteRoutes(string &result)
{
	vector<vector<int>> pawns(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> knights(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> bishops(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> rooks(vector<vector<int>>(0, vector<int>(2)));
	vector<vector<int>> queens(vector<vector<int>>(0, vector<int>(2)));
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			piece_ piece = board[y][x];
			if (piece.symbol == 'P')
				pawns.push_back({y, x});
			if (piece.symbol == 'N')
				knights.push_back({y, x});
			if (piece.symbol == 'B')
				bishops.push_back({y, x});
			if (piece.symbol == 'R')
				rooks.push_back({y, x});
			if (piece.symbol == 'Q')
				queens.push_back({y, x});
		}
	}

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			for (vector<int> piece : pawns)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isWhiteKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : knights)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isWhiteKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : bishops)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isWhiteKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : rooks)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isWhiteKingSafe(piece[0], piece[1], y, x, result))
					return true;

			for (vector<int> piece : queens)
				if (isValidMove(piece[0], piece[1], y, x) &&
					isWhiteKingSafe(piece[0], piece[1], y, x, result))
					return true;
		}
	}
	return false;
}

bool chessBoard_::isWhiteKingSafe(int fromRow, int fromCol, int toRow, int toCol, string &result)
{
	int kingY, kingX;
	findKingPosition(true, kingY, kingX);
	piece_ temp = board[toRow][toCol];
	board[toRow][toCol] = board[fromRow][fromCol];
	piece_ temp2 = board[fromRow][fromCol];
	board[fromRow][fromCol] = piece_('.', 0);
	if (isPieceUnderAttack(kingY, kingX) != true)
	{
		board[toRow][toCol] = temp;
		board[fromRow][fromCol] = temp2;
		result = string() + (char)(fromCol + 'a') + to_string(fromRow + 1) + (char)(toCol + 'a') + to_string(toRow + 1);
		return true;
	}
	board[toRow][toCol] = temp;
	board[fromRow][fromCol] = temp2;

	return false;
}

int chessBoard_::calculateWhiteScore() const
{
	int score = 0;

	// Loop through the entire board
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			piece_ piece = board[row][col];
			if (isWhitePiece(piece.symbol))
			{
				// Add points based on the value of the piece
				score += piece.value;

				// Subtract half the point if the piece is under attack
				if (isPieceUnderAttack(row, col))
				{
					score -= (piece.value / 2);
				}
			}
		}
	}

	return score;
}

int chessBoard_::calculateBlackScore() const
{
	int score = 0;

	// Loop through the entire board
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			piece_ piece = board[row][col];
			if (isBlackPiece(piece.symbol))
			{
				// Add points based on the value of the piece
				score += piece.value;

				// Subtract half the point if the piece is under attack
				if (isPieceUnderAttack(row, col))
				{
					score -= (piece.value / 2);
				}
			}
		}
	}

	return score;
}

void chessBoard_::findKingPosition(bool isWhite, int &row, int &col) const
{
	char kingSymbol = (isWhite) ? 'K' : 'k';

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (board[i][j].symbol == kingSymbol)
			{
				row = i;
				col = j;
				return;
			}
		}
	}
}

bool chessBoard_::isPieceUnderAttack(int row, int col) const
{

	// Check for attacks from opponent
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if (isValidMove(y, x, row, col))
			{
				return true;
			}
		}
	}

	return false;
}

bool chessBoard_::isPieceAttacking(int row, int col) const
{
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if (isValidMove(row, col, y, x) && board[y][x].symbol != '.')
			{
				return true;
			}
		}
	}
	return false;
}

// Function to check if two pieces have the same color
bool chessBoard_::isSameColor(char piece1, char piece2) const
{
	return (isWhitePiece(piece1) && isWhitePiece(piece2)) || (isBlackPiece(piece1) && isBlackPiece(piece2));
}

// Function to check if a piece is white
bool chessBoard_::isWhitePiece(char piece) const
{
	return piece >= 'A' && piece <= 'Z';
}

// Function to check if a piece is black
bool chessBoard_::isBlackPiece(char piece) const
{
	return piece >= 'a' && piece <= 'z';
}

// Function to check if the horizontal path is clear for the Rook
bool chessBoard_::isClearHorizontalPath(int fromCol, int toCol, int row) const
{
	int start = min(fromCol, toCol) + 1;
	int end = max(fromCol, toCol);

	for (int col = start; col < end; ++col)
	{
		if (board[row][col].symbol != '.')
		{
			return false; // There is a piece in the way
		}
	}

	return true; // The path is clear
}

// Function to check if the vertical path is clear for the Rook
bool chessBoard_::isClearVerticalPath(int fromRow, int toRow, int col) const
{
	int start = min(fromRow, toRow) + 1;
	int end = max(fromRow, toRow);

	for (int row = start; row < end; ++row)
	{
		if (board[row][col].symbol != '.')
		{
			return false; // There is a piece in the way
		}
	}

	return true; // The path is clear
}

// Function to check if the diagonal path is clear for the Bishop
bool chessBoard_::isClearDiagonalPath(int fromRow, int fromCol, int toRow, int toCol) const
{

	int rowStep = (toRow > fromRow) ? 1 : -1;
	int colStep = (toCol > fromCol) ? 1 : -1;

	int row = fromRow + rowStep;
	int col = fromCol + colStep;
	// cout << board[row][col].symbol << endl;
	while (row != toRow || col != toCol)
	{
		if (board[row][col].symbol != '.')
		{

			return false; // There is a piece in the way
		}

		row += rowStep;
		col += colStep;
	}

	return true; // The path is clear
}

bool chessBoard_::isCheckmate(bool isWhite) const
{
	char kingSymbol = (isWhite) ? 'K' : 'k';

	// Find the king's position
	int kingRow, kingCol;
	findKingPosition(isWhite, kingRow, kingCol);

	// Check if the king is under attack
	if (isPieceUnderAttack(kingRow, kingCol))
		return true;

	return false;
}

bool chessBoard_::isStalemate() const
{
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if (board[y][x].symbol != 'K' && board[y][x].symbol != 'k' && board[y][x].symbol != '.')
			{
				return false;
			}
		}
	}
	return true;
}

void chessBoard_::writeBoardToFile(const std::string &filename) const
{
	std::ofstream outputFile(filename, std::ios::app);

	if (!outputFile.is_open())
	{
		std::cerr << "Error: Unable to open the file: " << filename << std::endl;
		return;
	}

	for (int i = 7; i >= 0; --i)
	{
		outputFile << i + 1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			if (isPieceAttacking(i, j) && board[i][j].symbol != '.')
				outputFile << board[i][j].symbol;
			else if (isPieceUnderAttack(i, j) && board[i][j].symbol != '.')
				outputFile << board[i][j].symbol;
			else
				outputFile << board[i][j].symbol << " ";
		}
		outputFile << std::endl;
	}

	outputFile << "-----------------------" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		if (i < 1)
		{
			outputFile << "  ";
		}
		// Assuming you want to print 'a' through 'h'
		char current_char = 'a' + i;
		outputFile << current_char << " ";
	}
	outputFile << "\n";

	std::cout << "\nBoard written to file: " << filename << std::endl;
	outputFile.close();
}

void chessBoard_::writeScoresToFile(const std::string &filename) const
{
	std::ofstream outputFile(filename, std::ios::app);

	if (!outputFile.is_open())
	{
		std::cerr << "Error: Unable to open the file: " << filename << std::endl;
		return;
	}

	outputFile << "\n   W\tB\n";
	outputFile << "  " << calculateWhiteScore() << "\t" << calculateBlackScore() << "\n";

	outputFile.close();
}

void chessBoard_::writeWMovesToFile(const std::string &filename, const string &a) const
{
	std::ofstream outputFile(filename, std::ios::app);

	if (!outputFile.is_open())
	{
		std::cerr << "Error: Unable to open the file: " << filename << std::endl;
		return;
	}
	outputFile << "White's move: " << a << endl;

	outputFile.close();
}

void chessBoard_::writeBMovesToFile(const std::string &filename, const string &a) const
{
	std::ofstream outputFile(filename, std::ios::app);

	if (!outputFile.is_open())
	{
		std::cerr << "Error: Unable to open the file: " << filename << std::endl;
		return;
	}
	outputFile << "Black's move: " << a << endl;
	outputFile.close();
}