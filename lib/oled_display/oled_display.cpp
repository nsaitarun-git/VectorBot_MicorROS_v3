#include <oled_display.h>

// OLED display settings
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    //   QT-PY / XIAO

// Display object
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawRightArrow(Adafruit_SH1106G &display)
{
    display.clearDisplay();

    for (int i = -1; i <= 1; i++)
    {
        display.drawLine(30, 15 + i, 80, 15 + i, SH110X_WHITE);
    }
    // Upper diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(80, 15, 60 + i, 10 + j, SH110X_WHITE);
        }
    }
    // Lower diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(80, 15, 60 + i, 20 + j, SH110X_WHITE);
        }
    }
    display.display();
}

void drawLeftArrow(Adafruit_SH1106G &display)
{
    display.clearDisplay();

    for (int i = -1; i <= 1; i++)
    {
        display.drawLine(80, 15 + i, 30, 15 + i, SH110X_WHITE);
    }
    // Upper diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(30, 15, 50 + i, 10 + j, SH110X_WHITE);
        }
    }
    // Lower diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(30, 15, 50 + i, 20 + j, SH110X_WHITE);
        }
    }
    display.display();
}

void drawForwardArrow(Adafruit_SH1106G &display)
{
    display.clearDisplay();

    // up
    for (int i = -1; i <= 1; i++)
    {
        display.drawLine(55 + i, 5, 55 + i, 25, SH110X_WHITE);
    }
    // Left diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(45, 15, 55 + i, 5 + j, SH110X_WHITE);
        }
    }
    // Right diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(65, 15, 55 + i, 5 + j, SH110X_WHITE);
        }
    }
    display.display();
}

void drawBackwardArrow(Adafruit_SH1106G &display)
{
    display.clearDisplay();

    // Vertical line
    for (int i = -1; i <= 1; i++)
    {
        display.drawLine(55 + i, 5, 55 + i, 20, SH110X_WHITE);
    }
    // Left diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(45, 15, 55 + i, 20 + j, SH110X_WHITE);
        }
    }
    // Right diagonal
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            display.drawLine(65, 15, 55 + i, 20 + j, SH110X_WHITE);
        }
    }
    display.display();
}

void drawStopCircle(Adafruit_SH1106G &display)
{
    display.clearDisplay();

    for (int i = -1; i <= 1; i++)
    {
        display.drawCircle(64, 15, 10 + i, SH110X_WHITE);
    }
    display.display();
}

/************* Main *************/
void displayArrow(String request)
{
    if (request == "right")
    {
        drawRightArrow(display);
    }
    else if (request == "left")
    {
        drawLeftArrow(display);
    }
    else if (request == "forward")
    {
        drawForwardArrow(display);
    }
    else if (request == "backward")
    {
        drawBackwardArrow(display);
    }
    else
    {
        drawStopCircle(display);
    }
}