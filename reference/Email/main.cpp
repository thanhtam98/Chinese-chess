#include <iostream>
#include <sstream>
#include <string>
#include "email.h"
#include "emailBuilder.h"
#include "emailHeaderBuilder.h"
#include "emailBodyBuilder.h"
using namespace std;

int main()
{
    Email mail = Email::create()
                     .header()
                     .from("test1@example.com")
                     .to("test2@example.com")
                     .subject("This is a test mail")
                     .body()
                     .body("This is a test body")
                     .attachment("This is a test attachment");
    std::cout << mail << std::endl;
}