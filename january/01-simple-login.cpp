/**
 * 01-simple-login.cpp
 * logic> the user try the password if him wrong, try again with limit of chances to login
*/

#include<iostream>
#include<string>

int main()
{
    int count = 0;
    std::string try_passwd = {};

    while (true) {
        std::cout << "digit the password> ";
        std::cin >> try_passwd;

        std::string real_passwd = {"streetfighter"};

        if ((try_passwd) == (real_passwd)) {
            std::cout << "welcome to hft system\n ";
            break;
        } else {
            count += 1;
            std::cout << "sorry u wrong, try again\n ";
        }

        if (count == 3) {
            std::cout << "system block, try later\n ";
            break;
        } else if (count < 3) {
            continue;
        }
}
   return 0;
}
