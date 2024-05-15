#include "mini_uart.h"
#include "shell.h"

void kernel_main(void)
{
	uart_init();
	uart_send_string("Hello World!\r\n");
	shell();
	while (1) {
		uart_send(uart_recv());
	}
}
