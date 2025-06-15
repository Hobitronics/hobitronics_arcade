#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick Pins
#define JOY_X A0
#define JOY_Y A1

// Game Settings
#define SNAKE_SIZE 4
#define MAX_SNAKE_LENGTH 64

// Snake body coordinates
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength = 3;

// Direction: 0-up, 1-right, 2-down, 3-left
int direction = 1;

// Food coordinates
int foodX, foodY;

unsigned long lastMove = 0;
int moveDelay = 200;

void setup() {
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100); // OLED init delay
  display.clearDisplay();
  display.display();

  // Initial snake position
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 20 - i * SNAKE_SIZE;
    snakeY[i] = 20;
  }

  spawnFood();
}

void loop() {
  readJoystick();
  if (millis() - lastMove > moveDelay) {
    moveSnake();
    drawGame();
    lastMove = millis();
  }
}

void readJoystick() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  if (x < 400 && direction != 3) direction = 1; // right
  else if (x > 600 && direction != 1) direction = 3; // left
  else if (y < 400 && direction != 2) direction = 0; // up
  else if (y > 600 && direction != 0) direction = 2; // down
}

void moveSnake() {
  // Move body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move head
  if (direction == 0) snakeY[0] -= SNAKE_SIZE;
  else if (direction == 1) snakeX[0] += SNAKE_SIZE;
  else if (direction == 2) snakeY[0] += SNAKE_SIZE;
  else if (direction == 3) snakeX[0] -= SNAKE_SIZE;

  // Check collision with food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (snakeLength < MAX_SNAKE_LENGTH) snakeLength++;
    spawnFood();
  }

  // Wall collision
  if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
    gameOver();
    resetGame();
  }

  // Self collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver();
      resetGame();
      break;
    }
  }
}

void drawGame() {
  display.clearDisplay();

  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], SNAKE_SIZE, SNAKE_SIZE, SSD1306_WHITE);
  }

  // Draw food
  display.fillRect(foodX, foodY, SNAKE_SIZE, SNAKE_SIZE, SSD1306_WHITE);

  display.display();
}

void spawnFood() {
  bool valid = false;
  while (!valid) {
    foodX = random(0, SCREEN_WIDTH / SNAKE_SIZE) * SNAKE_SIZE;
    foodY = random(0, SCREEN_HEIGHT / SNAKE_SIZE) * SNAKE_SIZE;

    valid = true;
    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == foodX && snakeY[i] == foodY) {
        valid = false;
        break;
      }
    }
  }
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 30);
  display.println("Game Over!");
  display.display();
  delay(1000);
}

void resetGame() {
  snakeLength = 3;
  direction = 1;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 20 - i * SNAKE_SIZE;
    snakeY[i] = 20;
  }
  spawnFood();
}
