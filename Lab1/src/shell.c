#include "mini_uart.h"
#include "util.h"
#include "peripherals/mailbox.h"
#include <stddef.h>
#define BUFFER_SIZE 256u



void help(){
    uart_send_string("help     :");
    uart_send_string("print this help menu\r\n");
    uart_send_string("hello    :");
    uart_send_string("print Hello World!\r\n");
    uart_send_string("reboot   :");
    uart_send_string("reboot the device\r\n");
    uart_send_string("info     :");
    uart_send_string("the mailbox hardware info\r\n");
}
void hello(){
    uart_send_string("Hello Wolrld!!\r\n");
}
void info(){
    get_board_revision();
    get_memory_base_address();
}
void reboot(){
    uart_send_string("Rebooting...\r\n");
    reset(500);
}
void read_command(char* buffer){
    size_t index = 0;
    
    while(1){
    buffer[index]= uart_recv();
    uart_send(buffer[index]);
    if(buffer[index]=='\n')
    	break;
    index++;
    }   
    buffer[index + 1] = '\0';
}
void deal_command(char* buffer){
    newline2end(buffer);
    uart_send('\r');
    if(buffer[0]=='\0')
    	return;
    else if(compare_char(buffer, "help"))
    	help();
    else if(compare_char(buffer, "hello"))
    	hello();
    else if(compare_char(buffer, "info"))
    	info();
    else if(compare_char(buffer, "reboot"))
    	reboot();
    else{
    	uart_send_string("commnad '");
        uart_send_string(buffer);
        uart_send_string("' not found\r\n");
    }
}

void shell(){
    while(1){
    	char buffer[BUFFER_SIZE];
    	uart_send_string("$: ");
    	read_command(buffer);
    	uart_send_string(buffer);
    	deal_command(buffer);
    }
}
