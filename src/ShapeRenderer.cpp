#include "ShapeRenderer.h"
#include <avr/pgmspace.h>
#include "FastMath.h"

#define IN_RANGE(value, min, max) (value >= min && value < max) //inclusive min, exclusive max
#define SWAP(x, y) do{ (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }while(0)

#define BUFFER_SIZE     (32)

void ShapeRenderer::render(TFT *tft, int8_t *shape, int length, Color color, int oldx, int oldy, float oldr,
                           int newx, int newy, float newr, float scale) {
    if (scale > 1) scale = 1;
    if (scale < 0.1f) scale = 0.1f;

    // Clear the buffer.
    buffer_clear(buffer1_);

    // Pre-calculate sine and cosine of the new rotation.
    float
        sine = newr == 0 ? 0.0f : fast_sin(newr),
        cosine = newr == 0 ? 1.0f : fast_cos(newr);

    // Loop trough every line in shape.
    for (int j = 0, i = 0; i < length; i++) {
        // Read line coordinates from the program memory.
        float lineStartX, lineStartY, lineEndX, lineEndY;

        if (scale == 1) {
            lineStartX = (int8_t) pgm_read_byte(shape + j++);
            lineStartY = (int8_t) pgm_read_byte(shape + j++);
            lineEndX = (int8_t) pgm_read_byte(shape + j++);
            lineEndY = (int8_t) pgm_read_byte(shape + j++);
        }
        else {
            lineStartX = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineStartY = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineEndX = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineEndY = (int8_t) pgm_read_byte(shape + j++) * scale;
        }

        // Rotate the line coordinates based on pre-calculated sine/cosine.
        int startX, startY, endX, endY;

        if (newr == 0) {
            startX = (int) lineStartX;
            startY = (int) lineStartY;
            endX = (int) lineEndX;
            endY = (int) lineEndY;
        }
        else {
            startX = (int) (cosine * lineStartX - sine * lineStartY);
            startY = (int) (sine * lineStartX + cosine * lineStartY);
            endX = (int) (cosine * lineEndX - sine * lineEndY);
            endY = (int) (sine * lineEndX + cosine * lineEndY);
        }

        // Draw the line on the buffer.
        buffer_draw_line(buffer1_, startX + BUFFER_SIZE / 2, startY + BUFFER_SIZE / 2, endX + BUFFER_SIZE / 2,
                         endY + BUFFER_SIZE / 2);

        // Draw the line on the screen.
        tft->drawLine(startX + newx, startY + newy, endX + newx, endY + newy, color);
    }

    // Pre-calculate sine and cosine of the old rotation.
    sine = fast_sin(oldr);
    cosine = fast_cos(oldr);

    // Loop trough every line in shape.
    for (int j = 0, i = 0; i < length; i++) {
        // Read line coordinates from the program memory.
        float lineStartX, lineStartY, lineEndX, lineEndY;

        if (scale == 1) {
            lineStartX = (int8_t) pgm_read_byte(shape + j++);
            lineStartY = (int8_t) pgm_read_byte(shape + j++);
            lineEndX = (int8_t) pgm_read_byte(shape + j++);
            lineEndY = (int8_t) pgm_read_byte(shape + j++);
        }
        else {
            lineStartX = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineStartY = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineEndX = (int8_t) pgm_read_byte(shape + j++) * scale;
            lineEndY = (int8_t) pgm_read_byte(shape + j++) * scale;
        }

        // Rotate the line coordinates based on pre-calculated sine/cosine.
        int startX, startY, endX, endY;

        if (oldr == 0) {
            startX = (int)lineStartX;
            startY = (int)lineStartY;
            endX = (int)lineEndX;
            endY = (int)lineEndY;
        }
        else {
            startX = (int) (cosine * lineStartX - sine * lineStartY);
            startY = (int) (sine * lineStartX + cosine * lineStartY);
            endX = (int) (cosine * lineEndX - sine * lineEndY);
            endY = (int) (sine * lineEndX + cosine * lineEndY);
        }

        // Loop trough every pixel in the line.
        int16_t
            dx, dy,
            dx2, dy2,
            err,
            stepx, stepy;

        // If the startX and endX are equal, the line must be vertical.
        if (startX == endX) {
            // If the startY is higher than endY, swap the values.
            if (startY > endY) { SWAP(endY, startY); }

            // Loop trough every pixel in the vertical line.
            for (int y = startY; y <= endY; y++) {
                // If the pixel is not set in the buffer, clear it from the screen by setting it black.
                if (!buffer_get_pixel(buffer1_, startX + (oldx - newx) + BUFFER_SIZE / 2,
                                      y + (oldy - newy) + BUFFER_SIZE / 2))
                    tft->drawPixel(startX + oldx, y + oldy, 0);
            }
        }
            // If the startY and endY are equal, the line must be horizontal.
        else if (startY == endY) {
            // If the startX is higher than endX, swap the values.
            if (startX > endX) { SWAP(endX, startX); }

            // Loop trough every pixel in the horizontal line.
            for (int x = startX; x <= endX; x++) {
                // If the pixel is not set in the buffer, clear it from the screen by setting it black.
                if (!buffer_get_pixel(buffer1_, x + (oldx - newx) + BUFFER_SIZE / 2,
                                      startY + (oldy - newy) + BUFFER_SIZE / 2))
                    tft->drawPixel(x + oldx, startY + oldy, 0);
            }
        }
        else {
            // Calculate the offset between the ending and starting point.
            dx = endX - startX;
            dy = endY - startY;
            if (dx < 0) {
                dx = -dx;
                stepx = -1;
            } else { stepx = +1; }

            if (dy < 0) {
                dy = -dy;
                stepy = -1;
            } else { stepy = +1; }

            // Store the offset, multiplied by 2 in dx2/dy2.
            dx2 = dx << 1;
            dy2 = dy << 1;

            // If the pixel is not set in the buffer, clear it from the screen by setting it black.
            {
                if (!buffer_get_pixel(buffer1_, startX + (oldx - newx) + BUFFER_SIZE / 2,
                                      startY + (oldy - newy) + BUFFER_SIZE / 2))
                    tft->drawPixel(startX + oldx, startY + oldy, 0);
            }
            // If the line is wide...
            if (dx > dy) {
                // Calculate the "error" between the first two columns.
                err = dy2 - dx;

                // Loop trough every column of the line.
                while (startX != endX) {
                    // If any error exists, move the start Y coordinate.
                    if (err >= 0) {
                        startY += stepy;
                        err -= dx2;
                    }

                    // Proceed one step.
                    startX += stepx;
                    err += dy2;

                    // If the pixel is not set in the buffer, clear it from the screen by setting it black.
                    if (!buffer_get_pixel(buffer1_, startX + (oldx - newx) + BUFFER_SIZE / 2,
                                          startY + (oldy - newy) + BUFFER_SIZE / 2))
                        tft->drawPixel(startX + oldx, startY + oldy, 0);
                }
            }
                // If the line is high...
            else {
                // Calculate the "error" between the first two rows.
                err = dx2 - dy;

                // Loop trough every row of the line.
                while (startY != endY) {
                    // If any error exists, move the start X coordinate.
                    if (err >= 0) {
                        startX += stepx;
                        err -= dy2;
                    }

                    // Proceed one step.
                    startY += stepy;
                    err += dx2;

                    // If the pixel is not set in the buffer, clear it from the screen by setting it black.
                    if (!buffer_get_pixel(buffer1_, startX + (oldx - newx) + BUFFER_SIZE / 2,
                                          startY + (oldy - newy) + BUFFER_SIZE / 2))
                        tft->drawPixel(startX + oldx, startY + oldy, 0);
                }
            }
        }
    }
}

