### P2 Solution

a. MTCP_BIOC_ON
    MTCP_BIOC_ON is sent whenever an input is generated. The MTCP_BIOC_ON will enable Button interrupt-on_change. This will return MTCP_ACK.  
   MTCP_LED_SET
    MTCP_LED_SET sets the User-set LED display values. The first byte of the argument will show which of the LED's to set and also determine the number of bytes that will follow. Tux controller will update the LEDs and return MTCP_ACK.

b. MTCP_ACK:
    The device sends it when a command is sent from the computer to the controller. This response means that the command has been successfully completed.
   MTCP_BIOC_EVT:
    The device sends it when a computer uses opcode to enable interrupt-on-change mode or when we press or release a button. This respond
    means interrupt-on-change mode is on or the status of a button is changed.
   MTCP_RESET:
    The device sends it when the computer sends an MTCP_RESET_DEV to the device, a reset button is pressed, or when the device gets initialized
    after powering up. This response means the status of the device has been reset.

c. If tuxctl_handle_packet waits too long, the interrupt that calls tuxctl_Idisc_data_callback which calls tuxctl_handle_packet will also be waiting.
