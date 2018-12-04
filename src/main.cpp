#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zint.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main(int argc, char **argv) {


    while (1) {
        struct zint_symbol *my_symbol;
        int error_number;
        int rotate_angle;

        rotate_angle = 0;
        my_symbol = ZBarcode_Create();
        my_symbol->input_mode = UNICODE_MODE;

        int ver;
        char str[90];
        scanf("%d %s", &ver, str);

        my_symbol->symbology = ver;
        error_number = ZBarcode_Encode(my_symbol, (unsigned char*) str, strlen(str));
        if (error_number != 0) {
                printf("%s\n", my_symbol->errtxt);
        }
        if (error_number < 5) {
            error_number = ZBarcode_Print(my_symbol, rotate_angle);
            if (error_number != 0) {
                printf("%s\n", my_symbol->errtxt);
                break;
            }

            namedWindow("bgr", WINDOW_AUTOSIZE);
            Mat bgr = Mat(my_symbol->bitmap_height, my_symbol->bitmap_width, CV_8UC3, my_symbol->bitmap);
            imshow("bgr", bgr);
            while (1) {
                if (waitKey(1) == 27) {
                    break;
                }
            }
            destroyWindow("bgr");
        }
        ZBarcode_Delete(my_symbol);
    }


    return 0;
}

