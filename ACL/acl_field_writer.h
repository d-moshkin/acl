#pragma once

template <class data_t>
class acl_field_writer
{
public:
    virtual void write(data_t* data, const std::string& src) = 0;

};

template <class data_t, size_t size>
class acl_field_writer_impl : public acl_field_writer<data_t>
{
public:
    acl_field_writer_impl(char (data_t::*field)[size])
        : m_field(field)
    {
    }

    virtual ~acl_field_writer_impl()
    {
    }

protected:
    char (data_t::*m_field)[size];
};

