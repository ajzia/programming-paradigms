cd ./c
gnatmake ../../ada/lib.adb && gcc -c ada_wrapper.c && gnatbind -n lib.ali && gnatlink lib.ali ada_wrapper.o
./lib
rm *.o *.ali 
rm lib
cd ../..
