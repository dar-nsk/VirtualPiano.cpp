#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

using namespace std;

// Key class to represent each key on the piano
class Key {
private:
    int x, y, width, height;
    bool isPressed;
    char soundKey;

public:
    // Constructor to initialize key attributes
    Key(int xPos, int yPos, int w, int h, char key) 
        : x(xPos), y(yPos), width(w), height(h), isPressed(false), soundKey(key) {}

    // Function to draw the key
    void draw() {
        if (isPressed) {
            setfillstyle(SOLID_FILL, RED);  // Highlight pressed key in red
        } else {
            setfillstyle(SOLID_FILL, WHITE);  // Default key color
        }
        bar(x, y, x + width, y + height);   // Draw rectangle for key
        rectangle(x, y, x + width, y + height);  // Outline of key
    }

    // Function to play sound (simple Beep for demonstration)
    void playSound() {
        // Use ASCII value of soundKey to set frequency for simplicity
        int frequency = 200 + (soundKey - 'A') * 100;
        Beep(frequency, 300);  // Beep sound for 300 ms
    }

    // Check if key is pressed
    void press(char keyPressed) {
        if (keyPressed == soundKey) {
            isPressed = true;
            playSound();
        }
    }

    // Release the key
    void release(char keyPressed) {
        if (keyPressed == soundKey) {
            isPressed = false;
        }
    }

    // Accessor for key character
    char getSoundKey() const { return soundKey; }
};

// Piano class to manage multiple keys
class Piano {
private:
    Key* keys[7];  // Array of 7 keys, representing notes A-G

public:
    Piano() {
        // Initialize each key with its position and character
        int startX = 100, startY = 200, keyWidth = 50, keyHeight = 200;
        char notes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        for (int i = 0; i < 7; i++) {
            keys[i] = new Key(startX + i * keyWidth, startY, keyWidth, keyHeight, notes[i]);
        }
    }

    ~Piano() {
        // Cleanup keys
        for (int i = 0; i < 7; i++) {
            delete keys[i];
        }
    }

    // Draw the entire piano
    void draw() {
        for (int i = 0; i < 7; i++) {
            keys[i]->draw();
        }
    }

    // Handle key press for the piano
    void handleKeyPress(char keyPressed) {
        for (int i = 0; i < 7; i++) {
            keys[i]->press(keyPressed);
        }
        draw();  // Redraw piano to show pressed state
    }

    // Handle key release
    void handleKeyRelease(char keyReleased) {
        for (int i = 0; i < 7; i++) {
            keys[i]->release(keyReleased);
        }
        draw();  // Redraw piano to reset pressed state
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    Piano piano;

    char key;
    bool running = true;
    piano.draw();  // Initial piano display

    // Main loop to detect and handle key events
    while (running) {
        if (kbhit()) {  // Check if a key is pressed
            key = getch();
            if (key == 27) {  // ESC key to exit
                running = false;
            } else {
                piano.handleKeyPress(key);  // Press key
                delay(300);  // Delay to show key press visually
                piano.handleKeyRelease(key);  // Release key
            }
        }
    }

    closegraph();
    return 0;
}
