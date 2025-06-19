 # 🕹️ Hobitronics Arcade  
### Let's build fun, nostalgic games with just code, wires, and imagination!  

---

# 🐍 Snake Game on OLED with Joystick

## Description:
Bring back the nostalgic arcade vibes with this minimalist Snake Game built using an Arduino, a joystick, and a 0.96" OLED screen.  
Control the snake, eat the food, and grow longer — all in just 64 pixels!

---

## 🎮 Components:
- Arduino UNO  
- 0.96" OLED Display (SSD1306, I2C)  
- Joystick Module (Analog)  
- Jumper Wires & Breadboard  
- Optional: 10kΩ resistors (if needed for joystick voltage divider)

---

## 🔍 Features:
- Real-time snake movement using analog joystick input  
- Auto food spawning (never on snake body!)  
- Self and wall collision detection  
- Game over animation and auto-reset  
- Adjustable speed via `moveDelay`  
- Compact and optimized for 128x64 OLED

---

## 🧠 Concepts Covered:
- OLED graphics with Adafruit GFX library  
- Analog joystick input handling  
- Arrays and game logic on microcontrollers  
- Collision detection  
- Procedural food spawning

---

## 📺 Demo  
👉 [Watch on YouTube Shorts](https://www.youtube.com/shorts/wpcqOu3Ykuk)  
👉 [Find Code on GitHub](https://github.com/Hobitronics/hobitronics_arcade/blob/main/code/snake_game.ino)

---

## ✅ Quick Tips:
- If the joystick feels reversed, just swap X/Y pins or logic in `readJoystick()`  
- To increase difficulty, reduce `moveDelay`  
- Expand the project by adding a score counter, splash screen, or level system!

---

# 🧩 Joystick Maze Game on OLED

## Description:
Navigate through 5 progressively challenging mazes using a joystick on a 128x64 OLED screen.  
This project combines logic, memory-efficient graphics, and satisfying pixel movement — a perfect hands-on learning experience in embedded game design.

---

## 🎮 Components:
- Arduino UNO  
- 0.96" OLED Display (SSD1306, I2C)  
- Analog Joystick Module  
- Jumper Wires & Breadboard  
- Optional: Pull-up resistors (10kΩ for joystick button)

---

## 🔍 Features:
- 5 levels of handcrafted maze puzzles  
- Pixel-perfect joystick navigation (analog input to digital move)  
- Dynamic maze drawing from PROGMEM to save RAM  
- Win animation and auto-restart  
- Button press supported for future upgrades (pause, reset, etc.)

---

## 🧠 Concepts Covered:
- Drawing 2D levels using arrays in `PROGMEM`  
- Display graphics with Adafruit GFX & SSD1306  
- Handling analog joystick input and debouncing movement  
- Coordinate-based logic and collision detection  
- Game state logic and level progression

---

## 📺 Demo  
👉 [Watch on YouTube Shorts](https://www.youtube.com/shorts/j5V-KC0HfVs)  
👉 [View Code on GitHub](https://github.com/Hobitronics/hobitronics_arcade/blob/main/code/joystick_maze.ino)

---
# 🧱 Brick Breaker on OLED  
### Part of the Hobitronics Arcade Collection

---

## 🎮 Game Description  
A full-featured **Brick Breaker** game built using an Arduino UNO, joystick, and 128x64 OLED.  
Use the joystick to control the paddle, bounce the ball, break all the bricks, and advance through 3 exciting levels. Game Over and Victory screens included!

---

## ⚙️ Components Required
- Arduino UNO  
- 0.96" OLED Display (SSD1306, I2C)  
- Analog Joystick Module (connected to A0)  
- Jumper Wires & Breadboard  

---

## 🧠 Key Features & Concepts
- Joystick-based paddle control (analog input)  
- OLED rendering with **Adafruit GFX + SSD1306**  
- Ball physics with basic collision detection  
- Brick grid with collision response  
- Game states: win, lose, reset  
- Level progression with increasing difficulty  
- Memory-efficient display updates using `clearDisplay()` and `fillRect()` logic

---

## 🕹️ Gameplay Mechanics
- **Paddle**: Controlled via joystick (X-axis)  
- **Ball**: Bounces off walls, paddle, and bricks  
- **Bricks**: Destroy on impact, earn points  
- **Levels**:  
  - Level 1 → 2 rows of bricks, slower ball  
  - Level 2 → 3 rows of bricks, medium speed  
  - Level 3 → 4 rows, faster ball  
- **Win**: Clear all bricks in Level 3  
- **Lose**: Ball falls below paddle

---

## 📺 Demo  
👉 [Watch the YouTube Short](https://www.youtube.com/shorts/PUPcUioOR-o)  
👉 [View Source Code on GitHub](https://github.com/Hobitronics/hobitronics_arcade/blob/main/code/breaking_bricks_oled.ino)


---

🧱 Dodger Game on OLED with Joystick
Description:
Dodge falling blocks like a pro in this fast-paced Pixel Dodging Game made with an Arduino UNO, a joystick, and a 0.96" OLED screen.
Three levels, increasing speed, and randomized block drops make it a thrilling challenge for hobbyists and students alike!

---

🎮 Components:
Arduino UNO

0.96" OLED Display (SSD1306, I2C)

Joystick Module (Analog)

Jumper Wires & Breadboard

Optional: 10kΩ resistors (for joystick stabilization)

---

🔍 Features:
Player-controlled dodging using analog joystick input

3 progressive levels with increasing difficulty

Dynamic obstacle sizing and randomized fall paths

Real-time score tracking and level display

Smooth win/lose animation and automatic reset

Optimized for 128x64 OLED using Adafruit GFX library

---

🧠 Concepts Covered:
OLED graphics with Adafruit SSD1306 & GFX library

Analog input handling for joystick

Game loop timing and collision detection

Random obstacle generation

State management (level system, win/lose screens)

---

## 📺 Demo  
👉 [Watch on YouTube Shorts](https://www.youtube.com/shorts/qnpOjiRsCfk)  
👉 [View Code on GitHub](https://github.com/Hobitronics/hobitronics_arcade/blob/main/code/pixel_dodging_game.ino)

---

✅ Quick Tips:
Obstacle speed increases slightly with every dodge

Each level includes 10 dodges before progressing

Want to increase difficulty? Decrease updateInterval or increase speed scaling

Reverse joystick directions by modifying logic in readJoystick()
---

## 📚 Explore More Electronics
For tutorials, explanations, and in-depth electronics blogs, visit:  
👉 [**hobitronics.blog**](https://hobitronics.blog)

---

## 📲 Stay Connected!
Follow us for regular project updates, memes, and DIY tips:  
- 📸 Instagram: [**@hobitronics**](https://instagram.com/hobitronics)  
- 📺 YouTube: [**Hobitronics on YouTube**](https://www.youtube.com/@hobitronics)

---

Built with 💙 by Hobitronics
*Let’s make electronics exciting — one pixel at a time!*
