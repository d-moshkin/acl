#pragma once

class acl_writer
{
public:
    acl_writer(const char* file_name);
    ~acl_writer();

    void write_row(const std::list<std::string>& row);

private:
    std::string m_file_name;
    std::ofstream m_file;
};

