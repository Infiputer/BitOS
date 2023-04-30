clear
echo "Compiling BitOS!"
python3 bmlc.py code.bml > kernel/src/executables/exampleExe.h
cd kernel
rm -r lib
mkdir lib
make
make buildimg
cd ../gnu-efi/
make
make bootloader
cd ../kernel/
make setup
make buildimg
echo "Done!"
make run