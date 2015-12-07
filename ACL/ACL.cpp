// ACL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "csv_reader.h"
#include "acl_writer.h"

void show_help()
{
    std::cerr << "Usage: acl input.csv output.dat" << std::endl;
}

template <class reader_t, class writer_t>
int process(const char* input_file_name, const char* output_file_name)
{
    reader_t reader(input_file_name);
    writer_t writer(output_file_name);

    int rows_copied = 0;
    while (reader.has_more_rows()) {
        std::list<std::string> row = reader.next_row();
        if (row.empty())
        {
            continue;
        }

        writer.write_row(row);
        ++rows_copied;
    }

    return rows_copied;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        show_help();
        return -1;
    }

    std::cout << "Conversion started" << std::endl;
    std::cout << "Input file: " << argv[1] << std::endl;
    std::cout << "Output file: " << argv[2] << std::endl;

    try {
        int rows_copied = process<csv_reader, acl_writer>(argv[1], argv[2]);
        std::cout << "Conversion completed." << std::endl;
        std::cout << "Rows copied: " << rows_copied << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

	return 0;
}

