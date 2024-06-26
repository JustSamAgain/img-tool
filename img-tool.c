//list for further features:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

typedef struct{
    char defined;
    int r;
    int g;
    int b;
    int num;
} num_col;

void add_array(int r, int g, int b, num_col *arr, int arr_size);
void greyscale(unsigned char *img, unsigned char *new_image, size_t img_size, int channels, int new_channels);
void black_n_white(unsigned char *img, unsigned char *new_image, size_t img_size, int channels, int new_channels);

int main(int argc, char *argv[]){
    if(argc==2){
        //manual for using the tool !!extend if implementing further features
        if(strcmp(argv[1], "actions?")==0){
            printf("./img-tool [file-name] [action or edit]\n");
            printf("[actions]:\n");
            printf("    [p] print properties of image (width, height, channels)\n");
            printf("    [to-png] convert to png\n");
            printf("    [to-jpg] convert to jpg\n");
            printf("    [count-px] count number of px per color\n");
            printf("[edit]:\n");
            printf("    [g [filetype]] makes greyscale version of image in given filetype\n");
            printf("    [b-w [ft]] makes black-and-white version of image\n");
            printf("    [cut-below [number of px]] cut number of px from below\n");
            printf("    [cut-top [number of px]] cut number of px from top\n");
            printf("    [cut-left [number of px]] cut from left side\n");
            printf("    [cut-right [number of px]] cut from right\n");
            printf("[filetype]:\n");
            printf("    [jpg]\n");
            printf("    [png]\n");
            printf("For further questions please go to https://github.com/JustSamAgain/img-tool/issues\n");
            return 0;
        }else{
            printf("./img-tool [file-name] [[>action<]or[>edit< >file-type<]] or ./img-tool actions?\n");
            return 1;
        }
    }

    int width, height, channels;
    unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
    size_t img_size = width * height * channels;

    if(img==NULL){
        printf("Error in loading the image\n");
        return(2);
    }

//"img-tool [file-name] p" (p for properties), "to-png", "to-jpg", "count-px"
    if(argc==3){
        //print properties of image
        if(*argv[2]=='p'){
            printf("Image has width of %dpx, height of %dpx and %d channels\n", width, height, channels);
            return 0;
        }else if(strcmp(argv[2], "to-png")==0){
            //make-png
            printf("New name? ");
            char new_name[30];
            scanf("%s", new_name);
            stbi_write_png(strcat(new_name, ".png"), width, height, channels, img, width * channels);
        }else if(strcmp(argv[2], "to-jpg")==0){
            //make jpg
            printf("New name? ");
            char new_name[30];
            scanf("%s", new_name);
            stbi_write_jpg(strcat(new_name, ".jpg"), width, height, channels, img, 100);
        }else if(strcmp(argv[2], "count-px")==0){
            //count number of px per color in image
            int array_size = 10;
            num_col colors[array_size]; //still have to work on that
            for(int i=0; i<array_size; i++){
                colors[i].defined='\0';
            }
            if(channels>2){
                for(unsigned char *p = img; p!=img+img_size; p+= channels){
                    add_array(*p, *(p+1), *(p+2), colors, array_size);
                }
                int i;
                while(colors[i].defined!='\0' && i<array_size){
                    printf("%i : %i : %i counted %i times\n", colors[i].r, colors[i].g, colors[i].b, colors[i].num);
                    i++;
                }
            }else if(channels=2){
                for(unsigned char *p = img; p!=img+img_size; p+= channels){
                    add_array(*p, *(p+1), '-', colors, array_size);
                }
                int i;
                while(colors[i].defined!='\0' && i<array_size){
                    printf("%i : %i : %c counted %i times\n", colors[i].r, colors[i].g, colors[i].b, colors[i].num);
                    i++;
                }
            }else{
                printf("Error: Problem with channels.\n");
                return 8;
            }
        }else{
            printf("Error: couldn't find [action]\n");
            printf("./img-tool [file-name] [[>action<]or[>edit< >file-type<]] or ./img-tool actions?\n");
            return(3);
            };
    }

//img-tool [file-name] g [jpg/png], - "g" for grey-scale, "b-w" for black and white
    if(argc == 4){
        if(*argv[2]=='g' || strcmp(argv[2], "b-w")==0){
            
            int new_channels = channels == 4 ? 2 : 1;
            size_t new_img_size = width * height * new_channels;
            
            unsigned char *new_image = malloc(new_img_size);
            if(new_image == NULL){
                printf("Unable to allocate memory for the image.\n");
                return(4);
            }
            //greyscale
            if(*argv[2]=='g'){
                greyscale(img, new_image, img_size, channels, new_channels);
            }else{
            //black-and-white
                black_n_white(img, new_image, img_size, channels, new_channels);
            }
            
            printf("New name? ");
            char new_name[30];
            scanf("%s", new_name);

            if(strcmp(argv[3], "jpg")==0){   //could implement: [file-name[-.jpg]]2.jpg
               stbi_write_jpg(strcat(new_name, ".jpg"), width, height, new_channels, new_image, 100);
            }else if(strcmp(argv[3], "png")==0){
                stbi_write_png(strcat(new_name, ".png"), width, height, new_channels, new_image, width * new_channels);
            }else{
                printf("only supports jpg and png\n");
                printf("./img-tool [file-name] >edit< >file-type<   or ./img-tool actions?\n");
                return(5);
            }
            stbi_image_free(img);
            free(new_image);
            return 0;
        }else if(strcmp(argv[2], "cut-below")==0 || strcmp(argv[2], "cut-top")==0 ||
        strcmp(argv[2], "cut-left")==0 || strcmp(argv[2], "cut-right")==0){
                int px = atoi(argv[3]);
                size_t new_img_size;
                int new_width;
                int new_height;
                if(strcmp(argv[2], "cut-below")==0 || strcmp(argv[2], "cut-top")==0){
                    if(px>=height || px<0){
                        printf("You cannot cut more than: Height %d\n", height);
                        return 6;
                    }
                    new_img_size = width * (height-px) * channels;
                    new_width = width;
                    new_height = (height-px);
                }else{
                    if(px>=width || px<0){
                        printf("You cannot cut more than: Width %d\n", width);
                        return 6;
                    }
                    new_img_size = (width-px) * height * channels;
                    new_width = (width-px);
                    new_height = height;
                }
                
                unsigned char *new_image = malloc(new_img_size);

                if(strcmp(argv[2], "cut-below")==0){
                    for(unsigned char *p = img, *pg=new_image; p!=img+new_img_size; *p++, *pg++){
                        *pg = (uint8_t)*p;
                    }
                }else if(strcmp(argv[2], "cut-top")==0){
                    for(unsigned char *p = (img+(width*channels*px)), *pg=new_image; p!=img+img_size; *p++, *pg++){
                        *pg = (uint8_t)*p;
                    }
                }else if(strcmp(argv[2], "cut-left")==0){
                    int ctr = 0;
                    for(unsigned char *p = img, *pg=new_image; p!=img+img_size; *p++, ctr++){
                        if((ctr%(width*channels))>=(px*channels)){
                            *pg=(uint8_t)*p;
                            *pg ++;
                        }else{
                            *p += ((px*channels)-1);
                        }
                    }
                }else{ //cut right
                int ctr = 0;
                    for(unsigned char *p = img, *pg=new_image; p!=img+img_size; *p++, ctr++){
                        if((ctr%(width*channels))<((width-px)*channels)){
                            *pg=(uint8_t)*p;
                            *pg ++;
                        }else{
                            *p += ((px*channels)-1);
                        }
                    }
                }

                char new_name[30];
                printf("New name?: ");
                scanf("%s", new_name);
                if(channels==4){
                    stbi_write_png(strcat(new_name, ".png"), new_width, new_height, channels, new_image, new_width * channels);
                }else{
                    stbi_write_jpg(strcat(new_name, ".jpg"), new_width, new_height, channels, new_image, 100);
                }
                stbi_image_free(img);
                free(new_image);
                return 0;
            }else{
                printf("couldn't find [edit]\n");
                printf("./img-tool [file-name]  [[>action<]or[>edit< >file-type<]] or ./img-tool actions?\n");
                return(7);
            }
    }
}

