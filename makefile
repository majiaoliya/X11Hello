all: main1 main4 main5 main6 main7
main1: main.c
	gcc -o main1 main.c -lX11
main4: main4.c
	gcc -o main4 main4.c -lX11
main5: main5_utf8.c
	gcc -o main5 main5_utf8.c -lX11
main6: main6.c
	gcc -o main6 main6.c -lX11
main7: main7.c
	gcc -o main7 main7.c -lX11
clean:
	rm main1 main4 main5 main6 main7
