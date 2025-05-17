#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����Ű �ڵ�
#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77

// ��ֹ� �ִ� ����
#define MAX_OBSTACLES 50

// ��ǥ ����ü
typedef struct {
    int x, y;
} coord;
    
// ���� ����
coord head;                           // �� �Ӹ�
coord food;                           // ����
coord body[100];                      // �� ����
coord obstacles[MAX_OBSTACLES];       // ��ֹ�

int   length = 5;             // �� ����
int   life = 3;             // ���
int   dir = RIGHT;         // ����
int   delay = 100;           // �ӵ� (ms)
int   obstacle_count = 0;             // ��ֹ� ����
int   level = 0;             // ����
int   records[4] = { 0 };

HANDLE hConsole;                       // �ܼ� �ڵ�

// �Լ� ����
void hideCursor(void);
void moveCursor(int x, int y);
void setColor(WORD color);

void drawBorder(void);
void drawObstacles(void);
void drawStatus(void);
void placeFood(void);
void addObstacles(void);
void clearLine(int y);
void refreshScreen(void);

void resetGame(void);
void updateSnake(void);
void checkCollision(void);



int main(void) {
    srand((unsigned)time(NULL));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();

    // �ʱ� �� ��ġ
    head.x = 25;  head.y = 20;
    for (int i = 0; i < length; ++i) {
        body[i].x = head.x - i;
        body[i].y = head.y;
    }

    // ù ȭ��
    resetGame();

    // ���� ����
    while (1) {
        if (_kbhit()) {
            int c = _getch();
            if (c == 27)                // ESC
                break;
            if (c == 0 || c == 224) {   // ȭ��ǥ
                c = _getch();
                if ((c == RIGHT && dir != LEFT) ||
                    (c == LEFT && dir != RIGHT) ||
                    (c == UP && dir != DOWN) ||
                    (c == DOWN && dir != UP))
                {
                    dir = c;
                }
            }
        }

        updateSnake();

        // ���� ���� & ������
        if (head.x == food.x && head.y == food.y) {
            length++;
            MessageBeep(MB_OK);
            placeFood();

            if ((length - 5) % 10 == 0) {
                level++;
                addObstacles();
                if (delay > 20) delay -= 10;
            }
        }

        drawObstacles();
        checkCollision();
        drawStatus();
        Sleep(delay);
    }

    return 0;
}

// �ܼ� Ŀ�� �����
void hideCursor(void) {
    CONSOLE_CURSOR_INFO ci = { sizeof(ci), FALSE };
    SetConsoleCursorInfo(hConsole, &ci);
}

// Ŀ�� �̵�
void moveCursor(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(hConsole, pos);
}

// �ؽ�Ʈ ���� ����
void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

// �׵θ� �׸���
void drawBorder(void) {
    setColor(15);
    for (int x = 10; x <= 70; ++x) {
        moveCursor(x, 10); printf("!");
        moveCursor(x, 30); printf("!");
    }
    for (int y = 10; y <= 30; ++y) {
        moveCursor(10, y); printf("!");
        moveCursor(70, y); printf("!");
    }
}

// ��ֹ� �׸���
void drawObstacles(void) {
    setColor(8);
    for (int i = 0; i < obstacle_count; ++i) {
        moveCursor(obstacles[i].x, obstacles[i].y);
        printf("#");
    }
}

// ��������������� ǥ��
void drawStatus(void) {
    int score = length - 5;

    moveCursor(15, 8);
    setColor(14);
    printf("����: %d", score);

    moveCursor(35, 8);
    setColor(11);
    printf("���: %d", life);

    moveCursor(55, 8);
    setColor(13);
    printf("����: %d", level);
}

// ���� ��ġ (������)
void placeFood(void) {
    do {
        food.x = rand() % 59 + 11;
        food.y = rand() % 19 + 11;
    } while (food.x == head.x && food.y == head.y);

    moveCursor(food.x, food.y);
    setColor(12);
    printf("F");
}

// ��ֹ� �߰� (�������� 5��)
void addObstacles(void) {
    for (int k = 0; k < 5 && obstacle_count < MAX_OBSTACLES; ++k) {
        coord o;
        int valid;
        do {
            valid = 1;
            o.x = rand() % 59 + 11;
            o.y = rand() % 19 + 11;
            if ((o.x == head.x && o.y == head.y) ||
                (o.x == food.x && o.y == food.y)) valid = 0;
            for (int j = 0; j < obstacle_count; ++j)
                if (o.x == obstacles[j].x && o.y == obstacles[j].y)
                    valid = 0;
        } while (!valid);
        obstacles[obstacle_count++] = o;
    }
}

// Ư�� ���� ��ü �����
void clearLine(int y) {
    setColor(15);
    for (int x = 10; x <= 70; ++x) {
        moveCursor(x, y);
        printf(" ");
    }
}

// ȭ�� ��ü ����
void refreshScreen(void) {
    drawBorder();
    placeFood();
    drawObstacles();
    drawStatus();

    for (int i = 0; i < length; ++i) {
        moveCursor(body[i].x, body[i].y);
        setColor(i == 0 ? 10 : 2);
        printf(i == 0 ? "O" : "*");
    }
}

// ���� ���� (��� ���� �� ȣ��)
void resetGame(void) {
    system("cls");

    length = 5;
    delay = 100;
    obstacle_count = 0;
    level = 0;

    head.x = 25;
    head.y = 20;
    dir = RIGHT;

    for (int i = 0; i < length; ++i) {
        body[i].x = head.x - i;
        body[i].y = head.y;
    }

    refreshScreen();
}

// �� �̵� �� �׸���
void updateSnake(void) {
    coord tail = body[length - 1];
    moveCursor(tail.x, tail.y);
    printf(" ");

    for (int i = length - 1; i > 0; --i) {
        body[i] = body[i - 1];
    }

    switch (dir) {
    case RIGHT: head.x++; break;
    case LEFT:  head.x--; break;
    case DOWN:  head.y++; break;
    case UP:    head.y--; break;
    }

    body[0] = head;

    setColor(10);
    moveCursor(head.x, head.y);
    printf("O");

    if (length > 1) {
        setColor(2);
        moveCursor(body[1].x, body[1].y);
        printf("*");
    }
}

// �浹 �˻� �� ó��
void checkCollision(void) {
    // (���� �浹 ���� �ڵ�...)
    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30) {
        MessageBeep(MB_ICONEXCLAMATION);
        life--;
        records[life] = length - 5;
        if (life >= 0) {
            resetGame();
            return;
        }
    }
    else {
        for (int i = 1; i < length; ++i) {
            if (head.x == body[i].x && head.y == body[i].y) {
                MessageBeep(MB_ICONEXCLAMATION);
                life--;
                records[life] = length - 5;
                if (life >= 0) { resetGame(); return; }
            }
        }
        for (int i = 0; i < obstacle_count; ++i) {
            if (head.x == obstacles[i].x && head.y == obstacles[i].y) {
                MessageBeep(MB_ICONEXCLAMATION);
                life--;
                records[life] = length - 5;
                if (life >= 0) { resetGame(); return; }
            }
        }
    }

    if (life < 0) {
        system("cls");
        setColor(12);

        // �迭���� �ִ밪 ã��
        int best = records[0];
        for (int i = 1; i < 4; ++i) {
            if (records[i] > best) best = records[i];
        }

        printf("���� ����!\n�ְ� ���: %d\n", best);
        exit(0);
    }
}