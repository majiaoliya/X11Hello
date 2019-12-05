#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xlocale.h>
#include <stdio.h>
#define NULL (0)

void DrowCenteredMbString(dpy, w, fontset, gc, str, num_bytes, x, y, width, height)
	Display* dpy;
	Window w;
	XFontSet fontset;
	GC gc;
	char* str;
	int num_bytes;
	int x, y, width, height;
{
	XRectangle boundingbox;
	XRectangle dummy;
	int originx, originy;
	(void) XmbTextExtents(fontset, str, num_bytes, &dummy, &boundingbox);
	originx = x+(width - boundingbox.width) / 2 - boundingbox.x;
	originy = y+(height - boundingbox.height) / 2 - boundingbox.y;
	XmbDrawString(dpy, w, fontset, gc, originx, originy, str, num_bytes);
}

int main(void) {
	Display* dpy;
	Window w;
	XFontSet fontset;
	char** missing_charsets;
	int num_missing_charsets;
	char* default_string;
	int i, loc;
	GC gc;
	XEvent xe;
	dpy = XOpenDisplay(NULL);
	
	char* program_name = "majiao_x11";
	if( (loc=setlocale(LC_ALL, "")) == NULL) {
		printf("%s: LC_ALL什么也没有\n", program_name);
		return -1;
	} else {
		printf("%d\n", loc);
	}
	w = XCreateSimpleWindow(dpy, RootWindow(dpy, 0), 50, 50, 800, 600, 30,
			BlackPixel(dpy, 0), WhitePixel(dpy, 0));
	gc = XCreateGC(dpy, w, 0L, (XGCValues*) NULL);
	char* ch = "-*-*-*-*-*-*-16-*-*-*-*-*-*-*"; //中文
	const char* test = "-Misc-Fixed-Medium-R-Normal--20-200-75-75-C-100-UTF-8";
//	ch = "-*-*-*-R-Normal--*-180-100-100-*-*";
	fontset = XCreateFontSet(dpy, ch,
			&missing_charsets, &num_missing_charsets,
			&default_string);
//	XSetLineAttributes(dpy, gc, 5, LineSolid, CapRound, JoinRound);
	XSetLineAttributes(dpy, gc, 100, LineSolid, CapRound, JoinRound);
	XSelectInput(dpy, w, ExposureMask | ButtonPressMask | EnterWindowMask | LeaveWindowMask);
	XMapWindow(dpy, w);
	XFlush(dpy);
	while(1) {
		XNextEvent(dpy, &xe);
		switch(xe.type) {
			case Expose:
				printf("出现\n");
//				XSetForeground(dpy, gc, BlackPixel(dpy, 0));
				XSetForeground(dpy, gc, 111111);
				const char* text = "你好啊hello 我是垃圾 こんにちは\\n\\n\\n哈哈哈";
				DrowCenteredMbString(dpy, w, fontset, gc, text,
						strlen(text), 100, 100, 800, 600);
				break;
		}
	}
	XCloseDisplay(dpy);
	return 0;
}
