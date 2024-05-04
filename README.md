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
cut image from left: ./img-tool [file-name] cut-left [number of px] <br>
cut image from right: ./img-tool [file-name] cut-right [number of px] <br>

compiling the c file works with: gcc -std=c17 img-tool.c -o img-tool -lm (on bash with gcc installed)

for compiling [stb_image library](https://github.com/nothings/stb) is needed (in current form a folder called "stb_image" should be added to the workspacefolder which contains following files of the library:), the programm needs "stb_image_resize2.h", "stb_image_write.h" and "stb_image.h"

However if you just want to use the tool, you just need the binary file.

If you want to use it as an commandline tool (which I recommend) you have to add the folder where you store the binary to your Linux PATH Environment Variable<br>
You can do this in your terminal using the following commands (for more information I recommend you to do some own research):<br>
1. lookup and copy the directory path where you store the binary<br>
2. 
```
nano ~/.bashrc<br>
```
3. Put following at the end of the file:
```
# adding custom path to PATH
export PATH=$PATH:path/of/your/file
```
4. Ctrl+S<br>
5. Ctrl+X<br>
6.
```
source ~/.bashrc
```
