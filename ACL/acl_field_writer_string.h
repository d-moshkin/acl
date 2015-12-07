#pragma once

#include "acl_field_writer.h"

template <class data_t, size_t size>
class acl_field_writer_string
    : public acl_field_writer_impl<data_t, size>
{
public:
    acl_field_writer_string(char (data_t::*field)[size])
        : acl_field_writer_impl<data_t, size>(field)
    {
    }

    virtual void write(data_t* data, const std::string& src)
    {
        size_t src_size = src.size();
        size_t i = 0;

        char(data_t::*fld)[7] = &data_t::field_FirstName;

        while (i < size && i < src_size)
        {
            (data->*m_field)[i] = src[i];
            ++i;
        }

        while (i < size)
        {
            (data->*m_field)[i] = ' ';
            ++i;
        }
    }
};

