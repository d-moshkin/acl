#include "stdafx.h"
#include "csv_reader.h"

#define BUFFER_SIZE 1024

csv_reader::csv_reader(const char* file_name)
    : m_file_name(file_name)
    , m_buffer(NULL)
    , m_buffer_data(0)
    , m_buffer_pos(0)
{
}

csv_reader::~csv_reader()
{
    if (m_buffer != NULL)
    {
        delete m_buffer;
    }
}

bool csv_reader::has_more_rows()
{
    ensure_open();
    return !m_file.eof();
}

std::list<std::string> csv_reader::next_row()
{
    std::list<std::string> row;

    while (m_buffer_pos < m_buffer_data && m_buffer[m_buffer_pos] == '\r') {
        row.push_back(next_column());
    }

    return row;
}

std::string csv_reader::next_column()
{
    return "";
}

void csv_reader::ensure_open()
{
    if (!m_file.is_open()) 
    {
        m_buffer_data = 0;
        m_buffer_pos = 0;

        m_file.open(m_file_name, std::ios_base::in);

        if (m_file.fail())
        {
            throw std::runtime_error("Can not open input file");
        }
    }
}

void csv_reader::next_block()
{
    if (m_buffer == NULL)
    {
        m_buffer = new char[BUFFER_SIZE];
    }

    m_file.read(m_buffer, BUFFER_SIZE);

    if (m_file.fail() && !m_file.eof())
    {
        throw std::runtime_error("Can not read input file");
    }

    m_buffer_data = m_file.gcount();
    m_buffer_pos = 0;
}
