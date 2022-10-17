#pragma once
#include <string>
#include "emailBuilder.h"
class EmailBodyBuilder : public AbstractEmailBuilder
{
    public:
    explicit EmailBodyBuilder(Email &email): AbstractEmailBuilder{email}
        {
        }
        EmailBodyBuilder &body (const std::string &body)
        {
            m_email.m_body = body;
            return *this;
        }
        EmailBodyBuilder &attachment(const std::string &att)
        {
            m_email.m_attachment = att;
            return *this;
        }
};


