#include "shell.h"
#include "vga.h"
#include "util.h"
#include "stdio.h"

typedef enum {
    CMD_UNKNOWN,
    CMD_ECHO,
    CMD_CLEAR,
    CMD_HELP
} command_t;

command_t parse_cmd(const char* cmd_buffer)
{
    if (strcmp(cmd_buffer, "echo") == 0) return CMD_ECHO;
    if (strcmp(cmd_buffer, "clear") == 0) return CMD_CLEAR;
    if (strcmp(cmd_buffer, "help") == 0) return CMD_HELP;
    return CMD_UNKNOWN;
}

void echo(const char* input_buffer, unsigned int idx)
{
    print("\n");
    print(&input_buffer[idx]);
}

void print_help_menu()
{
    print_color("\nAvailable commands:\n", VGA_COLOR_LIGHT_RED);
    print("   help     - Display help menu\n");
    print("   clear    - Clear the screen\n");
    print("   echo     - Echo back a message\n");
}

void handle_backspace(unsigned int *current_line_length)
{
    if (*current_line_length > PROMPT_LENGTH){
        print("\b");
        *current_line_length -= 1;
    }
}

void print_prompt()
{
    print_color(PROMPT, VGA_COLOR_LIGHT_BLUE);
}

void handle_input(const char* input_buffer)
{
    char cmd_buffer[256];
    unsigned int idx = 0;
    while (input_buffer[idx] != ' ' && input_buffer[idx] != '\0' && idx < 255)
    {
        cmd_buffer[idx] = input_buffer[idx];
        idx++;
    }
    
    cmd_buffer[idx] = '\0';

    command_t cmd = parse_cmd(cmd_buffer);
    switch(cmd)
    {
        case CMD_UNKNOWN:
            print_color("\nUnknown Command",VGA_COLOR_RED);
            print("\n");
            break;
        case CMD_ECHO:
            echo(input_buffer, idx+1);
            print("\n");
            break;
        case CMD_CLEAR:
            reset_screen();
            break;
        case CMD_HELP:
            print_help_menu();
            break;
    }
    print_prompt();

}
