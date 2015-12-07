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

}
