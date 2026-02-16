#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

/////////////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////////////

template <typename T> class Player;
template <typename T> class Move;

/////////////////////////////////////////////////////////////
// Class declarations
/////////////////////////////////////////////////////////////

/**
 * @brief Represents the type of player in the game.
 */
enum class PlayerType {
    HUMAN,     ///< A human player.
    COMPUTER,  ///< A computer-controlled player.
};

/**
 * @brief Base template for any board used in board games.
 *
 * @tparam T Type of the elements stored on the board (e.g., char, int, string).
 *
 * Provides core data (rows, columns, matrix) and virtual methods to be
 * implemented by specific games like Tic-Tac-Toe, Connect4, etc.
 */
template <typename T>
class Board {
protected:
    int rows;        ///< Number of rows
    int columns;     ///< Number of columns
    vector<vector<T>> board; ///< 2D vector for the board
    int n_moves = 0; ///< Number of moves made

public:
    /**
     * @brief Construct a board with given dimensions.
     */
    Board(int rows, int columns)
        : rows(rows), columns(columns), board(rows, vector<T>(columns)) {}

    /**
     * @brief Virtual destructor. Frees allocated board memory.
     */
    virtual ~Board() {}

    /**
     * @brief Update the board with a new move.
     * @param move The move object containing position and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    virtual bool update_board(Move<T>* move) = 0;

    /** @brief Check if a player has won. */
    virtual bool is_win(Player<T>*) = 0;

    /** @brief Check if a player has lost. */
    virtual bool is_lose(Player<T>*) = 0;

    /** @brief Check if the game ended in a draw. */
    virtual bool is_draw(Player<T>*) = 0;

    /** @brief Check if the game is over. */
    virtual bool game_is_over(Player<T>*) = 0;

    /**
     * @brief Return a copy of the current board as a 2D vector.
     */
    vector<vector<T>> get_board_matrix() const {
        return board;
    }

    /** @brief Get number of rows. */
    int get_rows() const { return rows; }

    /** @brief Get number of columns. */
    int get_columns() const { return columns; }

    T get_cell(int x, int y) {
        return board[x][y];
    }

};

//-----------------------------------------------------
/**
 * @brief Represents a single move in a board game.
 *
 * @tparam T Type of symbol placed on the board (e.g., char, int).
 */
template <typename T>
class Move {
    int x;      ///< Row index
    int y;      ///< Column index
    T symbol;   ///< Symbol used in the move

public:
    /** @brief Construct a move at (x, y) using a symbol. */
    Move(int x, int y, T symbol) : x(x), y(y), symbol(symbol) {}

    /** @brief Get row index. */
    int get_x() const { return x; }

    /** @brief Get column index. */
    int get_y() const { return y; }

    /** @brief Get the move symbol. */
    T get_symbol() const { return symbol; }
};

//-----------------------------------------------------
/**
 * @brief Base template for all players (human or AI).
 *
 * @tparam T Type of symbol used by the player.
 */
template <typename T>
class Player {
protected:
    string name;         ///< Player name
    PlayerType type;     ///< Player type (e.g., HUMAN or COMPUTER)
    T symbol;            ///< Player�s symbol on board
    Board<T>* boardPtr;  ///< Pointer to the game board

public:
    /**
     * @brief Construct a player with name, symbol, and type.
     */
    Player(string n, T s, PlayerType t)
        : name(n), symbol(s), type(t), boardPtr(nullptr) {}

    virtual ~Player() {}

    /** @brief Get the player's name. */
    string get_name() const { return name; }

    /** @brief Get player type (e.g., 'H' or 'C'). */
    PlayerType get_type() const { return type; }

    /** @brief Get the player's symbol. */
    T get_symbol() const { return symbol; }

    /** @brief Get a pointer to the game board. */
    Board<T>* get_board_ptr() const { return boardPtr; }

    /** @brief Assign the board pointer for the player. */
    void set_board_ptr(Board<T>* b) { boardPtr = b; }
};


#endif // _BOARDGAME_CLASSES_H
