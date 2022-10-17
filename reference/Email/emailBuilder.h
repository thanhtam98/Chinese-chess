#pragma once
#include "email.h"
#include "abstracEmailBuilder.h"
class EmailBuilder : public AbstractEmailBuilder
{
private:
    Email m_email;
public:
    EmailBuilder() : AbstractEmailBuilder{m_email} {}
};