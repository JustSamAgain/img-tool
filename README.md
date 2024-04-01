:README.md + tool still in work (although the features below already work): <br>
img-tool only supports jpg and png at the moment

print possible actions: ./img-tool actions? <br>
read properties: ./img-tool [file-name] p <br>
count how many px of which color: ./img-tool [file-name] count-px (at the moment only with 10 colors) <br>
transform to jpg: ./img-tool [file-name] to-jpg <br>
to png: ./img-tool [file-name] to-png <br>
grayscale to jpg: ./img-tool [file-name] g jpg <br>
grayscale to png: ./img-tool [file-name] g png <br>
black and white : ./img-tool [file-name] b-w [jpg/png] <br>
cut image number of px from below: ./img-tool [file-name] cut-below [number of px]<br>
cut image from top: ./img-tool [file-name] cut-top [number of px]<br>
cut image from right: ./img-tool [file-name] cut-right [number of px] <br>

compiling the c file works with: gcc -std=c17 img-tool.c -o img-tool -lm (on bash with gcc installed)

for compiling [stb_image library](https://github.com/nothings/stb) is needed (in current form a folder called "stb_image" should be added to the workspacefolder which contains following files of the library:), the programm needs "stb_image_resize2.h", "stb_image_write.h" and "stb_image.h"