clear_terminal := clear
compile := gcc
compile_option := -c
enable_warnings := -Wall -Wextra
header_file := ./minishell.h
library_option := -l
new_curses_library := ncurses # https://en.wikipedia.org/wiki/Ncurses
NAME := minishell
norminette := norminette
object_files := \
allocate_memory.o \
calculate_string_length.o \
format_environment.o \
free_memory.o \
handle_commands.o \
handle_signals.o \
main.o \
open_terminal.o \
print_error_message.o \
print_message.o \
read_input_until_new_line.o
output_name_option := -o
program_file := ./${NAME}
remove_file := rm
remove_file_option := -f
source_files := $(object_files:.o=.c)
turn_warnings_into_errors := -Werror

default_rule: clear_terminal remove_program norminette compile execute_program

clear_terminal:
	@${clear_terminal}

remove_program:
	@${remove_file} ${remove_file_option} ${program_file}

norminette:
	@$(eval norminette_errors=`${norminette} ${header_file} ${source_files} | grep --invert-match 'OK'`)
	@if [ "${norminette_errors}" != "" ]; then\
		echo "${norminette_errors}";\
		exit 1;\
	fi

compile: ${program_file}

execute_program:
	@${program_file}

# The "all", "${NAME}", "clean", "fclean" and "re" make rules are mandatory
# by 42's Norm (version 3 at the time of writting this comment).

all: ${program_file}

%.o: %.c
	@${compile} \
		${enable_warnings} \
		${turn_warnings_into_errors} \
		${compile_option} $< \
		${output_name_option} $@

${NAME}: ${object_files}
	@${compile} \
		${enable_warnings} \
		${turn_warnings_into_errors} \
		${output_name_option} ${program_file} \
		${object_files} \
		${library_option}${new_curses_library}

clean:
	@${remove_file} ${remove_file_option} ${object_files}

fclean: clean
	@${remove_file} ${remove_file_option} ${program_file}

re: fclean all

.PHONY: default_rule clear_terminal remove_program norminette compile execute_program all clean fclean re