void ShapeRenderer::buffer_draw_line(uint32_t *buffer, int startX, int startY, int endX, int endY) {
    int16_t
        dx, dy,
        dx2, dy2,
        err,
        stepx, stepy;

    // If the startX and endX are equal, the line must be vertical.
    if (startX == endX) {
        // If the startY is higher than endY, swap the values.
        if (startY > endY) { SWAP(endY, startY); }

        // Loop trough every pixel in the vertical line and set it.
        for (int y = startY; y <= endY; y++)
            buffer_set_pixel(buffer, startX, y, 1);
    }
        // If the startY and endY are equal, the line must be horizontal.
    else if (startY == endY) {
        // If the startX is higher than endX, swap the values.
        if (startX > endX) { SWAP(endX, startX); }

        // Loop trough every pixel in the horizontal line and set it.
        for (int x = startX; x <= endX; x++)
            buffer_set_pixel(buffer, x, startY, 1);
    }
    else {
        // Calculate the offset between the ending and starting point.
        dx = endX - startX;
        dy = endY - startY;
        if (dx < 0) {
            dx = -dx;
            stepx = -1;
        } else { stepx = +1; }
        if (dy < 0) {
            dy = -dy;
            stepy = -1;
        } else { stepy = +1; }

        // Store the offset, multiplied by 2 in dx2/dy2.
        dx2 = dx << 1;
        dy2 = dy << 1;

        // Set the pixel in the buffer.
        buffer_set_pixel(buffer, startX, startY, 1);
        if (dx > dy) {
            // Calculate the "error" between the first two columns.
            err = dy2 - dx;

            // Loop trough every column of the line.
            while (startX != endX) {
                // If any error exists, move the start Y coordinate.
                if (err >= 0) {
                    startY += stepy;
                    err -= dx2;
                }

                // Proceed one step.
                startX += stepx;
                err += dy2;

                // Set the pixel in the buffer.
                buffer_set_pixel(buffer, startX, startY, 1);
            }
        }
        else {
            // Calculate the "error" between the first two rows.
            err = dx2 - dy;

            // Loop trough every row of the line.
            while (startY != endY) {
                // If any error exists, move the start X coordinate.
                if (err >= 0) {
                    startX += stepx;
                    err -= dy2;
                }

                // Proceed one step.
                startY += stepy;
                err += dx2;

                // Set the pixel in the buffer.
                buffer_set_pixel(buffer, startX, startY, 1);
            }
        }
    }
    return;
}

void ShapeRenderer::buffer_set_pixel(uint32_t *buffer, int x, int y, uint8_t value) {
    if (!value || !IN_RANGE(x, 0, BUFFER_SIZE) || !IN_RANGE(y, 0, BUFFER_SIZE)) return;
    buffer[y] |= ((uint32_t) 1 << x);
}

uint8_t ShapeRenderer::buffer_get_pixel(uint32_t *buffer, int x, int y) {
    if (!IN_RANGE(x, 0, BUFFER_SIZE) || !IN_RANGE(y, 0, BUFFER_SIZE)) return 0;
    return buffer[y] & ((uint32_t) 1 << x) ? 1 : 0;
}

void ShapeRenderer::buffer_clear(uint32_t *buffer) {
    for (uint8_t i = 0; i < 32; i++)
        buffer[i] = 0;
}
