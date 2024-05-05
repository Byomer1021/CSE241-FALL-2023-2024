// chess.h

#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class piece_
{
public:
	char symbol; // K, Q, R, N, B, P
	int value;	 // Point value of the piece

	piece_(char s, int v) : symbol(s), value(v) {}
};

class chessBoard_
{
public:
	chessBoard_();

	void displayBoard() const;
	bool makeMove(const string &move);

	string generateComputerMove();
	string pushBlackKing(int kingY, int kingX);
	string randomBlackMove(int kingY, int kingX);
	bool blockBlackRoutes(string &result);
	bool isBlackKingSafe(int fromRow, int fromCol, int toRow, int toCol, string &result);

	string generateYourMove();
	string pushWhiteKing(int kingY, int kingX);
	string randomWhiteMove(int kingY, int kingX);
	bool blockWhiteRoutes(string &result);
	bool isWhiteKingSafe(int fromRow, int fromCol, int toRow, int toCol, string &result);

	bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
	bool isSameColor(char piece1, char piece2) const;
	bool isWhitePiece(char piece) const;
	bool isBlackPiece(char piece) const;
	bool isClearHorizontalPath(int fromCol, int toCol, int row) const;
	bool isClearVerticalPath(int fromRow, int toRow, int col) const;
	bool isClearDiagonalPath(int fromRow, int fromCol, int toRow, int toCol) const;
	int calculateWhiteScore() const;
	int calculateBlackScore() const;
	bool isCheckmate(bool isWhite) const;
	bool isStalemate() const;
	void findKingPosition(bool isWhite, int &row, int &col) const;
	void writeBoardToFile(const std::string &filename) const;
	void writeScoresToFile(const std::string &filename) const;
	void writeWMovesToFile(const std::string &filename, const string &a) const;
	void writeBMovesToFile(const std::string &filename, const string &a) const;

private:
	std::vector<std::vector<piece_>> board; // 2D vector to represent the chess board

	// Function to check if a piece is under attack or atacking
	bool isPieceUnderAttack(int row, int col) const;
	bool isPieceAttacking(int row, int col) const;
};

#endif

string whiteInput(chessBoard_ &chess);
bool whiteMove(chessBoard_ &chess, const string move);
string blackInput(chessBoard_ &chess);
bool blackMove(chessBoard_ &chess, const string move);
