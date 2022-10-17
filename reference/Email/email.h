#pragma once
#include <string>
#include <sstream>

class EmailBuilder;

class Email
{
public:
    friend class EmailBuilder;
    friend class EmailHeaderBuilder;
    friend class EmailBodyBuilder;
    friend std::ostream &operator<<(std::ostream &os, const Email &obj);
    static EmailBuilder create();

private:
    Email() = default;
    std::string m_from;
    std::string m_to;
    std::string m_subject;
    std::string m_body;
    std::string m_attachment;
};
