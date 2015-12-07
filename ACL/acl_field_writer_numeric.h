#pragma once

#include "acl_field_writer.h"

template <class data_t, size_t size>
class acl_field_writer_numeric 
    : public acl_field_writer_impl<data_t, size>
{
public:
    acl_field_writer_numeric(char (data_t::*field)[size])
        : acl_field_writer_impl<data_t, size>(field)
    {
    }

    virtual void write(data_t* data, const std::string& src)
    {
        size_t src_size = src.size();
        size_t i = 0;

        while (i + src_size < size)
        {
            (data->*m_field)[i] = ' ';
            ++i;
        }

        size_t t = 0;
        while (i < size)
        {
            (data->*m_field)[i] = src[t];
            ++i; ++t;
        }
    }
};

