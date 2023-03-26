#include "pci.h"
#include "pciLookup.h"
#include "../logger/logger.h"
#include "../BitOSUtilities.h"

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

        char deviceString[2000];
        uint32_t deviceIndex = 0;
        strcpy(deviceString, PCILookup::GetVendorName(pciDeviceHeader->VendorID));
        deviceIndex += strlen(PCILookup::GetVendorName(pciDeviceHeader->VendorID));
        deviceString[deviceIndex++] = '/';

        strcpy((char*)((uint64_t)deviceString+deviceIndex), PCILookup::GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID));
        deviceIndex += strlen(PCILookup::GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID));
        deviceString[deviceIndex++] = '/';

        strcpy((char*)((uint64_t)deviceString+deviceIndex), PCILookup::GetSubclassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass));
        deviceIndex += strlen(PCILookup::GetSubclassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass));
        deviceString[deviceIndex++] = '/';

        strcpy((char*)((uint64_t)deviceString+deviceIndex), PCILookup::GetProgIFName(pciDeviceHeader->Class, pciDeviceHeader->Subclass, pciDeviceHeader->ProgIF));
        
        log(deviceString);
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