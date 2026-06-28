#ifndef udDescriptors_h
#define udDescriptors_h

#include <avr/pgmspace.h>
#include <stdint.h>
#include "global.h"

#define HID_REPORT_INPUT 0x01
#define HID_REPORT_EFFECT_REPORT 0x02
#define HID_REPORT_CONSTANT_FORCE 0x03
#define HID_REPORT_DEVICE_CONTROL 0x04
#define HID_REPORT_EFFECT_OPERATION 0x05
#define HID_REPORT_PARAM_BLOCK_POOLS 0x06

static const uint8_t udDeviceDescriptor[] PROGMEM = {
   18, // bLength
    1, // bDescriptorType
    0x00,
    0x02, // bcdUSB (2.0)
    0, // bDeviceClass (defined in interface [in cfg. descriptor])
    0, // bDeviceSubclass (above is 0)
    0, 
    UD_EP0_SIZE, // 64
    (0x1209 & 255),
    ((0x1209 >> 8) & 255), // idVendor, https://pid.codes
    (0x0001 & 255),
    ((0x0001 >> 8) & 255), // idProduct https://pid.codes
    0x00,
    0x01, // bcdDevice release number
    0,
    1, // TODO: this. 1, // (iProduct at index 1)
    0,
    1
};

static const uint8_t udHIDReportDescriptor[] PROGMEM = {
    // Input 
    0x05, 0x02, //      Usage Page: Simulation Controls
    0x09, 0x02, //      Usage: Automobile Simulation Device
    0xA1, 0x01, //      Collection: Application
    0x85, 0x01, //          Report ID: (1)
    
    0x05, 0x02, //          Usage Page: Simulation Controls
    0x09, 0xC8, //          Usage: Steering
    0x16, 0x01, 0x80, //    Logical Minimum: (-32767)
    0x26, 0xFF, 0x7F, //    Logical Maximum: (32767)
    0x75, 0x10, //          Report Size: (16)b
    0x95, 0x01, //          Report Count: (1)
    0x81, 0x02, //          Input Report (Data,Var,Abs)
    /*
    0x09, 0x21, //                  Usage: Set Effect Report
    // PID Output   
    // Driver managed
    // NOTE: Each new Collection (bold usages) should have its own report ID.
    //       Regular usages dont need their own report ID, as they are part of 
    //       the group.
    //       (Bold, C) Usage -> CL -> Report ID
    /
    field name
    bits
    range
    units
    whether firmware honors it or ignores it
    */
    //
    0x05, 0x0F, //          Usage Page: Phyisical Interface Device
    0x09, 0x21, //          Usage: Set Effect Report
    0xA1, 0x02, //          Collection: Logical
    0x85, 0x02, //              Report ID: (2)
    
    0x09, 0x22, //              Usage: Effect Block Index
    0x15, 0x01, //              Logical Minimum: (1)
    0x25, 0x01, //              Logical Maximum: (1)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output(Data,Var,Abs)
    
    0x09, 0x25, //              Usage: Effect Type
    0xA1, 0x02, //              Collection: Logical
    0x09, 0x26, //                  Usage: ET Constant-Force
    0x15, 0x01, //                  Logical Minimum: (1)
    0x25, 0x01, //                  Logical Maximum: (1)
    0x75, 0x08, //                  Report Size: (8)
    0x95, 0x01, //                  Report Count: (1)
    0x91, 0x00, //                  Output: (Data,Arr,Abs)
    0xC0, //                    End Collection: Logical
    
    0x09, 0x50, //              Usage: Duration
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x66, 0x03, 0x10, //        Units: (Eng-Lin,Sec)
    0x55, 0x0D, //              Uint Exponent: (-3)
    0x91, 0x02, //              Output: (Data,Var,Abs)
    0x66, 0x00, 0x00, //        Uints: (None)
    0x55, 0x00, //              Uint Exponent: (0)

    0x09, 0x51, //              Usage: Sample Period
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x66, 0x03, 0x10, //        Units: (Eng-Lin,Sec)
    0x55, 0x0D, //              Uint Exponent: (-3)
    0x91, 0x02, //              Output: (Data,Var,Abs)
    0x66, 0x00, 0x00, //        Uints: (None)
    0x55, 0x00, //              Uint Exponent: (0)
    
    0x09, 0x52, //              Usage: Gain
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x7F, //              Logical Maximum: (127)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output (Data,Var,Abs)
    
    0x09, 0x53, //              Usage: Trigger Button
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x00, //              Logical Maximum: (0)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output (Data,Var,Abs)
    
    0x09, 0x54, //              Usage: Trigger Repeat Interval
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x66, 0x03, 0x10, //        Units: (Eng-Lin,Sec)
    0x55, 0x0D, //              Uint Exponent: (-3)
    0x91, 0x02, //              Output: (Data,Var,Abs)
    0x66, 0x00, 0x00, //        Uints: (None)
    0x55, 0x00, //              Uint Exponent: (0)
    
    0x09, 0x55, //              Usage: Axes Enable
    0xA1, 0x02, //              Collection: Logical
    0x05, 0x01, //                  Usage Page: Generic Desktop
    0x09, 0x01, //                  Usage: Pointer
    0xA1, 0x00, //                  Collection: Physical
    0x09, 0x35, //                      Usage: Rz
    0x15, 0x00, //                      Logical Minimum: (0)
    0x25, 0x01, //                      Logical Maximum: (1)
    0x75, 0x08, //                      Report Size: (8)
    0x95, 0x01, //                      Report Count: (1)
    0x91, 0x02, //                      Output (Data,Var,Abs)
    0xC0, //                        End Collection: Physical
    0xC0, //                    End Collection: Logical (Axes Enable)
    
    0x05, 0x0F, //              Usage Page: Phyisical Interface Device
    0x09, 0x56, //              Usage: Direction Enable
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x01, //              Logical Maximum: (1)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output (Data,Var,Abs)
    
    0x09, 0x57, //              Usage: Direction 
    0xA1, 0x02, //              Collection: Logical
    0x05, 0x01, //                  Usage Page: Generic Desktop
    0x09, 0x01, //                  Usage: Pointer
    0xA1, 0x00, //                  Collection: Physical
    0x09, 0x35, //                      Usage: Rz
    0x15, 0x00, //                      Logical Minimum: (0)
    0x26, 0xFF, 0x00, //                Logical Maximum: (255)
    0x75, 0x08, //                      Report Size: (8)
    0x95, 0x01, //                      Report Count: (1)
    0x91, 0x02, //                      Output (Data,Var,Abs)
    0xC0, //                        End Collection: Physical
    0xC0, //                    End Collection: Logical (Direction)
    
    0x05, 0x0F, //              Usage Page: Phyisical Interface Device
    0x09, 0xA7, //              Usage: Start Delay
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x66, 0x03, 0x10, //        Units: (Eng-Lin,Sec)
    0x55, 0x0D, //              Uint Exponent: (-3)
    0x91, 0x02, //              Output: (Data,Var,Abs)
    0x66, 0x00, 0x00, //        Uints: (None)
    0x55, 0x00, //              Uint Exponent: (0)

    0x09, 0x58, //              Usage: Type Specific Block Offset
    0xA1, 0x02, //              Collection: (Logical)
    0x0B, 0x01, 0x00, 0x0A, 0x00,// Usage: Ordinal Instance 1
    0x15, 0x00, //                  Logical Minimum: (0)
    0x26, 0xFF, 0x7F, //            Logical Maximum: (32767)
    0x75, 0x10, //                  Report Size: (16)
    0x95, 0x01, //                  Report Count: (1)
    0x91, 0x02, //                  Output: (Data,Var,Abs)
    0xC0, //                    End Collection: Logical (Type Specific Block Offset)
    0xC0, //                End Collection: Logical (Set Effect Report)
    
    0x09, 0x73, //          Usage: Set Constant-Force Report
    0xA1, 0x02, //          Collection: Logical
    0x85, 0x03, //              Report ID: (3)
    
    0x09, 0x23, //              Usage: Effect Parameter Block Offset
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x7F, //         Logical Maximum: (32767)
    0x75, 0x10, //              Report Size: (16)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output (Data,Var,Abs)
    
    0x09, 0x70, //              Usage: Magnitude
    0x16, 0xF0, 0xD8, //        Logical Minimum: (-10000)
    0x26, 0x10, 0x27, //        Logical Maximum: (10000)
    0x75, 0x10, //              Report Size: (16)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output (Data,Var,Abs)
    0xC0, //                End Collection: Logical (Set Constant-Force Report)

    0x09, 0x95, //          Usage: PID Device Control Report
    0xA1, 0x02, //          Collection: Logical
    0x85, 0x04, //              Report ID: (4)

    0x09, 0x96, //              Usage: PID Device Control
    0xA1, 0x02, //              Collection: Logical
    0x09, 0x97, //                  Usage: DC Enable Actuators
    0x09, 0x98, //                  Usage: DC Disable Actuators
    0x09, 0x99, //                  Usage: DC Stop All Effects
    0x09, 0x9A, //                  Usage: DC Reset
    0x09, 0x9B, //                  Usage: DC Pause
    0x09, 0x9C, //                  Usage: DC Continue
    0x15, 0x01, //                  Logical Minimum: (1)
    0x25, 0x06, //                  Logical Maximum: (6)
    0x75, 0x08, //                  Report Size: (8)
    0x95, 0x01, //                  Report Count: (1)
    0x91, 0x00, //                  Output: (Data,Arr,Abs)
    0xC0, //                    End Collection: Logical (PID Device Control)
    0xC0, //                End Collection: Logical (PID Device Control Report)

    0x09, 0x77, //          Usage: Effect Operation Report
    0xA1, 0x02, //          Collection: Logical
    0x85, 0x05, //              Report ID: (5)

    0x09, 0x22, //              Usage: (Effect Block Index)
    0x15, 0x01, //              Logical Minimum: (1)
    0x25, 0x01, //              Logical Maximum: (1)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output: (Data,Var,Abs)

    0x09, 0x78, //              Usage: Effect Operation
    0xA1, 0x02, //              Collection: Logical
    0x09, 0x79, //                  Usage: OP Effect Start
    0x09, 0x7A, //                  Usage: OP Effect Start Solo
    0x09, 0x7B, //                  Usage: OP Effect Stop
    0x15, 0x01, //                  Logical Minimum: (1)
    0x25, 0x03, //                  Logical Maximum: (3)
    0x75, 0x08, //                  Report Size: (8)
    0x95, 0x01, //                  Report Count: (1)
    0x91, 0x00, //                  Output: (Data,Arr,Abs)
    0xC0, //                    End Collection: Logical (Effect Operation)
    
    0x09, 0x7C, //              Usage: Loop Count
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0x91, 0x02, //              Output: (Data,Var,Abs)
    0xC0, //                End Collection: Logical (Effect Operation Report)
   
    // Features
    0x09, 0x7F, //          Usage: Parameter Block Pools Report
    0xA1, 0x02, //          Collection: Logical
    0x85, 0x06, //              Report ID: (6)

    0x09, 0x80, //              Usage: RAM Pool Size
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x7F, //        Logical Maximum: (32767)
    0x75, 0x10, //              Report Size: (16)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x02, //              Feature: (Data,Var,Abs)

    0x09, 0x81, //              Usage: (ROM Pool Size)
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x00, //              Logical Maximum: (0)
    0x75, 0x10, //              Report Size: (16)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x03, //              Feature: (Const,Var,Abs)

    0x09, 0x82, //              Usage: (ROM Effect Block Count)
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x00, //              Logical Maximum: (0)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x03, //              Feature: (Const,Var,Abs)
        
    0x09, 0x83, //              Usage: Simultaneous Effects Max
    0x15, 0x00, //              Logical Minimum: (0)
    0x26, 0xFF, 0x00, //        Logical Maximum: (255)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x03, //              Feature: (Const,Var,Abs)
    
    0x09, 0xA8, //              Usage: Parameter Block Size
    0xA1, 0x02, //              Collection: Logical
    0x09, 0x21, //                  Usage: Set Effect Report
    0x09, 0x73, //                  Usage: Set Constant-Force Report
    0x15, 0x00, //                  Logical Minimum: (0)
    0x26, 0xFF, 0x00, //            Logical Maximum: (255)
    0x75, 0x08, //                  Report Size: (8)
    0x95, 0x02, //                  Report Count: (2)
    0xB1, 0x02, //                  Feature: (Data,Var,Abs)
    0xC0, //                    End Collection: Logical (Parameter Block Size)
    
    0x09, 0xA9, //              Usage: Device Managed Pool
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x00, //              Logical Maximum: (0)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x03, //              Feature: (Const,Var,Abs)
    
    0x09, 0xAA, //              Usage: Shared Parameter Blocks
    0x15, 0x00, //              Logical Minimum: (0)
    0x25, 0x00, //              Logical Maximum: (0)
    0x75, 0x08, //              Report Size: (8)
    0x95, 0x01, //              Report Count: (1)
    0xB1, 0x03, //              Feature: (Const,Var,Abs)
    0xC0, //                End Collection: Logical (Parameter Block Pools Report)

    0xC0 //             End Collection: Application (Top Level)
};

