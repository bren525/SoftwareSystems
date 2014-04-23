build: HelloGlib frequencyCounter

HelloGlib:
	gcc -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -o hello.out HelloGlib.c -lglib-2.0

frequencyCounter:
	gcc -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include frequencyCounter.c -lglib-2.0

#gcc `pkg-config --cflags --libs glib-2.0` HelloGlib.c
#gcc -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0 HelloGlib.c