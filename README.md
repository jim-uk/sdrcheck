sdcheck

command line utility for checking if RTL-SDR devices are available, and returns vendor/product/serial number and an index which can be used with dump1090/rtl-ais.

For Linux, use normal build tools
You may need to get the Makefile for your paths.  Maks sure you have libusb-dev, librtlsdr-dev


For Windows, build with msys2, with the packages:
pacman -S mingw-w64-x86_64-libusb git make mingw-w64-x86_64-rtl-sdr
then make.

You'll need to copy libusb-1.0.dll, librtlsdl.dll and libwinpthread-1.dll into the same directory as sdrcheck.exe.  If you don't the exe will just apper to do nothing when run. 
