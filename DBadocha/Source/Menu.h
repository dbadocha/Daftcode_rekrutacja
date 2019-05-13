#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef unsigned short int usint_td;

enum Kierunek {
	W_GORE = 0x48,
	W_DOL = 0x50,
	W_LEWO = 0x4B,
	W_PRAWO = 0x4D,
	ENTER = 0x0D
};

typedef struct MenuArray MenuArray;

struct MenuArray {
	int ArraySize;
	char **MenuArray;
};

int menu(char *name, usint_td orient, usint_td array_size, char *options_array[]);