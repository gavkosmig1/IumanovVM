#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


#define MAX_PROGRAM_LINE_LENGTH 1024
#define MAX_ARG_LENGTH 128
#define MAX_FLAGS_AMOUNT 32


int parse_string(char *string, int *delay, char* program) {
	if (string == NULL) {
		printf("No string");
		return -1;
	}
	char c = 0;
	int ind = 0;
	char number[MAX_PROGRAM_LINE_LENGTH];
	for (;;) {
		c = *string;
		++string;
		if (c == ' ') {
			number[ind] = '\0';
			break;
		}
		number[ind] = c;
		++ind;
	}
	*delay =  atoi(number);
	ind = 0;
	for (;;) {
		c = *string;
		++string;
		if (c == '\n') {
			program[ind] = '\0';
			++string;
			break;
		}
		program[ind] = c;
		++ind;
	}
	return 0;
}


int parse_program_string(char* args[], char* program, int max_args) {
	args[0] = strtok(program, " ");
	int i = 1;
	char *arg;

	while ((arg = strtok(NULL, " ")) != NULL) {
		if (i > max_args - 1) {
			printf("Too many args\n");
			return 1;
		}
		args[i] = arg;
		++i;
	}
	args[i] = NULL;
	return 0;
}


int start(FILE* fp) {
	int delay;
	char program[MAX_PROGRAM_LINE_LENGTH];
	char string[MAX_PROGRAM_LINE_LENGTH];

	while(fgets(string, MAX_PROGRAM_LINE_LENGTH, fp)) {
		parse_string(string, &delay, program);
		pid_t p = fork();
		if (p == -1) {
			perror("fork");
			return -2;
		}
		else if (p == 0) {
			sleep(delay);
			char *args[MAX_ARG_LENGTH];
			parse_program_string(args, program, MAX_FLAGS_AMOUNT);

			execvp(args[0], args);
			perror("\nExecute program:");
			exit(1);
		}
	}

	while (wait(NULL) > 0);
	return 0;
}


int main(int argc, char *argv[], char *envp[]) {
	if (argc < 2) {
		fprintf(stderr, "no file\n");
		return 1;
	} else if (argc > 2) {
		fprintf(stderr, "can't handle more than 1 file\n");
		return 1;
	}

	const char* filepath = argv[1];
	FILE* file = fopen(filepath, "r");
	if (file == NULL) {
		perror("Can't open file\n");
		return -1;
	}
	int ec = start(file);
	fclose(file);
	if (ec == -1) {
		printf("I can't read\n");
	}
	else if (ec == -2) {
		printf("Can't fork\n");
	}
	return 0;
}
