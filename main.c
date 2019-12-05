
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define nullptr 0
void draw(Display *display, Window win, GC gc, XFontStruct *fs, XFontStruct *fs16) {
    char *str = "Hello World!";
    char *str1 = "你好，大家??！";
//参考线
    XDrawLine(display, win, gc, 20, 100, 300, 100);
//画字符串
    XSetFont(display, gc, fs->fid);
    XDrawString(display, win, gc, 20, 100, str1, strlen(str1));
//计算宽度
    printf("str1 width:%d\n", XTextWidth(fs, str1, strlen(str1)));
//画中文字符串
    XSetFont(display, gc, fs16->fid);
//计算宽度
}

int main(int argc, char **argv) {
    int i;
    Display *display;
    Window win; //窗口ID
    unsigned int width, height; //窗口尺寸
    unsigned int border_width = 4; //边界空白
    unsigned int display_width, display_height;//屏幕尺寸
    int count;
    XEvent report;
    GC gc;
    unsigned long valuemask = 0;
    XGCValues values;
    char *display_name = nullptr;
    char **fonts;
    int font_count;
    XFontStruct *fs, *fs16;
// 和X 服务器连接
    if ((display = XOpenDisplay(display_name)) == NULL) {
        printf("Cannot connect to X server %s\n",
               XDisplayName(display_name));
        exit(-1);
    }
    printf("连接到X Server\n");
//获得缺省的 screen_num
    auto screen_num = DefaultScreen(display);
    printf("Screen Num: %d\n", screen_num);
//获得屏幕的宽度和高度
    display_width = DisplayWidth(display, screen_num);
    display_height = DisplayHeight(display, screen_num);
//指定所建立窗口?宽度和高度
//width = display_width/2;
//height = display_height/2;
    width = 600;
    height = 400;
//列出所有GB2312
    printf("All gb2312 fonts on this server:\n");
    fonts = XListFonts(display, "*gb2312*", 10000, &font_count);
    for (i = 0; i < font_count; i++)
        printf("%s\n", fonts[i]);
    XFreeFontNames(fonts);
//载入8x16字体
    if ((fs = XLoadQueryFont(display, "9x15")) == NULL) {
        printf("Cannot load font 9x15\n");
        exit(1);
    }
//载入中文16点阵字体
    if ((fs16 = XLoadQueryFont(display, "hanzigb16st")) == NULL) {
        printf("Cannot load Chinese font\n");
        exit(1);
    }
//建立窗口
    win = XCreateSimpleWindow(
            display, //display
            RootWindow(display, screen_num), //父窗口
            0, 0, width, height, //位置和大小
            border_width, //边界宽度
            BlackPixel(display, screen_num), //前景色
            WhitePixel(display, screen_num));//背景色
//选择窗口感兴趣的事件掩码
    XSelectInput(display, win,
                 ExposureMask | KeyPressMask |
                 ButtonPressMask | StructureNotifyMask);
//建立GC
    gc = XCreateGC(display, win, valuemask, &values);
//显示窗口
    XMapWindow(display, win);
//进入事件循环
    printf("进入事件循环\n");
    while (true) {
//取得队列中的事件
        XNextEvent(display, &report);
        switch (report.type) {
//曝光事件, 窗口应重绘
            case Expose:
                printf("Expose\n");
//取得最后一个曝光事件
                if (report.xexpose.count != 0) break;
                draw(display, win, gc, fs, fs16);
                break;
//窗口尺寸改变, 重新取得窗口的宽度和高度
            case ConfigureNotify:
                printf("ConfigureNotify\n");
                width = report.xconfigure.width;
                height = report.xconfigure.height;
                break;
//鼠标点击或有按键, 释放资源?退出
            case ButtonPress:
                printf("ButtonPress\n");
                XFreeGC(display, gc);
                XCloseDisplay(display);
                exit(1);
            case KeyPress:
                printf("KeyPress\n");
                printf("report: %c\n", report.xkey.keycode);
                break;
            default:
                printf("default\n");
                break;
        }
    }
}







//#include <X11/Xlib.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
// 
//int main(void) {
//   Display *d;
//   Window w;
//   XEvent e;
//   char *msg = "Hello, World!中文";
//   int s;
// 
//   d = XOpenDisplay(NULL);
//   if (d == NULL) {
//      fprintf(stderr, "Cannot open display\n");
//      exit(1);
//   }
// 
//   s = DefaultScreen(d);
//   w = XCreateSimpleWindow(d, RootWindow(d, s), 100, 100, 500,500, 1,
//                           777215, 111111);
//               printf("BlackPixel(d, s) is %d\n",(int)BlackPixel(d, s));
//               printf("WhitePixel(d, s) is %d\n",(int)WhitePixel(d, s));
//   XSelectInput(d, w, ExposureMask | KeyPressMask);
//   XMapWindow(d, w);
// 
//   while (1) {
//      XNextEvent(d, &e);
//	  if (e.type == Expose) {
//         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
//         XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
//      }
//      if (e.type == KeyPress)
//         break;
//   }
// 
//   XCloseDisplay(d);
//   return 0;
//}
//
//


