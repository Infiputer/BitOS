#pragma once

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

struct interrupt_frame;
/**
 * Page Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a page fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame *frame);
/**
 * Double Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a Double fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame *frame);
/**
 * General Protectio Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a General Protection fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame *frame);
/**
 * Interrupt handler for PS/2 Keyboard event
 *
 * @param frame Pointer to the interrupt frame
 */
__attribute__((interrupt)) void KeyboardInt_Handler(struct interrupt_frame *frame);
/**
 * Interrupt handler for PS/2 Mouse event
 *
 * @param frame Pointer to the interrupt frame
 */
__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame *frame);

void RemapPIC();
/**
 * Sends End-of-Interrupt signal to Master PIC
 */
void PIC_EndMaster();
/**
 * Sends End-of-Interrupt signal to both Master and Slave PIC
 */
void PIC_EndSlave();