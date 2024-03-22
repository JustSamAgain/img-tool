#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(int argc, char *argv[]){
    if(argc<=1){
        printf("to-grey [file-name]\n");
        return 1;
        }

    int width, height, channels;
    unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
    if(img==NULL){
        printf("Error in loading the image\n");
        return(2);
    }

//"to-grey [file-name] p" (p for properties), "to-png", "to-jpg"
    if(argc==3 && *argv[2]!='g'){
        if(*argv[2]=='p'){
            printf("Image has width of %dpx, height of %dpx and %d channels\n", width, height, channels);
            return 0;
        }else if(strcmp(argv[2], "to-png")==0){
            printf("New name? ");
            char new_name[30];
            scanf("%s", new_name);
            stbi_write_png(strcat(new_name, ".png"), width, height, channels, img, width * channels);
        }else if(strcmp(argv[2], "to-jpg")==0){
            printf("New name? ");
            char new_name[30];
            scanf("%s", new_name);
            stbi_write_jpg(strcat(new_name, ".jpg"), width, height, channels, img, 100);
        }else return(3);
    }

//to-grey [file-name] g [jpg/png], - "g" for grey-scale
    if(argc == 3 || argc == 4){
        if(*argv[2]=='g'){
            
            size_t img_size = width * height * channels;
            int gray_channels = channels == 4 ? 2 : 1;
            size_t gray_img_size = width * height * gray_channels;
            
            unsigned char *gray_img = malloc(gray_img_size);
            if(gray_img == NULL){
                printf("Unable to allocate memory for the gray image.\n");
                return(4);
            }
            for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p+= channels, pg += gray_channels){
                *pg = (uint8_t)((*p +(*p + 1) + *(p + 2))/3.0);
                if(channels == 4){
                    *(pg + 1) = *(p + 3);
                }
            }
//---       + if 4 else jpg
            if(strcmp(argv[3], "jpg")==0){   //could implement: [file-name[-.jpg]]2.jpg
               stbi_write_jpg("new_image.jpg", width, height, gray_channels, gray_img, 100);
            }else if(strcmp(argv[3], "png")==0){
                stbi_write_png("new_image.png", width, height, gray_channels, gray_img, width * gray_channels);
            }
            stbi_image_free(img);
            free(gray_img);
            return 0;
            }else return(4);
    }
}