//#include <stdio.h>
//#include <X11/Xlib.h>
//
//char *key_name[] = {
//    "left",
//    "second (or middle)",
//    "right",
//    "pull_up",
//    "pull_down"
//};
//
//int main(int argc, char **argv)
//{
//    Display *display;
//    XEvent xevent;
//    Window window;
//
//    if( (display = XOpenDisplay(NULL)) == NULL )
//        return -1;
//
//
//    window = DefaultRootWindow(display);
//    XAllowEvents(display, AsyncBoth, CurrentTime);
//
//    XGrabPointer(display,
//                 window,
//                 1,
//                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask ,
//                 GrabModeAsync,
//                 GrabModeAsync,
//                 None,
//                 None,
//                 CurrentTime);
//
//    while(1) {
//        XNextEvent(display, &xevent);
//
//        switch (xevent.type) {
//            case MotionNotify:
//                printf("Mouse move      : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
//                break;
//            case ButtonPress:
//                printf("Button pressed  : %s\n", key_name[xevent.xbutton.button - 1]);
//                break;
//            case ButtonRelease:
//                printf("Button released : %s\n", key_name[xevent.xbutton.button - 1]);
//                break;
//        }
//    }
//
//    return 0;
//}


//
//#include <stdio.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
///*
//#include <locale.h>
//*/
//#include <X11/Xlocale.h>
//#include <stdlib.h>
//
//void DrawCenteredMbString(Display *, Window, XFontSet, GC, char *, int, int, int, int, int);
//
//int main(int argc, char *argv[]) {
//    Display *dpy;
//    Window w;
//    XFontSet fontset;
//    char **missing_charsets;
//    int num_missing_charsets;
//    char *default_string;
//    int i;
//    GC gc;
//    XEvent xe;
//
//    if (setlocale(LC_ALL, "") == NULL) {
//        printf("cannot set locale \n");
//        exit(1);
//    }
//
//    if (!XSupportsLocale()) {
//        printf("X does not support locale %s\n",setlocale(LC_ALL, NULL));
//        exit(1);
//    }
//
//    if (XSetLocaleModifiers("") == NULL) {
//        printf("Warning: cannot set locale modifiers\n");
//    }
//
//    dpy = XOpenDisplay(NULL);
//    w = XCreateSimpleWindow(
//            dpy, RootWindow(dpy, 0), 50, 50,
//                            300, 200, 5, BlackPixel(dpy, 0),
//                            WhitePixel(dpy, 0));
//    gc = XCreateGC(dpy, w, 0L, (XGCValues *) NULL);
//
//    fontset = XCreateFontSet(
//            dpy, "-*-*-*-*-*-*-16-*-*-*-*-*-*-*",
//                             &missing_charsets, &num_missing_charsets,
//                             &default_string);
//    if (num_missing_charsets > 0) {
//        printf("The following charsets are missing\n");
//        for (i = 0; i < num_missing_charsets; i++) {
//            printf("%s \n", missing_charsets);
//            printf("The string is %s \n", default_string);
//            printf("of any characters from those sets\n");
//        }
//        XFreeStringList(missing_charsets);
//    }
//    XSetLineAttributes(dpy, gc, 5, LineSolid, CapRound, JoinRound);
//    XSelectInput(
//            dpy, w, ExposureMask | ButtonPressMask
//                         | EnterWindowMask | LeaveWindowMask);
//    XMapWindow(dpy, w);
//    XFlush(dpy);
//    while (1) {
//        XNextEvent(dpy, &xe);
//        switch (xe.type) {
//            case Expose:
//                printf("Expose 出现\n");
//                XSetForeground(dpy, gc, BlackPixel(dpy, 0));
//                DrawCenteredMbString(
//                        dpy, w, fontset, gc,
//                                     "你好 Hello",
//                                     10, 0, 0, 100, 50);
//                break;
//            case ButtonPress:
//                printf("按下\n");
////                exit(1);
//                break;
//            case EnterNotify:
//                printf("进入\n");
//                XSetForeground(dpy, gc, BlackPixel(dpy, 0));
//                XDrawRectangle(dpy, w, gc, 0, 0, 100, 50);
//                break;
//            case LeaveNotify:
//                printf("离开\n");
//                XSetForeground(dpy, gc, WhitePixel(dpy, 0));
//                XDrawRectangle(dpy, w, gc, 0, 0, 100, 50);
//                break;
//            default:
//                printf("默认\n");
//                break;
//        }
//    }
//    return 0;
//}
//
//void
//DrawCenteredMbString(Display *dpy, Window w, XFontSet fontset, GC gc, char *str, int num_bytes, int x, int y, int width,
//                     int height) {
//    XRectangle boundingbox;
//    XRectangle dummy;
//    int originx, originy;
//
//    (void) XmbTextExtents(fontset, str, num_bytes, &dummy, &boundingbox);
//
//    originx = x + (width - boundingbox.width) / 2 - boundingbox.x;
//    originy = y + (height - boundingbox.height) / 2 - boundingbox.y;
//
//    XmbDrawString(dpy, w, fontset, gc, originx, originy, str, num_bytes);
//}
//
//
