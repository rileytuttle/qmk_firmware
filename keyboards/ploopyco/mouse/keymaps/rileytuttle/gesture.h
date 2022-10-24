#pragma once

enum GestureType
{
    GESTURE_TYPE_NONE,
    GESTURE_TYPE_VERTICAL,
    GESTURE_TYPE_HORIZONTAL,
};

typedef enum
{
    GESTURE_DIRECTION_NONE,
    GESTURE_DIRECTION_UP,
    GESTURE_DIRECTION_DOWN,
    GESTURE_DIRECTION_LEFT,
    GESTURE_DIRECTION_RIGHT
} GestureDirection;

typedef struct {
    bool pressed;
} GestureData;

void gesture_update_key_state(GestureData *data, const bool pressed)
{ 
    data->pressed = pressed;
}

GestureDirection gesture_update(GestureData *data, const report_mouse_t mouse_report)
{
    int gesture_type = GESTURE_TYPE_NONE;
    int gesture_dir = GESTURE_DIRECTION_NONE;
    if (data->pressed)
    {
        // interpret the mouse gesture
        if (mouse_report.x != 0 && mouse_report.y != 0)
        {
            if (abs(mouse_report.x) >= abs(mouse_report.y)) { gesture_type = GESTURE_TYPE_VERTICAL; }
            else { gesture_type = GESTURE_TYPE_HORIZONTAL; }
        }
        else if (mouse_report.x != 0)
        {
            gesture_type = GESTURE_TYPE_VERTICAL;
        }
        else if (mouse_report.y != 0)
        {
            gesture_type = GESTURE_TYPE_HORIZONTAL;
        }
    }
    switch (gesture_type)
    {
        case GESTURE_TYPE_VERTICAL:
            if (mouse_report.y > 0) { gesture_dir = GESTURE_DIRECTION_LEFT; }
            else if (mouse_report.y < 0) { gesture_dir = GESTURE_DIRECTION_RIGHT; }
            break;
        case GESTURE_TYPE_HORIZONTAL:
            if (mouse_report.x > 0) { gesture_dir = GESTURE_DIRECTION_DOWN; }
            else if (mouse_report.x < 0) { gesture_dir = GESTURE_DIRECTION_UP; }
            break;
        case GESTURE_TYPE_NONE:
            gesture_dir = GESTURE_DIRECTION_NONE;
            break;
    }
    return gesture_dir;
}
