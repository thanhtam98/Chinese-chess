#pragma once
#include "string"
#include "emailBuilder.h"
class EmailHeaderBuilder : public AbstractEmailBuilder
{
    public:
    explicit EmailHeaderBuilder(Email &email) : AbstractEmailBuilder{email} {}

    EmailHeaderBuilder &from (const std::string &from)
    {
        m_email.m_from = from;
        return *this;
    }
    EmailHeaderBuilder &to (const std::string &to)
    {
        m_email.m_to = to;
        return *this;
    }
    EmailHeaderBuilder &subject(const std::string &subject)
    {
        m_email.m_subject = subject;
        return *this;
    }
};