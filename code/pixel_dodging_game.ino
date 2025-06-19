*Dodger game*

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define JOYSTICK_X A0

int playerX = 60;
int playerY = 56;
int playerWidth = 10;
int playerHeight = 8;

int objX;
int objY = 0;
int objWidth = 6;
int objHeight = 6;
float speed = 2.0;

int score = 0;
int level = 1;
int bricksDodged = 0;

unsigned long lastUpdate = 0;
int updateInterval = 100;
bool levelStart = true;

void setup() {
  pinMode(JOYSTICK_X, INPUT);
  randomSeed(analogRead(0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);  // OLED error
  }

  display.clearDisplay();
  objX = random(0, SCREEN_WIDTH - objWidth);
}

void loop() {
  if (levelStart) {
    showLevelScreen();
    return;
  }

  if (millis() - lastUpdate > updateInterval) {
    lastUpdate = millis();
    objY += speed;

    if (checkCollision()) {
      gameOver();
      return;
    }

    if (objY > SCREEN_HEIGHT) {
      objY = 0;
      objX = random(0, SCREEN_WIDTH - objWidth);
      bricksDodged++;
      score++;

      // Random speed bump each block (range +0.3 to +0.6)
      speed += random(3, 7) / 10.0;

      // Reduce interval to increase update frequency (min 30ms)
      if (updateInterval > 30) updateInterval -= random(1, 4);

      if (bricksDodged == 10) {
        level++;
        if (level > 3) {
          youWin();
          return;
        }
        prepareNextLevel();
        return;
      }
    }
  }

  readJoystick();
  drawGame();
}

void readJoystick() {
  int joyVal = analogRead(JOYSTICK_X);
  if (joyVal < 400 && playerX < SCREEN_WIDTH - playerWidth) {
    playerX += 3;
  } else if (joyVal > 600 && playerX > 0) {
    playerX -= 3;
  }
}

bool checkCollision() {
  return (objY + objHeight >= playerY &&
          objX < playerX + playerWidth &&
          objX + objWidth > playerX);
}

void drawGame() {
  display.clearDisplay();

  // Player
  display.fillRect(playerX, playerY, playerWidth, playerHeight, SSD1306_WHITE);

  // Obstacle
  display.fillRect(objX, objY, objWidth, objHeight, SSD1306_WHITE);

  // Score
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);

  // Level
  display.setCursor(80, 0);
  display.print("Lv ");
  display.print(level);

  display.display();
}

void showLevelScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 25);
  display.print("Level ");
  display.print(level);
  display.display();
  delay(1500);

  levelStart = false;
  applyLevelSettings();
}

void applyLevelSettings() {
  if (level == 1) {
    objWidth = 6; objHeight = 6;
    updateInterval = 100;
    speed = 2.0;
  } else if (level == 2) {
    objWidth = 10; objHeight = 10;
    updateInterval = 90;
    speed = 2.5;
  } else if (level == 3) {
    objWidth = 14; objHeight = 14;
    updateInterval = 80;
    speed = 3.0;
  }
}

void prepareNextLevel() {
  bricksDodged = 0;
  objY = 0;
  objX = random(0, SCREEN_WIDTH - objWidth);
  levelStart = true;
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.print("You Lose!");
  display.display();
  delay(3000);
  resetGame();
}

void youWin() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.print("You Win!");
  display.display();
  delay(3000);
  resetGame();
}

void resetGame() {
  playerX = 60;
  objY = 0;
  objX = random(0, SCREEN_WIDTH - objWidth);
  score = 0;
  level = 1;
  bricksDodged = 0;
  levelStart = true;
}
