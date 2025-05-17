// ����������������������������������������������������������������������������������������������������������������������������������������������������
// �浹 �߻� �ø��� ���� ������ �����Ͽ� ���� �� �ְ� ����� ����մϴ�.
int records[4] = { 0 };

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// �ܼ� �÷� ��� �� Ŀ�� �����
HANDLE hConsole;  // ���� �ܼ� �ڵ�

void hideCursor(void) {
    CONSOLE_CURSOR_INFO ci = { sizeof(ci), FALSE };
    SetConsoleCursorInfo(hConsole, &ci);
}

void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

// main() ���� �κп� �߰�
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
hideCursor();

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// ������ �� ��ֹ� ���� ���
#define MAX_OBSTACLES 50  // �ִ� ��ֹ� ����
coord obstacles[MAX_OBSTACLES];
int   obstacle_count = 0;  // ������ ��ֹ� ��
int   level = 0;  // ���� ����

// ������ �� ��ֹ� 5���� �߰�
void addObstacles(void) {
    for (int k = 0; k < 5 && obstacle_count < MAX_OBSTACLES; ++k) {
        coord o; int valid;
        do {
            valid = 1;
            o.x = rand() % 59 + 11;
            o.y = rand() % 19 + 11;
            // �� �Ӹ� Ȥ�� ���� ��ġ �ߺ� ����
            if ((o.x == head.x && o.y == head.y) ||
                (o.x == food.x && o.y == food.y)) valid = 0;
            // ���� ��ֹ� ��ġ �ߺ� ����
            for (int j = 0; j < obstacle_count; ++j)
                if (o.x == obstacles[j].x && o.y == obstacles[j].y)
                    valid = 0;
        } while (!valid);
        obstacles[obstacle_count++] = o;
    }
}

// ��ֹ� �׸���
void drawObstacles(void) {
    setColor(8);  // ȸ��
    for (int i = 0; i < obstacle_count; ++i) {
        moveCursor(obstacles[i].x, obstacles[i].y);
        printf("#");
    }
}

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// �÷�Ǯ UI: ����, ���, ����, ����, �� ���� ����

// ��������������� ǥ�� (���� �ٸ� ����)
void drawStatus(void) {
    int score = length - 5;

    moveCursor(15, 8);
    setColor(14);  // �����
    printf("����: %d", score);

    moveCursor(35, 8);
    setColor(11);  // �ϴû�
    printf("���: %d", life);

    moveCursor(55, 8);
    setColor(13);  // �����
    printf("����: %d", level);
}

// ���� ǥ�� (������)
void placeFood(void) {
    // (���� ���� ��ġ ���� ����)
    moveCursor(food.x, food.y);
    setColor(12);
    printf("F");
}

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// �Ҹ� ȿ��: MessageBeep ���
MessageBeep(MB_OK);            // ���� ���� ��
MessageBeep(MB_ICONEXCLAMATION); // �浹 ��

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// ��� ���� �� ��� ���� �� ���� �ְ� ��� ���
void checkCollision(void) {
    if (/* �浹 ���� */) {
        MessageBeep(MB_ICONEXCLAMATION);
        // �浹 ���� ���� ����
        records[life - 1] = length - 5;
        life--;
        if (life > 0) { resetGame(); return; }
    }
    // (���� �� ��ֹ� �浹 �ÿ��� ���� ����)

    if (life <= 0) {
        system("cls");
        setColor(12);
        // ����� ��� �� �ְ� ���
        int best = records[0];
        for (int i = 1; i < 3; ++i)
            if (records[i] > best) best = records[i];
        printf("���� ����!\n�ְ� ���: %d\n", best);
        exit(0);
    }
}

// ����������������������������������������������������������������������������������������������������������������������������������������������������
// ������ ����: ���� 10������ ���� ���� �� �ӵ� ����
if ((length - 5) % 10 == 0) {
    level++;
    addObstacles();
    if (delay > 20) delay -= 10;
}
