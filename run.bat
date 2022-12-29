clear
echo "Compiling BitOS!"
cd ~/BitOS/kernel
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
