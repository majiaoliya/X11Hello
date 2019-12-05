// g++ XftTest.cc -lX11 -lXft `pkg-config --cflags freetype2`
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include <string.h>
#include<X11/Xft/Xft.h>
#include <X11/Xlocale.h>
int main()
{
  Display *display;
  XftFont      *font;
  XftDraw      *xftdraw;
  XRenderColor xrcolor;
  XftColor     xftcolor;

  display = XOpenDisplay(0);
  Window XP = XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,360,90,0,0,0);
  XMapWindow(display,XP);

  font = NULL; /* added 6/16 */

  //font = XftFontOpenName(display,0,"NorthKorea-50"); // how to check if this is good ?
  setlocale(LC_ALL, ""); 
  font = XftFontOpenName(display,0,"-*-*-*-*-*-*-16-*-*-*-*-*-*-*"); /* added 6/16 */
  if (!font) return 1;

  xftdraw = XftDrawCreate(display,XP,DefaultVisual(display,0),DefaultColormap(display,0));

  xrcolor.red  =65535;
  xrcolor.green=0;
  xrcolor.blue =0;
  xrcolor.alpha=65535;
  XftColorAllocValue(display,DefaultVisual(display,0),DefaultColormap(display,0),&xrcolor,&xftcolor);
  char* str = "中文哈aaa";
  XftDrawString8(xftdraw, &xftcolor, font, 20,70 , (XftChar8 *)str, strlen(str));

  XFlush(display);

  sleep(2);

  XftDrawDestroy(xftdraw);
  XftColorFree(display,DefaultVisual(display,0),DefaultColormap(display,0),&xftcolor);

  return 0;
}
