*Joystick Maze game*

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int joyX = A0;
const int joyY = A1;
#define JOY_BUTTON 2  // Joystick button pin

const int cellSize = 8;
const int cols = SCREEN_WIDTH / cellSize; // 16
const int rows = SCREEN_HEIGHT / cellSize; // 8

unsigned long lastMoveTime = 0;
int moveDelay = 150;
int currentLevel = 0;

int playerX = 1;
int playerY = 1;

const int totalLevels = 5;

// Maze levels
const byte mazes[totalLevels][8][16] PROGMEM = {
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1},
    {1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1}
  },
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1}
  },
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1},
    {1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,0,1,1,1,1,1,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1}
  },
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,0,1,1,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1}
  },
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1}
  }
};

void setup() {
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(JOY_BUTTON, INPUT_PULLUP); // Button uses pull-up resistor

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  drawMaze();
}

void loop() {
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);

  if (millis() - lastMoveTime > moveDelay) {
    if (xVal < 400) movePlayer(1, 0);      // Right 
    else if (xVal > 600) movePlayer(-1, 0); // Left 

    if (yVal < 400) movePlayer(0, -1);     // Up
    else if (yVal > 600) movePlayer(0, 1); // Down

    lastMoveTime = millis();
  }

  // Reached end of maze?
  if (playerX == 14 && playerY == 7) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 25);

    if (currentLevel < totalLevels - 1) {
      display.print("Level ");
      display.print(currentLevel + 1);
      display.println(" Complete!");
      display.display();
      delay(2000);

      currentLevel++;
      playerX = 1;
      playerY = 1;
      drawMaze();
    } else {
      // Final win screen
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(10, 20);
      display.println("YOU WIN!");
      display.display();

      delay(8000);  // Wait 8 seconds

      // Restart game
      currentLevel = 0;
      playerX = 1;
      playerY = 1;
      drawMaze();
    }
  }
}

void drawMaze() {
  display.clearDisplay();
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      if (pgm_read_byte(&(mazes[currentLevel][y][x])) == 1) {
        display.fillRect(x * cellSize, y * cellSize, cellSize, cellSize, SSD1306_WHITE);
      }
    }
  }
  drawPlayer();
  display.display();
}

void drawPlayer() {
  display.fillRect(playerX * cellSize + 2, playerY * cellSize + 2, cellSize - 4, cellSize - 4, SSD1306_WHITE);
}

void movePlayer(int dx, int dy) {
  int newX = playerX + dx;
  int newY = playerY + dy;

  if (newX < 0 || newX >= cols || newY < 0 || newY >= rows) return;
  if (pgm_read_byte(&(mazes[currentLevel][newY][newX])) == 1) return;

  playerX = newX;
  playerY = newY;
  drawMaze();
}
