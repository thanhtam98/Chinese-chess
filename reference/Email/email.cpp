#include "email.h"
#include "emailBuilder.h"

EmailBuilder Email::create()
{
    return EmailBuilder{};
}

std::ostream &operator<<(std::ostream &os, const Email &obj)
{
    return os << "from: " << obj.m_from << std::endl
              << "to: " << obj.m_to << std::endl
              << "subject: " << obj.m_subject << std::endl
              << "body: " << obj.m_body << std::endl;
}