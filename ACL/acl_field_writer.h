#pragma once

template <class data_t>
class acl_field_writer
{
public:
    acl_field_writer(char* data_t::*field, size_t field_size)
        : m_field(field)
        , m_field_size(field_size)
    {
    }

    virtual ~acl_field_writer()
    {
    }

    virtual void write(data_t* data, const std::string& src) = 0;

protected:
    char* data_t::*m_field;
    size_t m_field_size;
};

