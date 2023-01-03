clear
echo "Compiling BitOS!"
cd ~/BitOS/kernel
rm -r lib
mkdir lib
make
make buildimg
cd ~/BitOS/gnu-efi/
make
make bootloader
cd ~/BitOS/kernel/
make setup
make buildimg
echo "Done!"
make run
