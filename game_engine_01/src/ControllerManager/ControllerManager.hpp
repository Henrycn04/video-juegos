#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP
#include <SDL2/SDL.h>
#include <map>
#include <string>


class ControllerManager {
    private:
    std::map<std::string, int> actionKeyName;
    std::map<int, bool> keyDown;

    std::map<std::string, int> mouseButtonName;
    std::map<int, bool> mouseButtonDown;

    int mousePosX;
    int mousePosY;

    public:
    ControllerManager();
    ~ControllerManager();
    void Clear();
    //keyboard
    void AddActionKey(const std::string& action, int keyCode);
    void KeyDown(int keyCode);
    void KeyUp(int keyCode);
    bool IsActionActivated(const std::string& action);
    //mouse
    void AddMouseButton(const std::string& action, int buttonCode);
    void MouseButtonDown(int buttonCode);
    void MouseButtonUp(int buttonCode);
    bool IsMouseButtonDown(const std::string& name);

    void SetMousePosition(int x, int y);
    std::tuple<int, int> GetMousePosition();
};


#endif // CONTROLLER_MANAGER_HPP