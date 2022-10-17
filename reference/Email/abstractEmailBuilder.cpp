#include "abstracEmailBuilder.h"
#include "emailBuilder.h"
#include "emailBodyBuilder.h"
#include "emailHeaderBuilder.h"

EmailHeaderBuilder AbstractEmailBuilder::header() const
{
    return EmailHeaderBuilder{m_email};
}
EmailBodyBuilder AbstractEmailBuilder::body() const
{
    return EmailBodyBuilder{m_email};
}