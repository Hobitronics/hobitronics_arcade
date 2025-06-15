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
