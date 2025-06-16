*Brick breaker game*

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin config
#define JOY_X A0

// Game config
#define PADDLE_WIDTH 30
#define PADDLE_HEIGHT 4
#define BALL_SIZE 3
#define BRICK_WIDTH 20
#define BRICK_HEIGHT 6
#define BRICK_COLUMNS 6

int paddleX;
int paddleY = SCREEN_HEIGHT - 10;

float ballX, ballY, ballVX, ballVY;
int score = 0;
int level = 1;
int brickRows = 2;
bool bricks[4][BRICK_COLUMNS];

unsigned long lastUpdate = 0;
const int refreshRate = 15;

void setup() {
  pinMode(JOY_X, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  resetGame();
}

void loop() {
  if (millis() - lastUpdate > refreshRate) {
    handleJoystick();
    updateBall();
    drawGame();
    lastUpdate = millis();
  }
}

void resetGame() {
  paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;

  // Set parameters based on level
  switch (level) {
    case 1:
      ballVX = 0.7;
      ballVY = -0.7;
      brickRows = 2;
      break;
    case 2:
      ballVX = 1;
      ballVY = -1;
      brickRows = 3;
      break;
    case 3:
      ballVX = 1.4;
      ballVY = -1.4;
      brickRows = 4;
      break;
  }

  // Reset bricks
  for (int r = 0; r < brickRows; r++)
    for (int c = 0; c < BRICK_COLUMNS; c++)
      bricks[r][c] = true;
}

void handleJoystick() {
  int xVal = analogRead(JOY_X);
  static int lastPaddleX = paddleX;

  if (abs(xVal - 512) > 30) {
    paddleX = map(xVal, 0, 1023, SCREEN_WIDTH - PADDLE_WIDTH, 0);
  } else {
    paddleX = lastPaddleX;
  }

  lastPaddleX = paddleX;
}

void updateBall() {
  ballX += ballVX;
  ballY += ballVY;

  // Wall collisions
  if (ballX <= 0 || ballX + BALL_SIZE >= SCREEN_WIDTH) ballVX *= -1;
  if (ballY <= 0) ballVY *= -1;

  // Paddle collision
  if (ballY + BALL_SIZE >= paddleY && ballY + BALL_SIZE <= paddleY + PADDLE_HEIGHT &&
      ballX + BALL_SIZE >= paddleX && ballX <= paddleX + PADDLE_WIDTH) {
    ballVY *= -1;
    ballY = paddleY - BALL_SIZE;
  }

  // Brick collisions
  bool anyBrick = false;
  for (int r = 0; r < brickRows; r++) {
    for (int c = 0; c < BRICK_COLUMNS; c++) {
      if (bricks[r][c]) {
        anyBrick = true;
        int bx = c * (BRICK_WIDTH + 2) + 4;
        int by = r * (BRICK_HEIGHT + 2) + 5;

        if (ballX + BALL_SIZE > bx && ballX < bx + BRICK_WIDTH &&
            ballY + BALL_SIZE > by && ballY < by + BRICK_HEIGHT) {
          bricks[r][c] = false;
          ballVY *= -1;
          score++;
        }
      }
    }
  }

  // Win condition: all bricks gone
  if (!anyBrick) {
    level++;
    if (level > 3) {
      showWin();
      level = 1;
      score = 0;
    }
    resetGame();
  }

  // Game over
  if (ballY > SCREEN_HEIGHT) {
    showGameOver();
    level = 1;
    score = 0;
    resetGame();
  }
}

void drawGame() {
  display.clearDisplay();

  // Paddle
  display.fillRect(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  // Ball
  display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, SSD1306_WHITE);

  // Bricks
  for (int r = 0; r < brickRows; r++) {
    for (int c = 0; c < BRICK_COLUMNS; c++) {
      if (bricks[r][c]) {
        int bx = c * (BRICK_WIDTH + 2) + 4;
        int by = r * (BRICK_HEIGHT + 2) + 5;
        display.fillRect(bx, by, BRICK_WIDTH, BRICK_HEIGHT, SSD1306_WHITE);
      }
    }
  }

  // HUD
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);
  display.setCursor(80, 0);
  display.print("Lvl: ");
  display.print(level);
  display.display();
}

void showGameOver() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30, 20);
  display.println("Game Over!");
  display.setCursor(25, 35);
  display.print("Score: ");
  display.print(score);
  display.display();
  delay(3000);
}

void showWin() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 20);
  display.println("YOU WIN!");
  display.setCursor(15, 35);
  display.print("Final Score: ");
  display.print(score);
  display.display();
  delay(4000);
}
