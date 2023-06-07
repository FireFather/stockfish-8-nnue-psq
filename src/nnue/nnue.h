/*
  Thanks to Yu Nasu, Hisayori Noda, this implementation adapted from R. De Man
  and Daniel Shaw's Cfish nnue probe code https://github.com/dshawul/nnue-probe
*/

#pragma once

#ifndef __cplusplus
#ifndef _MSC_VER
#include <stdalign.h>
#endif
#endif

/**
* Calling convention
*/
#ifdef __cplusplus
#   define EXTERNC extern "C"
#else
#   define EXTERNC
#endif

#if defined (_WIN32)
#   define _CDECL __cdecl
#ifdef DLL_EXPORT
#   define DLLExport EXTERNC __declspec(dllexport)
#else
#   define DLLExport EXTERNC __declspec(dllimport)
#endif
#else
#   define _CDECL
#   define DLLExport EXTERNC
#endif

/**
* Internal piece representation
*     wking=1, wqueen=2, wrook=3, wbishop= 4, wknight= 5, wpawn= 6,
*     bking=7, bqueen=8, brook=9, bbishop=10, bknight=11, bpawn=12
*
* Make sure the pieces you pass to the library from your engine
* use this format.
*/
enum colors
{
	white_nnue, black_nnue
};
enum pieces
{
	blank = 0, wking, wqueen, wrook, wbishop, wknight, wpawn,
	bking, bqueen, brook, bbishop, bknight, bpawn
};

/**
* nnue data structure
*/

typedef struct dirty_piece
{
	int dirty_num;
	int pc[3];
	int from[3];
	int to[3];
} dirty_piece;

typedef struct Accumulator
{
	alignas(64) int16_t accumulation[2][256];
	int computed_accumulation;
} Accumulator;

typedef struct nnue_data
{
	Accumulator accumulator;
	dirty_piece dirtyPiece;
} nnue_data;

/**
* position data structure passed to core subroutines
*  See nnue_evaluate for a description of parameters
*/
typedef struct position
{
	int player;
	int* pieces;
	int* squares;
	nnue_data* nnue[3];
} position;

int nnue_evaluate_pos(position* pos);

/************************************************************************
*         EXTERNAL INTERFACES
*
* Load a NNUE file using
*
*   nnue_init(file_path)
*
* and then probe score using one of three functions, whichever
* is convenient. From easy to hard
*
*   a) nnue_evaluate_fen         - accepts a fen string for evaluation
*   b) nnue_evaluate             - suitable for use in engines
*   c) nnue_evaluate_incremental - for ultimate performance but will need
*                                  some work on the engines side.
*
**************************************************************************/

/**
* Load NNUE file
*/
void _CDECL nnue_init
(
	const char* eval_file             /** Path to NNUE file */
);

/**
* Evaluate on FEN string
* Returns
*   Score relative to side to move in approximate centipawns
*/
int _CDECL nnue_evaluate_fen
(
	const char* fen                   /** FEN string to probe evaluation for */
);

/**
* Evaluation subroutine suitable for chess engines.
* -------------------------------------------------
* Piece codes are
*     wking=1, wqueen=2, wrook=3, wbishop= 4, wknight= 5, wpawn= 6,
*     bking=7, bqueen=8, brook=9, bbishop=10, bknight=11, bpawn=12,
* Squares are
*     A1=0, B1=1 ... H8=63
* Input format:
*     piece[0] is white king, square[0] is its location
*     piece[1] is black king, square[1] is its location
*     ..
*     piece[x], square[x] can be in any order
*     ..
*     piece[n+1] is set to 0 to represent end of array
* Returns
*   Score relative to side to move in approximate centipawns
*/
int _CDECL nnue_evaluate
(
	int player,                       /** Side to move: white=0 black=1 */
	int* pieces,                      /** Array of pieces */
	int* squares                      /** Corresponding array of squares each piece stands on */
);

/**
* Incremental NNUE evaluation function.
* -------------------------------------------------
* First three parameters and return type are as in nnue_evaluate
*
* nnue_data
*    nnue_data[0] is pointer to NNUEdata for ply i.e. current position
*    nnue_data[1] is pointer to NNUEdata for ply - 1
*    nnue_data[2] is pointer to NNUEdata for ply - 2
*/
int _CDECL nnue_evaluate_incremental
(
	int player,                       /** Side to move: white=0 black=1 */
	int* pieces,                      /** Array of pieces */
	int* squares,                     /** Corresponding array of squares each piece stands on */
	nnue_data** nnue			      /** Pointer to NNUEdata* for current and previous plies */
);

