#pragma once

#define INT_DISABLE 0
#define INT_ENABLE  0x200
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void outb(short port, char data){
        asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
        return;
}

char inb(short port){
        char res;
        asm volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
        return res;
}

/**************** SEND/RECEIVE WORD ******************/

void outw(short port, short value)
{
        asm volatile ("outw %w0, %1" : : "a" (value), "id" (port) );
}

short inw(short port){
   short ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

/**************** SEND/RECEIVE LONG (32-BIT) ******************/

void outl(short port, int value){
        asm volatile ("outl %%eax, %%dx" :: "d" (port), "a" (value));
}

int inl(short port){
   int ret;
   asm volatile ("inl %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void init_pics(int pic1, int pic2)
{
   /* send ICW1 */
   outb(PIC1, ICW1);
   outb(PIC2, ICW1);

   /* send ICW2 */
   outb(PIC1 + 1, pic1);
   outb(PIC2 + 1, pic2);

   /* send ICW3 */
   outb(PIC1 + 1, 4);
   outb(PIC2 + 1, 2);

   /* send ICW4 */
   outb(PIC1 + 1, ICW4);
   outb(PIC2 + 1, ICW4);

   /* disable all IRQs */
   outb(PIC1 + 1, 0xFF);
}