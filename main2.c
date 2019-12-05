//#include <X11/Xlib.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main() {
//	Display* d;
//	d = XOpenDisplay(NULL);
//	if(!d) {
//		printf("can not open windows\n");
//		return -1;
//	}
//	int s = DefaultScreen(d);
//	Window w = XCreateSimpleWindow(d, RootWindow(d,s), 
//				600, 800, 800, 600, 1, 777215, 111111);
//	XSelectInput(d, w, ExposureMask | KeyPressMask);
//	XMapWindow(d, w);
//	XEvent e;
//	const char* fontName = "-*-fixed-medium-r-normal--16-*-*-*";
//	const char* str = "hello world ! 你好啊垃圾!";
//	
//	char **missingList = {
//		"中文",
//	   	"日本語文字列を表示する." };
//    int missingCount = 1;
//    char *defString;
//    XFontSet fontSet =
//        XCreateFontSet(d, fontName,
//                       &missingList, &missingCount, &defString);
//    if (fontSet == NULL) {
//		printf("Failed to create fontset\n");
//		return -1;
//    }
//	const char* string = "呵呵哈哈哈或";
//	int x = 100, y = 300;
//	while(1) {
//		XNextEvent(d, &e);
//		if(e.type == Expose) {
//			XmbDrawString(d, w, fontSet, DefaultGC(d, s), x, y, string, strlen(string));
//			printf("draw str\n");
//		}
//		if(e.type == KeyPress) break;
//	}
//	XCloseDisplay(d);
//	return 0;
//}



#include <X11/Xlib.h>
#include <string.h>

int main(void)
{
    Display *d = XOpenDisplay(0);
    Window r = DefaultRootWindow(d);
    Window w = XCreateSimpleWindow(d, r, 0, 0, 256, 256, 0, 0, 0xffffff);
    GC gc = DefaultGC(d, 0);

    XMapRaised(d, w);
    XSelectInput(d, w, ExposureMask);

    Font font = XLoadFont(d, "9x15-cyrillic");
    XSetFont(d, gc, font);

    const char *msg = "中文可以吗"; // cyrillic symbols

    while (1)
    {
        XEvent e;
        XNextEvent(d, &e);
        XDrawString(d, w, gc, 16, 16, msg, (int) strlen(msg));
    }
	return 0;
}