static const uint8_t udConfigurationDescriptor[] PROGMEM = {
    //configuration descriptor
    
    9, //bLength
    0x02, //const CONFIGURATION
    41, 0x00, //bytes configuration descriptor TOTAL (everything)
    1, // num interfaces
    1, // bConfigurationValue
    0, // iConfiguration
    0b10000000, // bmAttributes
    50, // bMaxPower

    // interface descriptor
    9, // bLength
    0x04, // const INTERFACE
    0x00, // 0th interface
    0x00, // no alternates
    1, // additional endpoints
    0x03, // HID device (yay! [bInterfaceClass]) 
    0x00, // bInterfaceSubClass
    0x00, // bInterfaceProtocol (defined in HID)
    0x00, // iInterface

    // HID descriptor
    9, // bLength
    0x21, // class descriptor type
    0x11, 0x01, // bcdHID release number
    0x00, // country code
    0x01, // num. descriptors
    0x22, // bDescriptorType
    (sizeof(udHIDReportDescriptor) & 0xFF), (sizeof(udHIDReportDescriptor) >> 8),

    // endpoint descriptor (IN)
    7,
    0x05, // bDescriptorType
    0b10000001, // bEndpointAddress (ep 1, in)
    0b00000011, // bmAttributes (int.)
    64, 0, // wMaxPacketSize (in B) (size of bank [ep1 will be 64B])
    1, // once every ms

    // endpoint descriptor (OUT)
    7,
    0x05, // bDescriptorType
    0b00000010, // bEndpointAddress (ep 2, out)
    0b00000011, // bmAttributes (int.)
    64, 0, // wMaxPacketSize (in B) (size of bank [ep2 will be 64B])
    1, // once every ms
};

