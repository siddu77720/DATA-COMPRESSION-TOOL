#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void compress_file(const char *input_filename, const char *output_filename) {
    FILE *fin = fopen(input_filename, "r");
    if (fin == NULL) {
        printf("Error: Cannot open input file %s\n", input_filename);
        return;
    }
    FILE *fout = fopen(output_filename, "w");
    if (fout == NULL) {
        printf("Error: Cannot create output file %s\n", output_filename);
        fclose(fin);
        return;
    }

    int count = 1;
    int prev = fgetc(fin);
    if (prev == EOF) {
        printf("Input file is empty.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    int curr;
    while ((curr = fgetc(fin)) != EOF) {
        if (curr == prev) {
            count++;
        } else {
            fprintf(fout, "%d%c", count, prev);
            count = 1;
            prev = curr;
        }
    }
    // Write the last run
    fprintf(fout, "%d%c", count, prev);

    fclose(fin);
    fclose(fout);
    printf("File compressed successfully and saved as %s\n", output_filename);
}

void decompress_file(const char *input_filename, const char *output_filename) {
    FILE *fin = fopen(input_filename, "r");
    if (fin == NULL) {
        printf("Error: Cannot open input file %s\n", input_filename);
        return;
    }
    FILE *fout = fopen(output_filename, "w");
    if (fout == NULL) {
        printf("Error: Cannot create output file %s\n", output_filename);
        fclose(fin);
        return;
    }

    int c;
    int count = 0;
    while ((c = fgetc(fin)) != EOF) {
        if (isdigit(c)) {
            count = count * 10 + (c - '0');  // accumulate digit for multi-digit counts
        } else {
            // c is the character, print it count times
            for (int i = 0; i < count; i++) {
                fputc(c, fout);
            }
            count = 0; // reset count
        }
    }

    fclose(fin);
    fclose(fout);
    printf("File decompressed successfully and saved as %s\n", output_filename);
}

int main() {
    int choice;
    char input_file[100], output_file[100];

    printf("CODTECH Internship Task 4 - Data Compression Tool (RLE)\n");
    printf("Choose an option:\n");
    printf("1. Compress a text file\n");
    printf("2. Decompress a text file\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter input filename to compress: ");
        scanf("%s", input_file);
        printf("Enter output filename for compressed data: ");
        scanf("%s", output_file);
        compress_file(input_file, output_file);
    } else if (choice == 2) {
        printf("Enter input filename to decompress: ");
        scanf("%s", input_file);
        printf("Enter output filename for decompressed data: ");
        scanf("%s", output_file);
        decompress_file(input_file, output_file);
    } else {
        printf("Invalid choice. Please run again and enter 1 or 2.\n");
    }

    return 0;
}
