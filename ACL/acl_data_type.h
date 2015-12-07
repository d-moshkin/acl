#pragma once

#include "acl_field_writer_string.h"
#include "acl_field_writer_numeric.h"

enum field_type
{
    field_string,
    field_numeric
};

template<class data_type>
class meta_data {};

#define DEFINE_FIELD(name, type, size)                  \
    char field_##name[size];                            \
    static const field_type field_##name##_type = type; \
    static const size_t field_##name##_size = size;

#define BEGIN_META(data_type)                           \
    struct data_type##_meta                             \
    {                                                   \
    std::list<acl_field_writer<data_type>*> field_writer_enumerator; \
                                                        \
    data_type##_meta()                                  \
    {

#define DEFINE_FIELD_META(data_type, name)              \
    switch (data_type::field_##name##_type) {           \
    case field_string:                                  \
        field_writer_enumerator.push_back(              \
            new acl_field_writer_string<data_type>(     \
            (char* data_type::*) &data_type::field_##name, \
            data_type::field_##name##_size));           \
        break;                                          \
    case field_numeric:                                 \
        field_writer_enumerator.push_back(              \
            new acl_field_writer_numeric<data_type>(    \
            (char* data_type::*) &data_type::field_##name, \
            data_type::field_##name##_size));           \
        break;                                          \
    }

#define END_META(data_type)                             \
    }                                                   \
                                                        \
    ~data_type##_meta()                                 \
    {                                                   \
        for (acl_field_writer<data_type>* writer : field_writer_enumerator) \
            delete writer;                              \
    }                                                   \
                                                        \
    void write(data_type* dst_ptr, const std::list<std::string>& src) \
    {                                                   \
        std::list<std::string>::const_iterator ifield_src = src.begin(); \
        std::list<acl_field_writer<data_type>*>::iterator ifield_dst = field_writer_enumerator.begin(); \
                                                        \
        while (ifield_src != src.end() && ifield_dst != field_writer_enumerator.end()) \
        {                                               \
            (*ifield_dst)->write(dst_ptr, *ifield_src); \
            ++ifield_src;                               \
            ++ifield_dst;                               \
        }                                               \
                                                        \
        while (ifield_dst != field_writer_enumerator.end()) \
        {                                               \
            (*ifield_dst)->write(dst_ptr, "");          \
            ++ifield_dst;                               \
        }                                               \
    }                                                   \
};                                                      \
                                                        \
template<>                                              \
class meta_data<data_type> : public data_type##_meta {};