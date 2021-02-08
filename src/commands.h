#ifndef COMMANDS_H
#define COMMANDS_H

#define NO 0
#define YES 1

enum COMMANDS {
	// start at 2 so it doesn't clash 
	// with the #define'd YES and NO
	// I'm not sure if this is actually important,
	// it just popped into my mind and I don't want
	// to risk anything
	RESIGN = 2,
	DRAW,
	FLIP,
	QUIT,
	HELP,
	MOVE,
	ILLEGAL // invalid command
};

char* get_command(char* buffer, const int size, const int turn);
int validate_command(char* command);
int get_yn(char* buffer, const int size, const int turn);

#endif