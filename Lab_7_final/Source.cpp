#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void START_spawn()
{
	int sn, sy, i;
	for (i = 0; i < 20; i++) {
		sn = (rand() % 61) + 10;
		sy = (rand() % 4) + 2;
		while (cursor(sn, sy) == '*') {
			sn = (rand() % 61) + 10;
			sy = (rand() % 4) + 2;
		}
		gotoxy(sn, sy);
		printf("*");
	}
}
void NEW_spawn()
{
	int nx, ny;
	nx = (rand() % 61) + 10;
	ny = (rand() % 4) + 2;
	while (cursor(nx, ny) == '*') {
		nx = (rand() % 61) + 10;
		ny = (rand() % 4) + 2;
	}
	gotoxy(nx, ny);
	printf("*");
}

int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int bx, by;
	int bullet = 0;
	int scores = 0;
	srand(time(NULL));
	START_spawn();
	gotoxy(65, 0);
	printf("score : %d", scores);
	draw_ship(x, y);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {

			clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else {
				if (cursor(bx, by - 1) == '*') {
					scores++;
					gotoxy(65, 0);
					printf("score : %d", scores);
					draw_bullet(bx, --by);
					Beep(300, 100);
					clear_bullet(bx, by);
					NEW_spawn();
					bullet = 0;
				}
				else { draw_bullet(bx, --by); Beep(600, 100); }
			}

		}

		Sleep(100);
	} while (ch != 'x');
	return 0;
}