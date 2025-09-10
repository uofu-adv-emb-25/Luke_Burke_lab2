# Manual Test Plan – Blink + Serial Echo

## Setup

1. Attach the Pico to WSL:
   # From Windows PowerShell (Admin) if using Ubunto
   usbipd list
   usbipd attach --wsl --busid 1-2

2. Verify the device in Ubuntu:
   lsusb
   # should show Raspberry Pi Pico in boot mode

3. Build and flash the code:
   rm -rf build
   cmake -S . -B build 
   cmake --build build -j
   find build -name "*.uf2"
   # example: build/src/hello_freertos.uf2
   sudo picotool load build/src/hello_freertos.uf2 -f
   sudo picotool reboot

## Exercise

1. Open a serial monitor on the correct port (e.g. `/dev/ttyACM0`) at **115200 baud**:
   screen /dev/ttyACM0 115200
2. Start listening to the output.  
3. Type lowercase letters (e.g. `a`, `z`, `ahah`) and send them.  
4. Test uppercase letters (e.g. `P`, `GS`) and send them..
5. Test non-letter characters (numbers, symbols).  

## Expected Behavior

- **LED**: onboard LED blinks steadily, controlled by the FreeRTOS blink task.  
- **Serial Echo**:  
  - Lowercase input  -> echoed back as uppercase.  
  - Uppercase input -> echoed back as lowercase.  
  - Non-letters -> echoed back unchanged.  

### Example Session
---- Sent utf8 encoded message: "a" ----
A
---- Sent utf8 encoded message: "z" ----
Z
---- Sent utf8 encoded message: "ahah" ----
AHAH
---- Sent utf8 encoded message: "3" ----
3
---- Sent utf8 encoded message: "!" ----
!
