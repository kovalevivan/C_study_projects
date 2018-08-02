#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include<time.h>

#define ROWS 20
#define COLUMNS 20
#define ALIVE_LABEL '*'
#define DEAD_LABEL '-'

void showField(char first[][COLUMNS], int alive);

void fillField(char first[][COLUMNS], int number);

//void makeBorder(char first[][COLUMNS]);

void copy(char from[][COLUMNS], char to[][COLUMNS]);

void makeStep(char first[][COLUMNS], char second[][COLUMNS]);


int countAlive(char first[][COLUMNS]);



int main() {

	srand(time(NULL));

	//initial parametres

	int alive = 100; //number of alive cell
	int delay = 1000; //miliseconds
	static int number_of_steps = 0;


	char field[ROWS][COLUMNS];

	char tmp_field[ROWS][COLUMNS];

	fillField(field, alive);

	int boolean = 1;

	while (boolean > 0)
	{

		alive = countAlive(field);

		showField(field, alive);

		Sleep(delay);

		system("cls");

		makeStep(field, tmp_field);

		boolean = isEqual(tmp_field, field);

		number_of_steps++;

		copy(tmp_field, field);


	}



	showField(field, alive);

	if (alive > 0)
	{
		printf("\nCongratulations! Your world reached stable state in %d step.\n", number_of_steps);

	}
	else {
		printf("\nYour world died at %dth step!\n", number_of_steps);
	}

}

void showField(char first[][COLUMNS], int alive)
{
	printf("Number of alives --> %d\n", alive);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			printf("%c", first[i][j]);
		}
		puts("");
	}
}


void fillField(char first[][COLUMNS], int number)
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			first[i][j] = DEAD_LABEL;
		}
	}

	for (int n = 0; n < number; n++)
	{
		int i = rand()%ROWS;
		int j = rand()%COLUMNS;

		if (first[i][j] == ALIVE_LABEL)
			n--;
		else
			first[i][j] = ALIVE_LABEL;

	}
}

void copy(char from[][COLUMNS], char to[][COLUMNS])
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			to[i][j] = from[i][j];
		}
	}
}

void makeStep(char first[][COLUMNS], char second[][COLUMNS])
{
	int count = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			int count = 0;

			if (first[(i + ROWS - 1) % ROWS][(j + COLUMNS - 1) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS - 1) % ROWS][(j + COLUMNS    ) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS - 1) % ROWS][(j + COLUMNS + 1) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS    ) % ROWS][(j + COLUMNS - 1) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS    ) % ROWS][(j + COLUMNS + 1) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS + 1) % ROWS][(j + COLUMNS - 1) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS + 1) % ROWS][(j + COLUMNS    ) % COLUMNS] == ALIVE_LABEL) count++;
			if (first[(i + ROWS + 1) % ROWS][(j + COLUMNS + 1) % COLUMNS] == ALIVE_LABEL) count++;

			if (count == 2)
			{
				second[i][j] = first[i][j];
			}
			else if (count == 3)
			{
				second[i][j] = ALIVE_LABEL;
			}
			else
			{
				second[i][j] = DEAD_LABEL;
			}
		}
	}

}


int countAlive(char first[][COLUMNS])
{
	int count = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (first[i][j] == ALIVE_LABEL)
				count++;
		}
	}

	return count;

}

int isEqual(char first[][COLUMNS], char second[][COLUMNS])
{
	int sum_of_equal_elem = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			sum_of_equal_elem += first[i][j] == second[i][j] ? 1 : 0;
		}
	}

	if (sum_of_equal_elem == COLUMNS*ROWS)
	{
		return 0;
	}
	else {

		return 1;
	}
}