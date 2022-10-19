cd ./ada
gcc -c ../../c/src/lib.c && gnatmake c_wrapper.adb -largs lib.o && rm *.ali
./c_wrapper
rm *.o c_wrapper
cd ../..
