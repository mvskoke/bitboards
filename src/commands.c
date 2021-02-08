/** commands.c

Implements functions for user input at cmdline.

Gets commands from user.
Validates commands.
Can also get a "yes" or "no" response.

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "colors.h"

/* get_command()
	@buffer 	char array to place user's input
	@size 		max num of chars to read, including '\0'
	@turn 		current turn: BLACK or WHITE

	@return 	str containg the command. 

	But really, the return value just points to the contents
	of *buffer. strtok()'s destructiveness allows the caller
	to treat the entire buffer as one safely null-terminated
	string, even if garbage chars may be left over in some
	parts of it. strtok() just cuts out the garbage for us.

	Read in cmdline input into a buffer to get a command.
	Treats the first token separated by whitespaces as the 
	command.
*/
char* get_command(char* buffer, const int size, const int turn)
{
	char delims[] = " \r\n\t";
	char* token = NULL;

	turn == BLACK ? printf("Black >>> ") : printf("White >>> ");

	do
	{
		fgets(buffer, size, stdin);
	} while ((token = strtok(buffer, delims)) == NULL);

	// returning local ptr, but only the address it contains
	// is important. main() will still be able to use it
	// because it accesses the contents of *buffer
	return token;
}

/* to_lowercase()

	Converts a null-terminated string to all lowercase.
*/
static void to_lowercase(char* s)
{
	char* tmp = s;
	while (*tmp != '\0')
	{
		*tmp = tolower(*tmp);
		tmp++;
	}
}

/* validate_one_char()
	@return 	command enum type

	Validates a single-character command.
*/
static int validate_one_char(char c)
{
	switch (c)
	{
	case 'r': return RESIGN;
	case 'd': return DRAW;
	case 'f': return FLIP;
	case 'q': return QUIT;
	case 'h': return HELP;
	default:  return ILLEGAL;
	}
}

/* validate_promotion()
	@return 	MOVE (it's a legal command) or ILLEGAL.

	Validates a promotion move. Must go from 7th rank to 8th
	rank. Promotion file must be within 1 char of the starting
	file and on a legal file e.g. e7 > d8,e8,f8 or a7 > a8,b8
*/
static int validate_promotion(char* command)
{
	int sq1 = command[0] >= 'a' && command[0] <= 'h';
	int sq2 = command[2] >= 'a' && command[2] <= 'h';

	// the check for promo_sq WILL approve moves like
	// h7i8q, but sq1 and sq2 take care of that
	int promo_sq =  command[0] == command[2]-1 ||
			command[0] == command[2]   ||
			command[0] == command[2]+1;

	int first_rank = command[1] == '7';
	int promo_rank = command[3] == '8';

	if (sq1 && sq2 && first_rank && promo_rank && promo_sq)
	{
		switch (command[4])
		{
		case 'n':
		case 'b':
		case 'r':
		case 'q': return MOVE;
		default:  return ILLEGAL;
		}
	}
	return ILLEGAL;
}

/* validate_move()
	@return 	MOVE (it's a legal command) or ILLEGAL.

	Validates a move command. Must start and end on legal file,
	i.e. file a through h. Must start and end on legal rank,
	i.e. rank 1 through 8.
*/
static int validate_move(char* command)
{
	// check each index:
	// char* "e 2 e 4"
	// index  0 1 2 3
	int char0 = command[0] >= 'a' && command[0] <= 'h';
	int char2 = command[2] >= 'a' && command[2] <= 'h';

	int char1 = command[1] >= '1' && command[1] <= '8';
	int char3 = command[3] >= '1' && command[3] <= '8';

	int same_sq = command[0] == command [2] &&
		      command[1] == command[3];

	if (char0 && char1 && char2 && char3 && !same_sq)
	{
		return MOVE;
	}
	return ILLEGAL;
}

/* validate_command()
	@command 	str containing user's inputted command

	@return 	enum type of the command

	The way this module is designed, char* command should 
	point to a location within the buffer used in
	get_command(), i.e., the paramter *command should be
	the return value of get_command()

	When validating MOVE command, IT ONLY VALIDATES SYNTAX!
	The move.c module should  validate if it's a LEGAL move
	or not when given the board position.

	Validates the SYNTAX of command retrieved by get_command()
*/
int validate_command(char* command)
{
	int len = strlen(command);
	char copy[len+1];

	// convert to lowercase for easier checking
	// commands are case-insensitive anyways
	strcpy(copy, command);
	/* I have to use a strcpy here because the Unity tests pass
	in a string literal to this function, and when this func
	used to call to_lowercase(command), it segfaults because
	you can't dereference the memory of a literal... I think */
	to_lowercase(copy);

	if (len == 1)
	{
		// single-char commands i.e. r d f h q
		return validate_one_char(copy[0]);
	}
	else if (len == 4)
	{
		// normal moves e.g. e2e4
		return validate_move(copy);
	}
	else if (len == 5)
	{
		// pawn promotion e.g. a7a8q
		return validate_promotion(copy);
	}
	return ILLEGAL;
}

/* validate_yn()
	@str 		any string

	@return 	YES, NO, or ILLEGAL

	Checks if a string is a yes or no.
*/
static int validate_yn(char* str)
{
	to_lowercase(str);

	if (!strcmp(str, "yes") || !strcmp(str, "y"))
	{
		return YES;
	}
	else if (!strcmp(str, "no") || !strcmp(str, "n"))
	{
		return NO;
	}
	return ILLEGAL;
}

/* get_yn()
	@buffer 	char array to place user's input
	@size 		max num of chars to read, including '\0'
	@turn 		current turn: BLACK or WHITE

	@return 	user's answer, YES or NO

	Gets a yes-no response from user input. Asks for input
	until valid response is given.
*/
int get_yn(char* buffer, const int size, const int turn)
{
	char* input = NULL;
	int answer;
	do
	{
		input = get_command(buffer, size, turn);
	} while ((answer = validate_yn(input)) == ILLEGAL);
	return answer;
}
