#ifndef __GUI900_ELEMENT_H__
#define __GUI900_ELEMENT_H__

#include <Arduino.h>
#include <LinkedList.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"

namespace Gui900
{
    class Element;

    /// @brief A container that contains UI elements. Can be a page or element.
    class Container
    {
    public:
        /// @brief The app this container belongs to.
        App *app;
        /// @brief The background color of the content area of the container.
        uint16_t backColor;
        /// @brief The list of the container's children.
        LinkedList<Element *> children;
        /// @brief Indicates whether the container is currently being shown.
        bool isActive;

        /// @brief Returns the coordinates of the content area of the container.
        virtual int getContentAreaAbsoluteX() = 0;
        /// @brief Returns the coordinates of the content area of the container.
        virtual int getContentAreaAbsoluteY() = 0;
        /// @brief Returns the width of the content area of the container.
        virtual int getInnerWidth() = 0;
        /// @brief Returns the height of the content area of the container.
        virtual int getInnerHeight() = 0;

        /// @brief Adds a child element to the container.
        /// @param child The element to add.
        void addChild(Element *child);

    protected:
        void drawChildren(Adafruit_GFX &gfx);
        void undrawChildren(Adafruit_GFX &gfx);
    };

    /// @brief Represents a UI element
    class Element
    {
    public:
        /// @brief The app this element belongs to.
        App *app;
        /// @brief The position of the element relative to its parent's content area.
        int x;
        /// @brief The position of the element relative to its parent's content area.
        int y;
        /// @brief The width of the element.
        int width;
        /// @brief The height of the element.
        int height;
        /// @brief The container in which this element is.
        Container *parent;
        /// @brief Indicates whether the element is currently being shown.
        bool isActive;

        /// @brief Returns the coordinates of the element relative to the screen.
        int getAbsoluteX() { return x + (parent->getContentAreaAbsoluteX()); }
        /// @brief Returns the coordinates of the element relative to the screen.
        int getAbsoluteY() { return y + (parent->getContentAreaAbsoluteY()); }

        /// @brief Tests whether a point is inside the element
        /// @param x The coordinates of the point
        /// @param y The coordinates of the point
        /// @return True if the point is inside the element, false otherwise.
        virtual bool containsPoint(int x, int y);

        /// @brief Called by the app when the pointer is pressed.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        virtual void onPointerDown(int x, int y) {}
        /// @brief Called by the app when the pointer is released.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        virtual void onPointerUp(int x, int y) {}
        /// @brief Called by the app when the pointer is moved.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        /// @param isDown Whether the pointer is currently being pressed.
        virtual void onPointerMove(int x, int y, bool isDown) {}

        /// @brief Draws the element to the screen. Only for internal use.
        virtual void draw(Adafruit_GFX &gfx) = 0;

        /// @brief Clears the area occupied by the element, filling it with the parent container's background color. Only for internal use.
        virtual void undraw(Adafruit_GFX &gfx) = 0;
    };
}

#endif /* __GUI900_ELEMENT_H__ */
