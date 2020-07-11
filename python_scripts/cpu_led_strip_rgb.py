# Simple test for NeoPixels on Raspberry Pi
import time
import board
import neopixel
import psutil


# Choose an open pin connected to the Data In of the NeoPixel strip, i.e. board.D18
# NeoPixels must be connected to D10, D12, D18 or D21 to work.
pixel_pin = board.D18

# The number of NeoPixels
num_pixels = 8

# The order of the pixel colors - RGB or GRB. Some NeoPixels have red and green reversed!
# For RGBW NeoPixels, simply change the ORDER to RGBW or GRBW.
ORDER = neopixel.GRB

pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.2, auto_write=False, pixel_order=ORDER
)

RED = (255, 0, 0)
GREEN = (0, 255, 0)
YELLOW = (255, 150, 0)
OFF = (0,0,0)

while True:
    y = int(psutil.cpu_percent())
    #print(y)
    x = int(round((num_pixels*y) // 100))
    if x <= 1:
        colore = GREEN
    else:
        if x >= 5:
            colore = RED
        else:
            colore = YELLOW
    #z = int(x)
    #print(x)
    #pixels.fill(OFF)
    pixels[x] = colore
    for i in range(x):
        #pixels[i] = colore
        if i == 0:
            pixels[0]= GREEN
        else:
            if i == 1:
                pixels[1]= GREEN
            else:
                if i == 2:
                    pixels[2]= YELLOW
                else:
                    if i == 3:
                        pixels[3]= YELLOW
                    else:
                        if i == 4:
                            pixels[4]= YELLOW
                        else:
                            if i == 5:
                                pixels[5]= RED
                            else:
                                if i == 6:
                                    pixels[6]= RED
                                else:
                                    if i == 7:
                                        pixels[7]= RED
                                    else:
                                        if i == 8:
                                            pixels[7]= RED
    pixels.show()
    pixels.fill(OFF)
    time.sleep(0.5)
    