void add_array(int r, int g, int b, num_col *arr, int arr_size)
{
    for(int i = 0; i<arr_size; i++){
        if( //in array
            arr[i].defined != '\0' && arr[i].r == r &&
            arr[i].g == g && arr[i].b == b
        ){
            arr[i].num++;
            return;
        }else if(arr[i].defined == '\0'){ //not in array
            arr[i].defined = 1;
            arr[i].r = r;
            arr[i].g = g;
            arr[i].b = b;
            arr[i].num = 1;
            return;
        }
    }
}

void greyscale(unsigned char *img, unsigned char *new_image, size_t img_size, int channels, int new_channels){
    for(unsigned char *p = img, *pg = new_image; p != img + img_size; p+= channels, pg += new_channels){
                    *pg = (uint8_t)((*p +(*p + 1) + *(p + 2))/3.0);
                    if(channels == 4){
                        *(pg + 1) = *(p + 3);
                    }
                }
}

void black_n_white(unsigned char *img, unsigned char *new_image, size_t img_size, int channels, int new_channels){
    for(unsigned char *p = img, *pg = new_image; p != img + img_size; p+= channels, pg += new_channels){
                    int average = (uint8_t)((*p +(*p + 1) + *(p + 2))/3.0);
                    if(average>127.5){ //if darker than 127.5
                        *pg = (uint8_t)255;
                    }else{*pg = (uint8_t)0;}
                    if(channels == 4){
                        *(pg + 1) = *(p + 3);
                    }
                }
}