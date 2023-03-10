#include "pci.h"
#include "pciLookup.h"

namespace PCI
{
    uint32_t devicePrintCursorY = 1;
    void EnumerateFunction(uint64_t deviceAddress, uint64_t function)
    {
        uint64_t offset = function << 12;

        uint64_t functionAddress = deviceAddress + offset;

        PCIDeviceHeader *pciDeviceHeader = (PCIDeviceHeader *)functionAddress;

        if (pciDeviceHeader->DeviceID == 0)
            return;
        if (pciDeviceHeader->DeviceID == 0xFFFF)
            return;

        uint32_t devicePrintCursorX = 0;
        devicePrintCursorX = graphics->print(0, PCILookup::GetVendorName(pciDeviceHeader->VendorID), 0, devicePrintCursorY * 20) + 8;
        graphics->putChar(0, '/', devicePrintCursorX, devicePrintCursorY * 20);
        devicePrintCursorX = graphics->print(0, PCILookup::GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID), devicePrintCursorX + 16, devicePrintCursorY * 20) + 8;
        graphics->putChar(0, '/', devicePrintCursorX, devicePrintCursorY * 20);
        devicePrintCursorX = graphics->print(0, PCILookup::GetSubclassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass), devicePrintCursorX + 16, devicePrintCursorY * 20) + 8;
        graphics->putChar(0, '/', devicePrintCursorX, devicePrintCursorY * 20);
        devicePrintCursorX = graphics->print(0, PCILookup::GetProgIFName(pciDeviceHeader->Class, pciDeviceHeader->Subclass, pciDeviceHeader->ProgIF), devicePrintCursorX + 16, devicePrintCursorY * 20) + 8;
        devicePrintCursorY++;
    }

    void EnumerateDevice(uint64_t busAddress, uint64_t device)
    {
        uint64_t offset = device << 15;

        uint64_t deviceAddress = busAddress + offset;

        PCIDeviceHeader *pciDeviceHeader = (PCIDeviceHeader *)deviceAddress;

        if (pciDeviceHeader->DeviceID == 0)
            return;
        if (pciDeviceHeader->DeviceID == 0xFFFF)
            return;

        for (uint64_t function = 0; function < 8; function++)
        {
            EnumerateFunction(deviceAddress, function);
        }
    }

    void EnumerateBus(uint64_t baseAddress, uint64_t bus)
    {
        uint64_t offset = bus << 20;

        uint64_t busAddress = baseAddress + offset;
        // g_PageTableManager.MapMemory((void*)busAddress, (void*)busAddress);

        PCIDeviceHeader *pciDeviceHeader = (PCIDeviceHeader *)busAddress;

        if (pciDeviceHeader->DeviceID == 0)
            return;
        if (pciDeviceHeader->DeviceID == 0xFFFF)
            return;

        for (uint64_t device = 0; device < 32; device++)
        {
            EnumerateDevice(busAddress, device);
        }
    }

    void EnumeratePCI(ACPI::MCFGHeader *mcfg)
    {
        int entries = ((mcfg->Header.Length) - sizeof(ACPI::MCFGHeader)) / sizeof(ACPI::DeviceConfig);
        for (int t = 0; t < entries; t++)
        {
            ACPI::DeviceConfig *newDeviceConfig = (ACPI::DeviceConfig *)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(ACPI::DeviceConfig) * t));
            for (uint64_t bus = newDeviceConfig->StartBus; bus < newDeviceConfig->EndBus; bus++)
            {
                EnumerateBus(newDeviceConfig->BaseAddress, bus);
            }
        }
    }

}