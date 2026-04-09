#define PROMPT "V1 > "
#define PROMPT_LENGTH 5

void print_prompt();
void handle_backspace(unsigned int *current_line_length);
void handle_input(const char* input_buffer);
void print_info();
