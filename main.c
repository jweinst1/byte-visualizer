#include <stdio.h>
#include <stdlib.h>

#ifndef PVIS_NAME
#define PVIS_NAME "byte-tool"
#endif


#define PRINT_NEWLINE putc('\n', stdout)

static inline void
__get_file_ptr_size(FILE* fp, size_t* sz)
{
        fseek(fp, 0L, SEEK_END);
        *sz = ftell(fp);
        rewind(fp);
}

static void*
__safe_malloc_bytes(size_t size)
{
	void* arr = malloc(size);
	if(arr == NULL) 
	{
		fprintf(stderr, "Out of Memory Error: 'malloc()' returned NULL, exiting.");
		exit(2);
	}
	return arr;
}

static void* _read_file_into_mem(const char* path, size_t* file_size)
{
	FILE* fp;
	*file_size = 0;
	void* mem_got;
	fp = fopen(path, "rb");
	if(fp == NULL)
	{
		fprintf(stderr, "Cannot read file at path %s\n", path);
		exit(2);
	}
	__get_file_ptr_size(fp, file_size);
	mem_got = __safe_malloc_bytes(*file_size);
	fread(mem_got, *file_size, 1, fp);
	fclose(fp);
	return mem_got;
}

static inline void _print_fmt_byte(unsigned char b)
{
	if(b < 10) printf("\\x0%u", b);
	else printf("\\x%u", b);
}


int main(int argc, char const *argv[])
{
	const char* path;
	long line_length;
	long line_c;
	void* mem_block;
	size_t num_bytes;
	size_t bytes_i;
	unsigned char* reader;
	if(argc != 3)
	{
		fprintf(stderr, "Error: Invalid arguments.\n");
		fprintf(stderr, "Usage: %s <file> <bytes per line>\n", PVIS_NAME);
		exit(1);
	}
	line_length = strtol(argv[2], NULL, 10);
	path = argv[1];
	mem_block = _read_file_into_mem(path, &num_bytes);
	printf("Reading %lu bytes from %s\n", num_bytes, path);
	puts("start_________________");
	line_c = line_length;
	reader = mem_block;
	for (bytes_i = 0; bytes_i < num_bytes; bytes_i++)
	{
		if(!line_c)
		{
			line_c = line_length;
			PRINT_NEWLINE;
		}
		_print_fmt_byte(reader[bytes_i]);
		line_c--;
	}
	PRINT_NEWLINE;
	puts("___________________end");

	free(mem_block);
	return 0;
}
