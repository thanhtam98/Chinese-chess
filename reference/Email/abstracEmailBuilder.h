#pragma once
#include "email.h"

class EmailHeaderBuilder;
class EmailBodyBuilder;

class AbstractEmailBuilder
{
protected:
    Email &m_email;
    explicit AbstractEmailBuilder(Email &email) : m_email(email){};

public:
    operator Email() const
    {
        return std::move(m_email);
    };
    EmailHeaderBuilder header() const;
    EmailBodyBuilder body() const;
};