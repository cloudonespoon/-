// ──────────────────────────────────────────────────────────────────────────
// 충돌 발생 시마다 현재 점수를 저장하여 세션 중 최고 기록을 계산합니다.
int records[4] = { 0 };

// ──────────────────────────────────────────────────────────────────────────
// 콘솔 컬러 출력 및 커서 숨기기
HANDLE hConsole;  // 전역 콘솔 핸들

void hideCursor(void) {
    CONSOLE_CURSOR_INFO ci = { sizeof(ci), FALSE };
    SetConsoleCursorInfo(hConsole, &ci);
}

void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

// main() 시작 부분에 추가
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
hideCursor();

// ──────────────────────────────────────────────────────────────────────────
// 레벨업 및 장애물 생성 기능
#define MAX_OBSTACLES 50  // 최대 장애물 개수
coord obstacles[MAX_OBSTACLES];
int   obstacle_count = 0;  // 생성된 장애물 수
int   level = 0;  // 현재 레벨

// 레벨업 시 장애물 5개씩 추가
void addObstacles(void) {
    for (int k = 0; k < 5 && obstacle_count < MAX_OBSTACLES; ++k) {
        coord o; int valid;
        do {
            valid = 1;
            o.x = rand() % 59 + 11;
            o.y = rand() % 19 + 11;
            // 뱀 머리 혹은 먹이 위치 중복 방지
            if ((o.x == head.x && o.y == head.y) ||
                (o.x == food.x && o.y == food.y)) valid = 0;
            // 기존 장애물 위치 중복 방지
            for (int j = 0; j < obstacle_count; ++j)
                if (o.x == obstacles[j].x && o.y == obstacles[j].y)
                    valid = 0;
        } while (!valid);
        obstacles[obstacle_count++] = o;
    }
}

// 장애물 그리기
void drawObstacles(void) {
    setColor(8);  // 회색
    for (int i = 0; i < obstacle_count; ++i) {
        moveCursor(obstacles[i].x, obstacles[i].y);
        printf("#");
    }
}

// ──────────────────────────────────────────────────────────────────────────
// 컬러풀 UI: 점수, 목숨, 레벨, 먹이, 뱀 색상 지정

// 점수·목숨·레벨 표시 (각기 다른 색상)
void drawStatus(void) {
    int score = length - 5;

    moveCursor(15, 8);
    setColor(14);  // 노란색
    printf("점수: %d", score);

    moveCursor(35, 8);
    setColor(11);  // 하늘색
    printf("목숨: %d", life);

    moveCursor(55, 8);
    setColor(13);  // 보라색
    printf("레벨: %d", level);
}

// 먹이 표시 (빨간색)
void placeFood(void) {
    // (기존 랜덤 위치 결정 로직)
    moveCursor(food.x, food.y);
    setColor(12);
    printf("F");
}

// ──────────────────────────────────────────────────────────────────────────
// 소리 효과: MessageBeep 사용
MessageBeep(MB_OK);            // 먹이 섭취 시
MessageBeep(MB_ICONEXCLAMATION); // 충돌 시

// ──────────────────────────────────────────────────────────────────────────
// 목숨 소진 시 기록 저장 및 최종 최고 기록 계산
void checkCollision(void) {
    if (/* 충돌 감지 */) {
        MessageBeep(MB_ICONEXCLAMATION);
        // 충돌 직전 점수 저장
        records[life - 1] = length - 5;
        life--;
        if (life > 0) { resetGame(); return; }
    }
    // (몸통 및 장애물 충돌 시에도 동일 로직)

    if (life <= 0) {
        system("cls");
        setColor(12);
        // 저장된 기록 중 최고값 계산
        int best = records[0];
        for (int i = 1; i < 3; ++i)
            if (records[i] > best) best = records[i];
        printf("게임 종료!\n최고 기록: %d\n", best);
        exit(0);
    }
}

// ──────────────────────────────────────────────────────────────────────────
// 레벨업 조건: 먹이 10개마다 레벨 증가 및 속도 증가
if ((length - 5) % 10 == 0) {
    level++;
    addObstacles();
    if (delay > 20) delay -= 10;
}
