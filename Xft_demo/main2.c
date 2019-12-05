#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

int main()
{
    char font[] = "helvetica:size=11";
    char buf[] = "Lorem Ipsum";
    int s, x = 12;
    XRenderColor color = {0xFFFF, 0, 0, 0xFFFF};
    Display * d;
    Window r;
    Pixmap p;
    XftFont * f;
    XftDraw * drw;
    XftColor xftc;

    d = XOpenDisplay(NULL);
    s = DefaultScreen(d);
    r = RootWindow(d, s);
    if (!(f = XftFontOpenName(d, s, font))) printf("could not open font\n");
    if(!(p = XCreatePixmap(d, r, 1600, 900, DefaultDepth(d, s)))) printf("could not create pixmap\n");

    drw = XftDrawCreateAlpha(d, p, DefaultDepth(d, s));
    XftColorAllocValue(d, DefaultVisual(d, s), DefaultColormap(d, s), &color, &xftc);
    XftDrawStringUtf8(drw, &xftc, f, 100, 100, (XftChar8 *)buf, x);
    XftDrawRect(drw, &xftc, 10, 10, 50, 50);

    XSetWindowBackgroundPixmap(d, r, p);
    XFlush(d);
	XEvent e;
	XMapWindow(d, r);
	while(1) {
		XNextEvent(d, &e);
		
	}
    XCloseDisplay(d);

    return 0;
}
