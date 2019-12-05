#include <assert.h>
#include <locale.h>
#include <stdio.h>

#include <X11/Xlib.h>

int main(int argc, char ** argv)
{
    Display * display;

    setlocale(LC_ALL, "");
    display = XOpenDisplay(0);
	
	

	return 0;
}
