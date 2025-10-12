#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>      // The main header for ELF definitions
#include <sys/mman.h> // For memory mapping
#include <sys/stat.h> // For file stats

// Helper function to get a string from the string table
const char *get_string(const char *strtab, size_t strtab_size, size_t offset)
{
    if (offset >= strtab_size)
    {
        return "invalid string table offset";
    }
    return strtab + offset;
}

// Function to print detailed symbol information
void print_symbol(const char *symname, Elf64_Sym *sym)
{
    printf("Symbol: %s\n", symname);

    // Print symbol value (address)
    printf("  Value: 0x%lx\n", sym->st_value);

    // Print symbol size
    printf("  Size: %lu bytes\n", sym->st_size);

    // Print symbol type
    printf("  Type: ");
    switch (ELF64_ST_TYPE(sym->st_info))
    {
    case STT_NOTYPE:
        printf("NOTYPE\n");
        break;
    case STT_OBJECT:
        printf("OBJECT\n");
        break;
    case STT_FUNC:
        printf("FUNCTION\n");
        break;
    case STT_SECTION:
        printf("SECTION\n");
        break;
    case STT_FILE:
        printf("FILE\n");
        break;
    case STT_COMMON:
        printf("COMMON\n");
        break;
    case STT_TLS:
        printf("TLS\n");
        break;
    default:
        printf("Unknown (%d)\n", ELF64_ST_TYPE(sym->st_info));
        break;
    }

    // Print symbol binding
    printf("  Binding: ");
    switch (ELF64_ST_BIND(sym->st_info))
    {
    case STB_LOCAL:
        printf("LOCAL\n");
        break;
    case STB_GLOBAL:
        printf("GLOBAL\n");
        break;
    case STB_WEAK:
        printf("WEAK\n");
        break;
    default:
        printf("Unknown (%d)\n", ELF64_ST_BIND(sym->st_info));
        break;
    }

    // Print symbol visibility
    printf("  Visibility: ");
    switch (ELF64_ST_VISIBILITY(sym->st_other))
    {
    case STV_DEFAULT:
        printf("DEFAULT\n");
        break;
    case STV_INTERNAL:
        printf("INTERNAL\n");
        break;
    case STV_HIDDEN:
        printf("HIDDEN\n");
        break;
    case STV_PROTECTED:
        printf("PROTECTED\n");
        break;
    default:
        printf("Unknown (%d)\n", ELF64_ST_VISIBILITY(sym->st_other));
        break;
    }

    printf("  Section index: %d\n", sym->st_shndx);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int fd;
    struct stat st;
    void *map;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr, *sym_shdr, *str_shdr;
    Elf64_Sym *syms;
    char *strtab;
    char *shstrtab;
    size_t sym_count;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }

    // Open the ELF file
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    // Get file size
    if (fstat(fd, &st) < 0)
    {
        perror("fstat");
        close(fd);
        return 1;
    }

    // Map the file into memory
    map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    // Get the ELF header
    ehdr = (Elf64_Ehdr *)map;

    // Verify this is an ELF file by checking the magic number
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
    {
        fprintf(stderr, "Not a valid ELF file\n");
        munmap(map, st.st_size);
        close(fd);
        return 1;
    }

    // Check if this is a 64-bit ELF file
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
    {
        fprintf(stderr, "Not a 64-bit ELF file\n");
        munmap(map, st.st_size);
        close(fd);
        return 1;
    }

    // Get section header table
    shdr = (Elf64_Shdr *)((char *)map + ehdr->e_shoff);

    // Get section header string table
    // shstrtab points to the start of the section header string table
    shstrtab = (char *)map + shdr[ehdr->e_shstrndx].sh_offset;

    // Find symbol table section and its string table
    sym_shdr = NULL;
    str_shdr = NULL;

    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        // sh_name is the offset into the section header string table. start+offset gives the name
        char *section_name = shstrtab + shdr[i].sh_name;

        // Look for .symtab section
        if (strcmp(section_name, ".symtab") == 0)
        {
            // sym_shdr points to the symbol table section header, not the section itself
            sym_shdr = &shdr[i];
        }

        // Look for .strtab section (string table for .symtab)
        if (strcmp(section_name, ".strtab") == 0)
        {
            // str_shdr points to the string table section header, not the section itself
            str_shdr = &shdr[i];
        }
    }

    if (!sym_shdr)
    {
        fprintf(stderr, "No symbol table found in the ELF file\n");
        munmap(map, st.st_size);
        close(fd);
        return 1;
    }

    if (!str_shdr)
    {
        fprintf(stderr, "No string table found for symbols\n");
        munmap(map, st.st_size);
        close(fd);
        return 1;
    }

    // Get symbol table
    // syms points to the start of the symbol table in memory
    syms = (Elf64_Sym *)((char *)map + sym_shdr->sh_offset);
    // calculate the number of entries in the symbol table by the symbol table section header
    sym_count = sym_shdr->sh_size / sym_shdr->sh_entsize;

    // Get string table
    strtab = (char *)map + str_shdr->sh_offset;

    printf("Found %zu symbols in the symbol table\n\n", sym_count);

    // Print information for each symbol
    for (size_t i = 0; i < sym_count; i++)
    {
        const char *symname = get_string(strtab, str_shdr->sh_size, syms[i].st_name);

        // Skip symbols with empty names
        if (symname[0] != '\0')
        {
            print_symbol(symname, &syms[i]);
        }
    }

    // Clean up resources
    munmap(map, st.st_size);
    close(fd);

    return 0;
}