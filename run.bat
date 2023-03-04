clear
echo "Compiling BitOS!"
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