#pragma once

class csv_reader
{
public:
    csv_reader(const char* file_name);
    ~csv_reader();

    bool has_more_rows();
    std::list<std::string> next_row();

private:
    std::string m_file_name;
    std::ifstream m_file;

    char *m_buffer;
    std::streamsize m_buffer_data;
    std::streamsize m_buffer_pos;

    std::string next_column();

    void ensure_open();
    void next_block();
};

