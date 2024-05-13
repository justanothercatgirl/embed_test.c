#include "embed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const char *resources[] = {"resources/something.png", "resources/sheya_sb.png", "resources/sheya_fu_xuan.png"};

const char *produced_files[] = {"generated_res.h", "generated_res.s", "embed_test"};

int main(int argc, char *argv[])
{
	if (argc <= 1 || !strcmp(argv[1], "build")) {
		if (!embed_resources(resources, sizeof(resources) / sizeof(const char *), "generated_res")) {
			fputs("build failed: could not generate resource files\n", stderr);
			exit(EXIT_FAILURE);
		};
		const char *command[] = {
			"cc", "generated_res.s", "embed_test.c", "-o", "embed_test", "-lraylib", "-I.", NULL};
		execv("/usr/bin/cc", (char *const *)command);
		perror("build failed");
		exit(EXIT_FAILURE);
	} else if (!strcmp(argv[1], "generate")) {
		if (!embed_resources(resources, sizeof(resources) / sizeof(const char *), "generated_res")) {
			fputs("build failed: could not generate resource files\n", stderr);
			exit(EXIT_FAILURE);
		};
		exit(EXIT_SUCCESS);
	} else if (!strcmp(argv[1], "run")) {
		execlp("./embed_test", NULL);
		perror("run failed: ./embed_test:");
		exit(EXIT_FAILURE);
	} else if (!strcmp(argv[1], "clean")) {
		for (const char **i = produced_files; *i != NULL; ++i) {
			if (remove(*i) != 0) perror(*i);
		}
		exit(EXIT_SUCCESS);
	} else if (!strcmp(argv[1], "help")) {
		puts("available arguments:\n\tgenerate: generate assembly and header files for embedded "
		     "resources\n\tbuild: compile the program\n\trun: run compiled executable"
		     "\n\tclean: remove build files and the executable\n\thelp: show this message\n\t"
		     "test: build, move executable to different direcrory and run it");
		exit(EXIT_SUCCESS);
	} else if (!strcmp(argv[1], "test")) {
		char buffer[128] = {0};
		strncpy(buffer, argv[0], 120);
		strcat(buffer, " build");
		if (system(buffer) != 0) exit(EXIT_FAILURE);
		mkdir("test_directory", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); // 0755 basically
		rename("./embed_test", "test_directory/embed_test");
		execlp("test_directory/embed_test", NULL);
		perror("test failed: test_directory/embed_test");
		exit(EXIT_FAILURE);
	} else {
		fputs("unknown argument. run `help` to see available ones.\n", stderr);
		exit(EXIT_FAILURE);
	}
}
