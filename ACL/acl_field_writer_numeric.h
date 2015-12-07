#pragma once

#include "acl_field_writer.h"

template <class data_t>
class acl_field_writer_numeric 
    : public acl_field_writer<data_t>
{
public:
    acl_field_writer_numeric(char* data_t::*field, size_t field_size)
        : acl_field_writer<data_t>(field, field_size)
    {
    }

    virtual void write(data_t* data, const std::string& src)
    {
        //strncpy(data->*m_field, src.c_str(), m_field_size);
    }
};

