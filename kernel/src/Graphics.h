#pragma once
#include "FrameBuffer.h"
#include "FontDefinitions.h"
#include "GraphicsHelper.h"
#include <stdint.h>
#include "math.h"
class Graphics
{
public:
    Framebuffer *TargetFramebuffer;
    PSF1_FONT *PSF1_Font;
    uint32_t *pixPtr;
    uint64_t totalScreenSize;

    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];

    Graphics(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font);
    /**
     * @brief Clear the screen with a given color
     * @param color The color to fill the screen with in (0xRRGGBB)
     */
    void clear(uint32_t color);
    /**
     * Function to draw a pixel on the screen
     * @param color The color of the pixel to be drawn
     * @param x The x-coordinate of the pixel to be drawn
     * @param y The y-coordinate of the pixel to be drawn
     */
    void drawPixel(uint32_t color, uint32_t x, unsigned y);
    /**
     * fills a rectangle on the framebuffer with specified color
     * @param color uint32_teger that defines the color of the rectangle
     * @param xOff uint32_teger that defines the X offset of the rectangle
     * @param yOff uint32_teger that defines the Y offset of the rectangle
     * @param width uint32_teger that defines the width of the rectangle
     * @param height uint32_teger that defines the height of the rectangle
     */
    void fillRect(uint32_t color, int32_t xOff, int32_t yOff, int32_t width, int32_t height);

    /**
     * outlines a rectangle on the framebuffer with specified color
     * @param color uint32_teger that defines the color of the rectangle
     * @param xOff uint32_teger that defines the X offset of the rectangle
     * @param yOff uint32_teger that defines the Y offset of the rectangle
     * @param width uint32_teger that defines the width of the rectangle
     * @param height uint32_teger that defines the height of the rectangle
     */
    void drawRect(uint32_t color, int32_t x, int32_t y, int32_t width, int32_t height);

    /**
    Renders a single character to the screen at the specified coordinates with the given color and scaling.
    @param color The color to use when rendering the character.
    @param chr The character to render.
    @param xOff The x-coordinate to start drawing the character at.
    @param yOff The y-coordinate to start drawing the character at.
    @param width The width scaling factor to apply to the character.
    @param height The height scaling factor to apply to the character.
    */
    void putChar(uint32_t color, char chr, int32_t xOff, int32_t yOff, float width = 1, float height = 1);

    /**
     *prints a string of text to the screen.
     * @param color The color to use for the text.
     * @param str The string to print.
     * @param xOff The x-offset of the text on the screen.
     * @param yOff The y-offset of the text on the screen.
     * @param width The width of each character (defaults to 1).
     * @param height The height of each character (defaults to 1).
     * @return The x-offset after printing the text.
     */
    uint32_t print(uint32_t color, const char *str, int32_t xOff, int32_t yOff, float width = 1, float height = 1);

    void render();
    
    uint32_t GetPix(uint32_t x, uint32_t y);

    void DrawOverlayMouseCursor(uint8_t *mouseCursor, Point position);
    void ClearMouseCursor(uint8_t *mouseCursor, Point position);
    bool MouseDrawn;
};

extern Graphics *graphics;