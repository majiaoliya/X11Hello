#include <graphics.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <conio.h>
  #include <alloc.h>
  #include <dos.h>


  int main(void) {
        /* request auto detection */
        int gdriver=DETECT, gmode, err, color;
        int i, x[8], y[8], midx, midy, radius = 60;
        void far *image;
        unsigned long size;

        /* initialize graphic driver */
        initgraph(&gdriver, &gmode, "C:/TURBOC3/BGI");
        err = graphresult();

        if (err != grOk) {
                /* error occurred */
                printf("Graphics error: %s\n",
                                grapherrormsg(err));
                getch();
                return 0;
        }

        /* mid position in x and y-axis */
        midx = getmaxx() / 2;
        midy = getmaxy() / 2;

        /* below concentric circle will be sliced to 4 images */
        for (i = 1; i <= 5; i++) {
                if (i % 2 == 0) {
                        color = 15;
                } else {
                        color = i;
                }

                setcolor(color);
                setfillstyle(SOLID_FILL, color);
                circle(midx, midy, radius);
                floodfill(midx, midy, color);
                radius = radius - 10;
        }

        /* top left and bottom right for image 1 */
        x[0]= midx, y[0] = midy;
        x[1]= midx + 60, y[1] = midy + 60;

        /* top left and bottom right for image 2 */
        x[2]= midx, y[2] = midy - 60;
        x[3]= midx + 60, y[3] = midy;

        /* top left and bottom right for image 3 */
        x[4]= midx - 60, y[4] = midy;
        x[5]= midx, y[5] = midy + 60;

        /* top left and bottom right for image 4 */
        x[6]= midx - 60, y[6] = midy - 60;
        x[7]= midx, y[7] = midy;

        size = imagesize(x[0], y[0], x[1], y[1]);
        image = farmalloc(size);

        if (!image) {
                printf("Error: unable to allocate requested block");
                getch();
                closegraph();
                exit(1);
        }

        /* save image on screen to memory */
        getimage(x[0], y[0], x[1], y[1], image);

        /* print image from memory to onscreen */
        putimage(0, 0, image, NOT_PUT);

        getimage(x[2], y[2], x[3], y[3], image);
        putimage(0, 60, image, XOR_PUT);

        getimage(x[4], y[4], x[5], y[5], image);
        putimage(60, 0, image, OR_PUT);

        getimage(x[6], y[6], x[7], y[7], image);
        putimage(60, 60, image, NOT_PUT);

        /* clean up */
        getch();
        closegraph();
        return 0;
  }

