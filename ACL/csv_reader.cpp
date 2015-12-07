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
    return has_more_data();
}

std::list<std::string> csv_reader::next_row()
{
    std::list<std::string> row;

    while (has_more_columns()) {
        row.push_back(next_column());
    }

    return row;
}

bool csv_reader::has_more_columns()
{
    if (!has_more_data())
    {
        return false;
    }

    return m_buffer[m_buffer_pos] == '\n';
}

std::string csv_reader::next_column()
{
    std::string col;

    bool is_in_string = false;
    bool was_in_string = false;
    std::streamsize start = m_buffer_pos;

    while (has_more_data())
    {
        if (!was_in_string && m_buffer[m_buffer_pos] == '\"')
        {
            if (!is_in_string) {
                col.clear();
                start = m_buffer_pos + 1;

                is_in_string = true;
            }
            else {
                col.append(m_buffer + start, m_buffer + m_buffer_pos);
                is_in_string = false;
                was_in_string = true;
            }
        }

        if (!is_in_string && (m_buffer[m_buffer_pos] == ',' || m_buffer[m_buffer_pos] == '\r'))
        {
            ++m_buffer_pos;
            break;
        }

        ++m_buffer_pos;
        if (m_buffer_pos == m_buffer_data)
        {
            if (!was_in_string)
            {
                col.append(m_buffer + start, m_buffer + m_buffer_pos);
            }
            start = 0;
        }
    }

    return col;
}

bool csv_reader::has_more_data()
{
    ensure_open();

    if (m_buffer_pos < m_buffer_data)
    {
        return true;
    }

    if (!m_file.eof()) 
    {
        next_block();
        return m_buffer_pos < m_buffer_data;
    }

    return false;
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
