*Catch it game*

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick
#define JOY_X A0
#define BUCKET_WIDTH 18
#define BUCKET_HEIGHT 6

int bucketX = SCREEN_WIDTH / 2 - BUCKET_WIDTH / 2;

// Object
int objX, objY = 0;
int objSpeed = 1;
int objSize = 6;
int objShape = 0; // 0 = square, 1 = circle, 2 = triangle

// Game Variables
int score = 0;
int lives = 3;
unsigned long lastFallTime = 0;
unsigned long fallInterval = 100;
unsigned long startTime;

bool gameOver = false;

void setup() {
  pinMode(JOY_X, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  randomSeed(analogRead(0));
  spawnNewObject();
  startTime = millis();
}

void loop() {
  if (!gameOver) {
    handleJoystick();
    updateObject();
    checkCollision();
    drawGame();
    delay(20);
  } else {
    showGameOver();
  }
}

void handleJoystick() {
  int xVal = analogRead(JOY_X);

  if (xVal > 600 && bucketX > 0)
    bucketX -= 2;
  if (xVal < 400 && bucketX < SCREEN_WIDTH - BUCKET_WIDTH)
    bucketX += 2;
}

void updateObject() {
  unsigned long now = millis();
  if (now - lastFallTime > fallInterval) {
    objY += objSpeed;
    lastFallTime = now;
  }

  // Gradual difficulty increase
  unsigned long elapsed = now - startTime;
  if (elapsed > 5000) fallInterval = 90;
  if (elapsed > 10000) fallInterval = 75;
  if (elapsed > 15000) fallInterval = 60;
  if (elapsed > 20000) fallInterval = 45;
  if (elapsed > 30000) fallInterval = 30;
}

void checkCollision() {
  if (objY + objSize >= SCREEN_HEIGHT - BUCKET_HEIGHT - 1) {
    if (objX + objSize >= bucketX && objX <= bucketX + BUCKET_WIDTH) {
      score++;
    } else {
      lives--;
      if (lives <= 0) gameOver = true;
    }
    spawnNewObject();
  }
}

void spawnNewObject() {
  objX = random(0, SCREEN_WIDTH - objSize);
  objY = 0;
  objShape = random(0, 3); // 0 = square, 1 = circle, 2 = triangle
}

void drawGame() {
  display.clearDisplay();

  int topY = SCREEN_HEIGHT - BUCKET_HEIGHT - 3; 
  int bottomY = SCREEN_HEIGHT - 1;              

  int topWidth = BUCKET_WIDTH;
  int bottomWidth = BUCKET_WIDTH - 8; 

  int topLeftX = bucketX;
  int topRightX = bucketX + topWidth;
  int bottomLeftX = bucketX + 4;
  int bottomRightX = bucketX + topWidth - 4;

  // Bucket lines
  display.drawLine(topLeftX, topY, topRightX, topY, SSD1306_WHITE);           // Top
  display.drawLine(bottomLeftX, bottomY, bottomRightX, bottomY, SSD1306_WHITE); // Bottom
  display.drawLine(topLeftX, topY, bottomLeftX, bottomY, SSD1306_WHITE);      // Left
  display.drawLine(topRightX, topY, bottomRightX, bottomY, SSD1306_WHITE);    // Right

  // Draw falling object
  switch (objShape) {
    case 0: // Square
      display.fillRect(objX, objY, objSize, objSize, SSD1306_WHITE);
      break;
    case 1: // Circle
      display.fillCircle(objX + objSize / 2, objY + objSize / 2, objSize / 2, SSD1306_WHITE);
      break;
    case 2: // Triangle
      display.fillTriangle(
        objX, objY + objSize,
        objX + objSize / 2, objY,
        objX + objSize, objY + objSize,
        SSD1306_WHITE
      );
      break;
  }

  // Score and Lives
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);
  display.setCursor(80, 0);
  display.print("Lives: ");
  display.print(lives);

  display.display();
}

void showGameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20);
  display.print("Game Over");
  display.setTextSize(1);
  display.setCursor(35, 50);
  display.print("Score: ");
  display.print(score);
  display.display();
  delay(5000);
  resetGame();
}

void resetGame() {
  score = 0;
  lives = 3;
  bucketX = SCREEN_WIDTH / 2 - BUCKET_WIDTH / 2;
  fallInterval = 100;
  startTime = millis();
  gameOver = false;
  spawnNewObject();
}
