#include <main.h>
/**
 * check_if_elf - checks if file is an ELF file by checking if it
 *                contains the magic numbers/file signature of an ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
 */
void check_if_elf(unsigned char *e_ident) {
    int index = 0;

    while (index < 4) {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F') /* 0x7F is 127 in ASCII */
        {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(EXIT_FAILURE);
        }

        index++;
    }
}

/**
 * ... (existing function definitions) ...
 */

/**
 * close_file - closes the ELF file
 *
 * @elf_file: the file descriptor for the ELF file
 *
 * Return: nothing
 */
void close_file(int elf_file) {
    if (close(elf_file) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int elf_file = open(argv[1], O_RDONLY);
    if (elf_file == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    Elf64_Ehdr *elf = malloc(sizeof(Elf64_Ehdr));
    if (elf == NULL) {
        close_file(elf_file);
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    ssize_t read_file = read(elf_file, elf, sizeof(Elf64_Ehdr));
    if (read_file == -1) {
        perror("Error");
        free(elf);
        close_file(elf_file);
        exit(EXIT_FAILURE);
    }

    check_if_elf(elf->e_ident);
    printf("ELF Header:\n");
    print_magic(elf->e_ident);
    print_class(elf->e_ident);
    print_data(elf->e_ident);
    print_version(elf->e_ident);
    print_osabi(elf->e_ident);
    print_abi(elf->e_ident);
    print_type(elf->e_type, elf->e_ident);
    print_entry(elf->e_entry, elf->e_ident);

    free(elf);
    close_file(elf_file);
    return 0;
}
