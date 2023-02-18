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
	;// ���������� ���������
	mov al, z; // ��������� z � AL
	mov bl, 3; // ��������� 3 � BL
	imul bl; // ��������� 3 * z
	inc ax; // ��������� 3 * z + 1
	imul x; // ��������� x * (3 * z + 1)
	mov bx, ax; // ��������� ������� ����� ��������� � BX
	mov cx, dx; // ��������� ������� ����� ��������� � CX
	mov al, y; // ��������� y � AL
	cbw; // ��������� AL �� ������ �� �����
	cwd; // ��������� �� �������� �����
	sub bx, ax; // ���������� �������� �����
	sbb cx, dx; // ���������� �������� �����
	xchg dx, cx; // ��������� ������� ����� ��������� � DX
	;// ���������� �����������
	mov al, z; // ��������� z � AL
	cbw; // ��������� AL �� ������ �� �����
	sub ax, 2; // ��������� z - 2
	xchg ax, bx; // ��������� ������� ����� ��������� � AX, ����������� � BX
	idiv bx; // ��������� ������� ��������� �� �����������
	sub ax, 4; // ������� 3 �� AX
	mov v, ax; // ��������� AX � v
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

char y, z; // �����
short int x; // �����
short int v_c, v_asm;

int i; // ��� ����

int flag = 1;
while (flag != 0) {

	printf("�������� ��������:\n");
	printf("1 - ������������� �������� ��������.\n");
	printf("2 - ������ ���� ��������.\n");

	if (scanf("%d", &i) != 1 || (i != 1 && i != 2)) {
		printf("������� �������� ��������\n");
	}else{

		switch (i)
		{
		case 1: {
		short int v = -0x1F;

		// ������ �������� �����
		v_asm = calc_asm(-0x2, 0x7, 0x3);
		v_c = -4 + (-0x7 + (-0x2) * (3 * 0x3 + 1)) / (0x3 - 2);
		printf("\n���������� ������� ��������� ������:\n");
		printf("v_c = %x (16 �������) ��� %d (10 �������)\n", v_c, v_c);
		printf("v_asm = %x (16 �������) ��� %d (10 �������)\n", v_asm, v_asm);
		printf("�������� �������� v = %x (16 �������) ��� %d (10 �������)\n", v, v);

		// ������ �������� �����
		v = 0x2E5B;
		v_asm = calc_asm(0xFBe, 0x56, -0x7F);
		v_c = -4 + (-0x56 + 0xFBe * (3 * -0x7F + 1)) / (-0x7F - 2);
		printf("���������� ������� ��������� ������:\n");
		printf("v_c = %x (16 �������) ��� %d (10 �������)\n", v_c, v_c);
		printf("v_asm = %x (16 �������) ��� %d (10 �������)\n", v_asm, v_asm);
		printf("�������� �������� v = %x (16 �������) ��� %d (10 �������)\n\n", v, v);

		break;
		}
		case 2: {

		printf("������� �������� ����������:\n");
					
		char* str = malloc(sizeof(char) * 1000);
		memset(str, 0, 1000);

		if (scanf("%s", str) != 1 || !is_correct_short_int(str, &x)) {
			printf("������� �������� �������� x\n");
		}else if (scanf("%s", str) != 1 || !is_correct_char(str, &y)) {
			printf("������� �������� �������� y\n");
		}else if (scanf("%s", str) != 1 || !is_correct_char(str, &z) || (z == 2)) {
			printf("������� �������� �������� z\n");
		}else {

					
		v_c = -4 + (-y + x * (3 * z + 1)) / (z - 2);
		v_asm = calc_asm(x, y, z);
		printf("���������� ���������� ������ (%hd %hd %hd):\n", x, y ,z);
		printf("v_c = %x (16 �������) ��� %d (10 �������)\n", v_c, v_c);
		printf("v_asm = %x (16 �������) ��� %d (10 �������)\n", v_asm, v_asm);

		break;
		}
		}
		}
	}

	clear_input();

	printf("������ ����������?\n0 - ���\n1 - ��\n");

	int term = 1;
	while(term == 1){
		if (scanf("%d", &flag) != 1 || (flag != 0 && flag != 1)) {
			printf("������� �������� ��������\n");
			printf("������ ����������?\n0 - ���\n1 - ��\n");
			clear_input();
		}
		else {
			term = 0;
		}
	}
}

printf("\n����� �� ���������.\n\n\n");
exit(0);
}
