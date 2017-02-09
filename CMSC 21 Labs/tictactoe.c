#include <stdio.h>

void init(char grid[3][3]);
void display(char grid[3][3]);
int checkWin(char grid[3][3]);

int main() {
	int player, row, column, round;
	char grid[3][3];
	char choice;

	do {
		init(grid);
		player = 1;
		display(grid);

		for(round = 0; round < 9; round ++) {
			printf("Player %i:\n", player);
			
			do {
				do {
					printf("Enter row: ");
					scanf("%i", &row);
				} while(row > 3 || row < 1);

				do {
					printf("Enter column: ");
					scanf("%i", &column);
				} while(column > 3 || column < 1);
			} while(grid[row-1][column-1] != ' ');

			if(player == 1) {
				grid[row-1][column-1] = 'X';
				player = 2;
			}
			else {
				grid[row-1][column-1] = 'O';
				player = 1;
			}

			display(grid);

			int winner = checkWin(grid);

			if(winner > 0) {
				printf("Player %i wins!\n", winner);
				break;
			} else if(round == 8)
				printf("It's a tie!\n");
		}
		printf("Do you want to play again? (Y/N) ");
		scanf("%c", &choice);
	} while(choice == 'y' || choice == 'Y');
}

void init(char grid[3][3]) {
	for(int i = 0; i < 3; i ++) {
		for(int j = 0; j < 3; j ++) {
			grid[i][j] = ' ';
		}
	}
}

void display(char grid[3][3]) {
	printf("%c|%c|%c\n", grid[0][0], grid[0][1], grid[0][2]);
	printf("-+-+-\n");
	printf("%c|%c|%c\n", grid[1][0], grid[1][1], grid[1][2]);
	printf("-+-+-\n");
	printf("%c|%c|%c\n", grid[2][0], grid[2][1], grid[2][2]);
}

int checkWin(char grid[3][3]) {
	char sym = grid[0][0];

	if(sym != ' ') {
		if(grid[0][1] == sym && grid[0][2] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}

		if(grid[1][0] == sym && grid[2][0] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}

		if(grid[1][1] == sym && grid[2][2] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}
	}

	sym = grid[0][2];

	if(sym != ' ') {
		if(grid[1][1] == sym && grid[2][0] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}

		if(grid[1][2] == sym && grid[2][2] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}
	}

	sym = grid[0][1];

	if(sym != ' ') {
		if(grid[1][1] == sym && grid[2][1] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}
	}

	sym = grid[1][0];

	if(sym != ' ') {
		if(grid[1][1] == sym && grid[1][2] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}
	}

	sym = grid[2][0];

	if(sym != ' ') {
		if(grid[2][1] == sym && grid[2][2] == sym) {
			if(sym == 'X')
				return 1;
			else
				return 2;
		}
	}

	return 0;
}