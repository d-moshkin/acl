#include "stdafx.h"
#include "acl_writer.h"

acl_writer::acl_writer(const char* file_name)
    : m_file_name(file_name)
{
}

acl_writer::~acl_writer()
{
}

void acl_writer::write_row(const std::list<std::string>& row)
{
    data_block block;
    m_meta_data.write(&block, row);

    m_file.write((const char*) (&block), sizeof(data_block));
    if (m_file.fail())
        throw std::runtime_error("Can not write output file");
}

void acl_writer::ensure_open()
{
    if (!m_file.is_open())
    {
        m_file.open(m_file_name, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
        if (m_file.fail())
            throw std::runtime_error("Can not open output file");
    }
}

