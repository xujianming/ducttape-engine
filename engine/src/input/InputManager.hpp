
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_INPUT_INPUTMANAGER
#define DUCTTAPE_ENGINE_INPUT_INPUTMANAGER

#define OIS_DYNAMIC_LIB
#include <OIS.h>
#include <OgreWindowEventUtilities.h>

#include "utils/Logger.hpp"
#include "utils/Utils.hpp"
#include "MouseEvent.hpp"
#include "KeyboardEvent.hpp"
#include "event/WindowClosedEvent.hpp"
#include "Manager.hpp"

namespace dt {

/**
  * Used to capture all OIS input events and forward them to the Event system, and also for unbuffered input.
  */
class InputManager : public Manager,
        public OIS::KeyListener,
        public OIS::MouseListener,
        public Ogre::WindowEventListener {
public:
    enum MouseCursorMode {
        HIDDEN,
        SYSTEM,
        GRAPHICAL
    };

    /**
      * Default constructor.
      */
    InputManager();

    void Initialize();
    void Deinitialize();
    static InputManager* Get();

    /**
      * Sets the render window.
      * @param window The render window.
      */
    void SetWindow(Ogre::RenderWindow* window);

    /**
      * Captures the input devices and calls all events.
      */
    void Capture();

    /**
      * Sets whether the input deviced are jailed. If true, the mouse cannot move outside the window
      * and the keyboard events are not sent to other applications. Useful to disable for debugging.
      * Default: false.
      * @param jail_input Whether to jail the input devices.
      */
    void SetJailInput(bool jail_input = false);

    /**
      * Returns whether the input devices are jailed (for details on that see InputManager::SetJailInput).
      * @returns Whether to jail the input devices.
      */
    bool GetJailInput() const;

    // OIS::KeyListener
    virtual bool keyPressed(const OIS::KeyEvent& event);
    virtual bool keyReleased(const OIS::KeyEvent& event);

    // OIS::MouseListener
    virtual bool mouseMoved(const OIS::MouseEvent& event);
    virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID button);
    virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID button);

    // Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* window);
    virtual void windowClosed(Ogre::RenderWindow* window);

    /**
      * Returns the mouse object.
      * @returns The mouse object.
      */
    OIS::Mouse* GetMouse();

    /**
      * Returns the keyboard object.
      * @returns The keyboard object.
      */
    OIS::Keyboard* GetKeyboard();

    /**
      * Sets the mouse cursor mode. Available modes are:
      * - HIDDEN (no cursor)
      * - SYSTEM (show the default system cursor)
      * - GRAPHICAL (use the GUI system to show the cursor)
      * @param mode The mouse cursor mode.
      */
    void SetMouseCursorMode(MouseCursorMode mode);

    /**
      * Gets the mouse cursor mode.
      * @returns The mouse cursor mode.
      */
    MouseCursorMode GetMouseCursorMode() const;

private:
    void _ResetInputSystem();
    void _DestroyInputSystem();
    void _CreateInputSystem();

    Ogre::RenderWindow* mWindow;        //!< The Window used for input (from the DisplayManager).
    OIS::InputManager* mInputSystem;    //!< The OIS input manager.
    OIS::Mouse* mMouse;                 //!< The mouse object.
    OIS::Keyboard* mKeyboard;           //!< The keyboard object.

    MouseCursorMode mMouseCursorMode;
    bool mJailInput;                    //!< Whether the input devices are jailed (for details on that see InputManager::SetJailInput).
};

}

#endif
