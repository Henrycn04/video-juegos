#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <tuple>

/**
 * @brief Manages keyboard and mouse input states
 * 
 * Tracks keyboard actions, mouse buttons, and cursor position
 * with action-name mapping functionality.
 */
class ControllerManager {
private:
    std::map<std::string, int> actionKeyName;  ///< Maps action names to keyboard key codes
    std::map<int, bool> keyDown;              ///< Tracks pressed state of keyboard keys

    std::map<std::string, int> mouseButtonName; ///< Maps action names to mouse button codes
    std::map<int, bool> mouseButtonDown;       ///< Tracks pressed state of mouse buttons

    int mousePosX;                            ///< Current X position of mouse cursor
    int mousePosY;                            ///< Current Y position of mouse cursor

public:
    /**
     * @brief Construct a new Controller Manager object
     */
    ControllerManager();

    /**
     * @brief Destroy the Controller Manager object
     */
    ~ControllerManager();

    /**
     * @brief Clears all input states and mappings
     */
    void Clear();

    // Keyboard related methods
    
    /**
     * @brief Add a keyboard action mapping
     * @param action Name of the action to map
     * @param keyCode SDL key code for the action
     */
    void AddActionKey(const std::string& action, int keyCode);

    /**
     * @brief Set key state to pressed
     * @param keyCode SDL key code of the pressed key
     */
    void KeyDown(int keyCode);

    /**
     * @brief Set key state to released
     * @param keyCode SDL key code of the released key
     */
    void KeyUp(int keyCode);

    /**
     * @brief Check if an action is currently active (key pressed)
     * @param action Name of the action to check
     * @return true if the action's key is pressed
     * @return false otherwise
     */
    bool IsActionActivated(const std::string& action);

    // Mouse related methods
    
    /**
     * @brief Add a mouse button action mapping
     * @param action Name of the action to map
     * @param buttonCode SDL mouse button code
     */
    void AddMouseButton(const std::string& action, int buttonCode);

    /**
     * @brief Set mouse button state to pressed
     * @param buttonCode SDL mouse button code
     */
    void MouseButtonDown(int buttonCode);

    /**
     * @brief Set mouse button state to released
     * @param buttonCode SDL mouse button code
     */
    void MouseButtonUp(int buttonCode);

    /**
     * @brief Check if a mouse button action is pressed
     * @param name Name of the mouse action to check
     * @return true if the button is pressed
     * @return false otherwise
     */
    bool IsMouseButtonDown(const std::string& name);

    /**
     * @brief Update mouse cursor position
     * @param x New X coordinate
     * @param y New Y coordinate
     */
    void SetMousePosition(int x, int y);

    /**
     * @brief Get current mouse cursor position
     * @return std::tuple<int, int> Current (x, y) coordinates
     */
    std::tuple<int, int> GetMousePosition();
};

#endif // CONTROLLER_MANAGER_HPP