# Modifed from https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h#L169-L176

import math
gamma=2.6
num_values = 100
for x in range(num_values):
    print("{:3},".format(int(math.pow((x)/float(num_values - 1),gamma)*255+0.5)), end="")
    if (x + 1) % 10 == 0:
        print()
print()
