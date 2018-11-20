# How to compile and run

1. Compile on Linux

2. Make sure to to have Xming running to see the GUI!!

3. Either of the following both work (to run, type "./a.out")

	g++-8.2.0 -std=c++2a -lfltk -lfltk_images -lX11 -ljpeg *.cpp

	g++-8.2.0 -std=c++11 -lfltk -lfltk_images -lX11 -ljpeg *.cpp

   Another option is to type "make" and "make clean" (to run, type "./gui1")

https://serverfault.com/questions/765606/xming-cant-open-display-error/800464
