#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

short int calc_asm(short int x, char y, char z) {

short int v;

// -4 + (-y + x * (3 * z + 1)) / (z - 2)
__asm {
	;// вычисление числителя
	mov al, z; // поместить z в AL
	mov bl, 3; // поместить 3 в BL
	imul bl; // вычислить 3 * z
	inc ax; // вычислить 3 * z + 1
	imul x; // вычислить x * (3 * z + 1)
	mov bx, ax; // поместить младшее слово числителя в BX
	mov cx, dx; // поместить старшее слово числителя в CX
	mov al, y; // поместить y в AL
	cbw; // расширить AL со знаком до слова
	cwd; // расширить до двойного слова
	sub bx, ax; // вычисление младшего слова
	sbb cx, dx; // вычисление старшего слова
	xchg dx, cx; // поместить старшее слово числителя в DX
	;// вычисление знаменателя
	mov al, z; // поместить z в AL
	cbw; // расширить AL со знаком до слова
	sub ax, 2; // вычислить z - 2
	xchg ax, bx; // поместить младшее слово числителя в AX, знаменатель в BX
	idiv bx; // выполнить деление числителя на знаменатель
	sub ax, 4; // вычесть 3 из AX
	mov v, ax; // поместить AX в v
}
}

int  is_correct_short_int(char* buf, short* T) {
if (strlen(buf) == 0 || strlen(buf) > 6)
	return 0;

char* tmp = malloc(sizeof(char) * strlen(buf));
memset(tmp, 0, strlen(tmp));
memcpy(tmp, buf, strlen(buf));
tmp = (buf[0] == '-') ? tmp + 1 : tmp;
while (strlen(tmp) != 0) {
	if (!isdigit(tmp[0])) {
		return 0;
	}
	++tmp;
}
long long t = strtoll(buf, buf + strlen(buf), 10);
if (t < -32768 || t > 32767)
	return 0;

*T = (short)t;
return 1;
}

int  is_correct_char(char* buf, char* T) {
if (strlen(buf) == 0 || strlen(buf) > 4)
	return 0;

char* tmp = malloc(sizeof(char) * strlen(buf));
memset(tmp, 0, strlen(tmp));
memcpy(tmp, buf, strlen(buf));
tmp = (buf[0] == '-') ? tmp + 1 : tmp;
while (strlen(tmp) != 0) {
	if (!isdigit(tmp[0])) {
		return 0;
	}
	++tmp;
}
long long t = strtoll(buf, buf + strlen(buf), 10);
if (t < -128 || t > 127)
	return 0;

*T = (char)t;
return 1;
}

void clear_input() {
	
int c;
while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {

setlocale(LC_ALL, "rus");
setlocale(LC_NUMERIC, "eng");

char y, z; // байты
short int x; // слова
short int v_c, v_asm;

int i; // для меню

int flag = 1;
while (flag != 0) {

	printf("Выберите действие:\n");
	printf("1 - Использование тестовых значений.\n");
	printf("2 - Ручной ввод значений.\n");

	if (scanf("%d", &i) != 1 || (i != 1 && i != 2)) {
		printf("Введено неверное значение\n");
	}else{

		switch (i)
		{
		case 1: {
		short int v = -0x1F;

		// первый тестовый набор
		v_asm = calc_asm(-0x2, 0x7, 0x3);
		v_c = -4 + (-0x7 + (-0x2) * (3 * 0x3 + 1)) / (0x3 - 2);
		printf("\nРезультаты первого тестового набора:\n");
		printf("v_c = %x (16 система) или %d (10 система)\n", v_c, v_c);
		printf("v_asm = %x (16 система) или %d (10 система)\n", v_asm, v_asm);
		printf("Заданное значение v = %x (16 система) или %d (10 система)\n", v, v);

		// второй тестовый набор
		v = 0x2E5B;
		v_asm = calc_asm(0xFBe, 0x56, -0x7F);
		v_c = -4 + (-0x56 + 0xFBe * (3 * -0x7F + 1)) / (-0x7F - 2);
		printf("Результаты второго тестового набора:\n");
		printf("v_c = %x (16 система) или %d (10 система)\n", v_c, v_c);
		printf("v_asm = %x (16 система) или %d (10 система)\n", v_asm, v_asm);
		printf("Заданное значение v = %x (16 система) или %d (10 система)\n\n", v, v);

		break;
		}
		case 2: {

		printf("Введите значения переменных:\n");
					
		char* str = malloc(sizeof(char) * 1000);
		memset(str, 0, 1000);

		if (scanf("%s", str) != 1 || !is_correct_short_int(str, &x)) {
			printf("Введено неверное значение x\n");
		}else if (scanf("%s", str) != 1 || !is_correct_char(str, &y)) {
			printf("Введено неверное значение y\n");
		}else if (scanf("%s", str) != 1 || !is_correct_char(str, &z) || (z == 2)) {
			printf("Введено неверное значение z\n");
		}else {

					
		v_c = -4 + (-y + x * (3 * z + 1)) / (z - 2);
		v_asm = calc_asm(x, y, z);
		printf("Результаты введенного набора (%hd %hd %hd):\n", x, y ,z);
		printf("v_c = %x (16 система) или %d (10 система)\n", v_c, v_c);
		printf("v_asm = %x (16 система) или %d (10 система)\n", v_asm, v_asm);

		break;
		}
		}
		}
	}

	clear_input();

	printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");

	int term = 1;
	while(term == 1){
		if (scanf("%d", &flag) != 1 || (flag != 0 && flag != 1)) {
			printf("Введено неверное значение\n");
			printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");
			clear_input();
		}
		else {
			term = 0;
		}
	}
}

printf("\nВыход из программы.\n\n\n");
exit(0);
}