static const uint8_t udStringLanguageDescriptor[] PROGMEM = {
    4, // bLength
    0x03, // bDescriptorType (string)
    0x09, 0x04, // wLANGID (0x0409 = English US)
};

static const uint8_t udStringDeviceDescriptor[] PROGMEM = {
    42, // bLength
    0x03, // bDescriptorType (string)
    0x54, 0x00, 
    0x73, 0x00,
    0x20, 0x00, 
    0x69, 0x00, 
    0x73, 0x00, 
    0x20, 0x00, 
    0x66, 0x00, 
    0x75, 0x00, 
    0x63, 0x00, 
    0x6B, 0x00, 
    0x65, 0x00, 
    0x64, 0x00, 
    0x20, 0x00, 
    0x66, 0x00, 
    0x72, 0x00, 
    0x20, 0x00, 
    0x4C, 0x00, 
    0x4D, 0x00, 
    0x41, 0x00, 
    0x4F, 0x00
    // TODO: How to change the name of the device. 
    //       This just goes in the "Bus Reported Device Description"
    //       section in device manager.
};

static const uint8_t udPIDPoolReport[] PROGMEM = {
    0x06, //        Report ID: (6)
    0x40, 0x00, //  RAM Pool Size: (64)
    0x00, 0x00, //  ROM Pool Size: (0)
    0x00, //        ROM Effect Block Count: (0)
    0x01, //        Simultaneous Effects Max: (1)
    0x0E, //        Set Effect Report Size: (14 [13 + rID])
    0x05, //        Set Constant Force Report Size: (5 [4 + rID])
    0x00, //        Device Managed Pool: (0)
    0x00 //         Shared Parameter Blocks: (0)
};


#endif // #ifndef udDescriptors.h