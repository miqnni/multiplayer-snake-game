#pragma once

#include <raylib.h>

class Controls
{
private:
    struct control_struct
    {
        KeyboardKey go_up_key;
        KeyboardKey go_right_key;
        KeyboardKey go_down_key;
        KeyboardKey go_left_key;
    } my_control_struct;

public:
    Controls(){};
    Controls(KeyboardKey go_up_key, KeyboardKey go_right_key, KeyboardKey go_down_key, KeyboardKey go_left_key)
        : my_control_struct{go_up_key, go_right_key, go_down_key, go_left_key} {}

    ~Controls(){};

    struct control_struct getMyControlStruct()
    {
        return my_control_struct;
    }

    KeyboardKey getGoUpKey()
    {
        return my_control_struct.go_up_key;
    }
    KeyboardKey getGoRightKey()
    {
        return my_control_struct.go_right_key;
    }
    KeyboardKey getGoDownKey()
    {
        return my_control_struct.go_down_key;
    }
    KeyboardKey getGoLeftKey()
    {
        return my_control_struct.go_left_key;
    }
};
