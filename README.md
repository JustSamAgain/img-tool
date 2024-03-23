:README.md + tool still in work (although the features below already work):
img-tool only supports jpg and png at the moment

stb_image library is needed (https://github.com/nothings/stb) (in current form a folder called "stb_image" should be added to the workspacefolder which contains following files of the library:), the programm needs "stb_image_resize2.h", "stb_image_write.h" and "stb_image.h"

print possible actions: ./img-tool actions?
read properties: ./img-tool [file-name] p
count how many px of which color: ./img-tool [file-name] count-px (at the moment only with 10 colors)
transform to jpg: ./img-tool [file-name] to-jpg
to png: ./img-tool [file-name] to-png
grayscale to jpg: ./img-tool [file-name] g jpg
grayscale to png: ./img-tool [file-name] g png
black and white : ./img-tool [file-name] b-w [jpg/png]

rendering the c file works with: gcc -std=c17 img-tool.c -o img-tool -lm (on bash with gcc installed)
