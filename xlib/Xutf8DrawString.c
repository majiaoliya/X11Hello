/* Cut and paste of UTF8 string. cf. xp1210.c */
/* click the window, then you will see the letter river=kanji-river */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xlocale.h>

Display *d;
Window *w;
GC gc;
XFontStruct *fs;
Bool selected=False;
int len=0;
char txt[] = "中文可以吗";
Atom a;
Atom tgt;
XTextProperty ct;
main() {
  XEvent e;
  char **miss, *def;
  int n;

  /* Set utf8  characters */
  
  len=strlen(txt); 

  setlocale(LC_ALL,"");
  d = XOpenDisplay(NULL);
  /* Chose a relevant font if you do not find kanji letters */
#define DEFAULT_FONT_NAME       "-*-*-*-R-Normal--14-130-75-75-*-*"
  fs = XCreateFontSet(d, DEFAULT_FONT_NAME, &miss, &n, &def);
  w = XCreateSimpleWindow(d,RootWindow(d,0),400,400,400,50,
                          2,BlackPixel(d,0), WhitePixel(d,0));
  XSelectInput(d,w, ButtonPressMask);
  gc = DefaultGC(d,DefaultScreen(d));
  XMapWindow(d,w);

  XSetForeground(d,gc,BlackPixel(d,0));
  a = XInternAtom(d,"COMPOUND_TEXT",False);
  tgt = XInternAtom(d,"TARGETS",False);
  printf("tgt=%d\n",(int) tgt);

  printf("Left click the window, then the letter [river=kanji-river] will be selected.\n");
  printf("Paste in other windows --- kterm or emacs or ..., but it does not work.\n");
  fflush(NULL);
  
  while (1) {
    XNextEvent(d,&e);
    switch(e.type) {
    case ButtonPress:
      if (selected == False) {
        if (e.xbutton.button == Button1) OwnSelection(e);
      }
      break;
    case SelectionClear:
      LoseSelection(e); break;
    case SelectionRequest:
      StoreSelectionData(e); break;
    case SelectionNotify:
      printf("SelectionNofity is not implemented.\n");
      fflush(NULL);
      break;
    }
  }
}

OwnSelection(e)
  XEvent e;
{
  printf("OwnSelection\n"); fflush(NULL);
  XSetSelectionOwner(d,XA_PRIMARY,w,e.xbutton.time);
  XSetWindowBackground(d,w,BlackPixel(d,0));
  XSetForeground(d,gc,WhitePixel(d,0));
  XClearWindow(d,w);
  Xutf8DrawString(d,w,fs,gc,30,30,txt,len);
  selected=True;
  /* XStoreBytes(d,txt,strlen(txt)); */
}

LoseSelection(e)
  XEvent e;
{
  printf("LoseSelection\n"); fflush(NULL);
  if (e.xselectionclear.window == w && e.xselection.selection == XA_PRIMARY) {
    printf("LoseSelection body\n"); fflush(NULL);
    XSetWindowBackground(d,w,WhitePixel(d,0));
    XSetForeground(d,gc,BlackPixel(d,0));
    XClearWindow(d,w);
    Xutf8DrawString(d,w,fs,gc,30,30,txt,len);
    selected = False;
  }
}

StoreSelectionData(e)
  XEvent e;
{
  XSelectionEvent se;
  Atom al[3];
  char *cl[4]; cl[0]= txt; cl[1]=NULL;
  al[0] = tgt;
  al[1] = a;
  al[2] = XA_STRING;
  
  printf("Got a request: selection request (asked to send a data)\n");
  printf("txt=[%s]\n",txt);
  fflush(NULL);
  se.type = SelectionNotify;
  se.requestor = e.xselectionrequest.requestor;
  se.selection = e.xselectionrequest.selection;
  se.target = e.xselectionrequest.target;
  se.time = e.xselectionrequest.time;
  se.property = e.xselectionrequest.property;
  if (e.xselectionrequest.selection == XA_PRIMARY) {
    printf("xselectionrequest.target=%d\n",(int) e.xselectionrequest.target);
    if (e.xselectionrequest.target == tgt) {
      /* I never get this message... Why? */
      printf("Request: target.\n"); fflush(NULL);
      XChangeProperty(d,se.requestor,se.property, XA_ATOM,
					  32,PropModeReplace,al,3);
    }else if (e.xselectionrequest.target == a) {
      /* Implementation of the compound text format enables cut and paste with
         most applications. */
      printf("Request: TextListToTextProperty: compound text.\n"); fflush(NULL);
      Xutf8TextListToTextProperty(d,cl,1,XCompoundTextStyle,&ct);
      XChangeProperty(d,se.requestor, se.property, se.target, 8,
		      PropModeReplace,ct.value,ct.nitems);
    }else if (e.xselectionrequest.target == XA_STRING) {
      printf("Request: TextListToTextProperty: XA_STRING \n"); fflush(NULL);
      /* I'm not sure if it is fine to do as below. */
      Xutf8TextListToTextProperty(d,cl,1,XUTF8StringStyle,&ct);
      XChangeProperty(d,se.requestor, se.property, se.target, 8,
		      PropModeReplace,ct.value,ct.nitems);
    }else{
      printf("Request: Unknown No. : XA_PRIMARY and ?? \n"); fflush(NULL);
      se.property = None; 
    }
  }else{
    printf("Request: Unknown No. \n"); fflush(NULL);
    se.property = None;
  }
  XSendEvent(d, se.requestor,False,NULL,&se);
}





