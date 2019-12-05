#include <X11/Xlib.h>
#include <stdio.h>

int main(void) {
	int s = 0;
	Display* d = XOpenDisplay(NULL);
	Window w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 800, 600, 1, 
			111111, WhitePixel(d, 0));
	XEvent e;
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	GC gc = XCreateGC(d, w, 0L, (XGCValues*)NULL);
	const char* str = "this is text";
	while(1) {
		XNextEvent(d, &e);
		if(e.type == Expose) {
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 300, 150);
			XDrawString(d, w, gc, 400, 500, str, strlen(str));
		} else if(e.type == KeyPress) {
			break;
		}
	}

	XCloseDisplay(d);

	return 0;
}
