#include <drive_timer_fcn.h>

// Auto-relod software timer
static TimerHandle_t drive_timer = NULL;

// Software timer callback
void drive_timer_callback(TimerHandle_t xTimer)
{

    // Use flag to control motor direction
    if (direction == 1)
    {
        drive_straight(1);
    }
    else if (direction == 2)
    {
        drive_straight(-1);
    }
    else if (direction == 3)
    {
        left(mtr_power, mtr_power);
    }
    else if (direction == 4)
    {
        right(mtr_power, mtr_power);
    }
    else
    {
        stop();
    }
}

// Create an auto-reload software timer to update motor speed
void create_timer(void)
{

    drive_timer = xTimerCreate(
        "Drive Straight Timer",  // Name of timer
        20 / portTICK_PERIOD_MS, // Period of timer (in ticks), period 0.25s
        pdTRUE,                  // Auto-reload
        (void *)1,               // Timer ID
        drive_timer_callback);   // Callback function

    // Check if timer was created
    if (drive_timer == NULL)
    {
        Serial.println("Could not create timer!");
    }

    xTimerStart(drive_timer, portMAX_DELAY); // Start timer
}