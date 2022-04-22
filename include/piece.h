#ifndef PIECE
#define PIECE

#include <iostream>
#include <string>

#include "enum.h"
using namespace std;

class Piece {

  private:
    Color color;
    string name;

  public:
    /**
     * @brief Construct a new Piece object
     *
     * @param col (color)
     * @param str (name)
     */
    Piece(Color col, string str);

    /**
     * @brief Destroy the Piece object
     */
    virtual ~Piece();

    /**
     * @brief Print the piece
     */
    void print();

    /**
     * @brief Get the color of the piece
     * @return Color
     */
    Color get_color() const;

    /**
     * @brief Get the name object
     * @return string
     */
    string get_name() const;

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    virtual bool get_castling() const = 0;

    /**
     * @brief Set the castling of piece on true
     */
    virtual void set_castling() = 0;

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    virtual void promotion(int x, int y, Piece *chess_tab[8][8],
                           Color color) = 0;

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    virtual bool is_valid_move(int init_x, int init_y, int dest_x,
                               int dest_y,
                               Piece *chess_tab[8][8]) = 0;
};

class Bishop : public Piece {

  private:
    // indicate if the king has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new Bishop object
     *
     * @param col
     * @param str
     */
    Bishop(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8],
                   Color color) {}

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

class Knight : public Piece {

  private:
    // indicate if the king has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new Knight object
     *
     * @param col
     * @param str
     */
    Knight(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8],
                   Color color) {}

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

class Queen : public Piece {

  private:
    // indicate if the king has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new Queen object
     *
     * @param col
     * @param str
     */
    Queen(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8],
                   Color color) {}

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

class Rook : public Piece {

  private:
    // indicate if the rook has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new Rook object
     *
     * @param col
     * @param str
     */
    Rook(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8],
                   Color color) {}

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

class King : public Piece {

  private:
    // indicate if the king has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new King object
     *
     * @param col
     * @param str
     */
    King(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8],
                   Color color) {}

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

class Pawn : public Piece {

  private:
    // indicate if the king has been castled
    bool castling;

  public:
    /**
     * @brief Construct a new Pawn object
     *
     * @param col
     * @param str
     */
    Pawn(Color col, string str);

    /**
     * @brief Observe if the piece has been moved
     * @return true
     * @return false
     */
    bool get_castling() const;

    /**
     * @brief Set the castling of piece on true
     */
    void set_castling();

    /**
     * @brief Manage the promotion of the pawn when the pawn reach the
     * last line of the chessboard
     * @param x
     * @param y
     * @param chess_tab
     * @param color
     */
    void promotion(int x, int y, Piece *chess_tab[8][8], Color color);

    /**
     * @brief Check if the move is valid for the piece selected
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @param chess_tab
     * @return true
     * @return false
     */
    bool is_valid_move(int init_x, int init_y, int dest_x, int dest_y,
                       Piece *chess_tab[8][8]);
};

#endif
