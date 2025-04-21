#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// Option information structure
typedef struct
{
    struct option opt;   // The getopt_long option structure
    char short_opt;      // The corresponding short option (0 if none)
    const char *argname; // Name of argument, if any
    const char *desc;    // Description for help output
} option_info;

// Array of all program options
static option_info options[] = {
    {{.name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h'},
     'h',
     "",
     "Display this help message"},

    {{.name = "verbose", .has_arg = no_argument, .flag = NULL, .val = 'v'},
     'v',
     "",
     "Enable verbose output"},

    {{.name = "output", .has_arg = required_argument, .flag = NULL, .val = 'o'},
     'o',
     "FILE",
     "Write output to FILE"},

    {{.name = "level", .has_arg = required_argument, .flag = NULL, .val = 'l'},
     'l',
     "NUM",
     "Set processing level (1-10)"},

    {{.name = "log", .has_arg = optional_argument, .flag = NULL, .val = 'g'},
     'g',
     "FILE",
     "Enable logging, optionally to FILE"},

    {{0, 0, 0, 0}, 0, "", ""} // End marker
};

// Function to print help using option info
void print_help(const char *program_name)
{
    printf("Usage: %s [OPTIONS] [FILES...]\n\n", program_name);
    printf("Options:\n");

    for (int i = 0; options[i].opt.name != NULL; i++)
    {
        const option_info *info = &options[i];
        printf("  ");

        // Print short option if available
        if (info->short_opt)
            printf("-%c, ", info->short_opt);
        else
            printf("    ");

        // Print long option with argument info
        printf("--%s", info->opt.name);
        if (info->opt.has_arg == required_argument)
            printf("=%s", info->argname);
        else if (info->opt.has_arg == optional_argument)
            printf("[=%s]", info->argname);

        // Print description
        printf("\n        %s\n", info->desc);
    }
}

int main(int argc, char *argv[])
{
    int verbose = 0;
    char *output_file = NULL;
    int level = 1;
    int logging = 0;
    char *log_file = NULL;

    // Extract just the struct option parts for getopt_long
    // sizeof(options)/size(options[0]) gives the number of elements in the array
    struct option long_options[sizeof(options) / sizeof(options[0])];
    char optstring[256] = "";
    char *p = optstring;

    for (int i = 0; options[i].opt.name != NULL; i++)
    {
        long_options[i] = options[i].opt;

        if (options[i].short_opt)
        {
            *p++ = options[i].short_opt;
            if (options[i].opt.has_arg == required_argument)
                *p++ = ':';
            else if (options[i].opt.has_arg == optional_argument)
                *p++ = ':', *p++ = ':';
        }
    }
    *p = '\0'; // Null-terminate the optstring

    // Add the terminator to long_options
    long_options[sizeof(options) / sizeof(options[0]) - 1] = (struct option){0, 0, 0, 0};

    int option_index = 0;
    int c;

    while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        // Find the corresponding option_info
        const option_info *info = NULL;

        if (c == 0)
        {
            // Flag option that set a variable
            info = &options[option_index];
            printf("Flag option '--%s' set\n", info->opt.name);
        }
        else
        {
            // Find by short option
            for (int i = 0; options[i].opt.name != NULL; i++)
            {
                if (options[i].short_opt == c)
                {
                    info = &options[i];
                    option_index = i; // Align option_index with our array
                    break;
                }
            }
        }

        if (info == NULL)
        {
            fprintf(stderr, "Unknown option\n");
            continue;
        }

        printf("Processing option: --%s", info->opt.name);
        if (info->short_opt)
            printf(" (-%c)", info->short_opt);

        if (optarg)
            printf(" with argument: %s", optarg);
        printf("\n");

        // Actual option processing
        switch (c)
        {
        case 'h':
            print_help(argv[0]);
            return 0;

        case 'v':
            verbose = 1;
            break;

        case 'o':
            output_file = optarg;
            break;

        case 'l':
            level = atoi(optarg);
            break;

        case 'g':
            logging = 1;
            // log_file = optarg ? optarg : "program.log";
            break;

        case '?':
            // Error already printed by getopt_long
            break;
        }
    }

    // Show the processed settings
    printf("\nSettings after option processing:\n");
    printf("  Verbose: %s\n", verbose ? "yes" : "no");
    printf("  Output file: %s\n", output_file ? output_file : "(stdout)");
    printf("  Level: %d\n", level);
    printf("  Logging: %s\n", logging ? "enabled" : "disabled");
    if (logging && log_file)
        printf("  Log file: %s\n", log_file);

    // Process non-option arguments
    if (optind < argc)
    {
        printf("\nNon-option arguments:\n");
        for (int i = optind; i < argc; i++)
            printf("  %s\n", argv[i]);
    }

    return 0;
}