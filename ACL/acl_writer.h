#pragma once

#include "acl_data_type.h"

struct data_block
{
    DEFINE_FIELD(FirstName, field_string, 7);
    DEFINE_FIELD(LastName, field_string, 6);
    DEFINE_FIELD(SIN, field_string, 11);
    DEFINE_FIELD(Department, field_string, 10);
    DEFINE_FIELD(Title, field_string, 17);
    DEFINE_FIELD(Salary, field_numeric, 9);
};

BEGIN_META(data_block);
    DEFINE_FIELD_META(data_block, FirstName);
    DEFINE_FIELD_META(data_block, LastName);
    DEFINE_FIELD_META(data_block, SIN);
    DEFINE_FIELD_META(data_block, Department);
    DEFINE_FIELD_META(data_block, Title);
    DEFINE_FIELD_META(data_block, Salary);
END_META(data_block);

class acl_writer
{
public:
    acl_writer(const char* file_name);
    ~acl_writer();

    void write_row(const std::list<std::string>& row);

private:
    std::string m_file_name;
    std::ofstream m_file;

    meta_data<data_block> m_meta_data;

    void ensure_open();
};

