#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Использование: %s <устройство_tty>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* 1. Открываем оригинальный терминал для отправки координат */
	FILE *orig_tty = fopen("/dev/tty", "w");
	if (!orig_tty) {
		perror("Не удалось открыть /dev/tty");
		exit(EXIT_FAILURE);
	}

	/* 2. Открываем целевой TTY для ввода и вывода */
	FILE *tty_in = fopen(argv[1], "r");
	FILE *tty_out = fopen(argv[1], "w");
	if (!tty_in || !tty_out) {
		perror("Не удалось открыть целевой TTY. Проверьте права доступа.");
		fclose(orig_tty);
		exit(EXIT_FAILURE);
	}

	/* 3. Инициализируем ncurses для целевого TTY */
	const char *term_type = getenv("TERM") ? getenv("TERM") : "xterm";
	SCREEN *target_screen = newterm(term_type, tty_out, tty_in);
	if (!target_screen) {
		fprintf(stderr, "Не удалось инициализировать ncurses для %s\n", argv[1]);
		fclose(tty_in);
		fclose(tty_out);
		fclose(orig_tty);
		exit(EXIT_FAILURE);
	}

	/* Делаем этот экран активным по умолчанию для функций curses */
	set_term(target_screen);

	/* Настройка режима ввода */
	noecho();               /* Не отображать нажимаемые клавиши */
	cbreak();               /* Отключить буферизацию строк, читать по символу */
	keypad(stdscr, TRUE);   /* Включить обработку специальных клавиш (стрелки) */
	clear();                /* Очистить экран целевого TTY */

	int y = 0, x = 0;
	int ch;

	/* Рисуем начальный символ */
	mvaddch(y, x, 'X');
	refresh();

	fprintf(orig_tty, "Символ размещен на целевом TTY.\n");
	fprintf(orig_tty, "Используйте стрелки для перемещения, 'q' для выхода.\n");
	fflush(orig_tty);

	/* 4. Основной цикл обработки ввода */
	while ((ch = getch()) != 'q') {
		int new_y = y;
		int new_x = x;

		switch (ch) {
			case KEY_UP:    new_y--; break;
			case KEY_DOWN:  new_y++; break;
			case KEY_LEFT:  new_x--; break;
			case KEY_RIGHT: new_x++; break;
			default:        continue; /* Игнорируем остальные клавиши */
		}

		/* Проверка границ экрана (LINES и COLS инициализируются ncurses) */
		if (new_y >= 0 && new_y < LINES && new_x >= 0 && new_x < COLS) {
			/* Стираем старый символ */
			mvaddch(y, x, ' ');
			
			/* Обновляем координаты и рисуем новый символ */
			y = new_y;
			x = new_x;
			mvaddch(y, x, 'X');
			refresh();

			/* Выводим координаты в оригинальный терминал */
			fprintf(orig_tty, "Новые координаты: Y=%d, X=%d\n", y, x);
			fflush(orig_tty); /* Принудительный сброс буфера */
		}
	}

	/* 5. Очистка и завершение работы */
	endwin();
	fclose(tty_in);
	fclose(tty_out);
	fclose(orig_tty);

	return EXIT_SUCCESS;
}