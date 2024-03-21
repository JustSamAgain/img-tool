
img-tool only supports jpg and png at the moment

stb_image library is needed (https://github.com/nothings/stb)(in current form in a folder called "stb_image"), the programm needs "stb_image_resize2.h", "stb_image_write.h" and "stb_image.h"

read properties: ./to-grey [file-name] p
transform to jpg: ./to-grey [file-name] to-jpg
to png: ./to-grey [file-name] to-png
grayscale to jpg: ./to-grey [file-name] g jpg
grayscale to png: ./to-grey [file-name] g png

rendering c file works with: gcc -std=c17 to-grey.c -o to-grey -lm (on bash with gcc installed)
