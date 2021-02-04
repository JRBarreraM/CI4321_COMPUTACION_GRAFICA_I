#ifndef CS248_CONSOLE_H
#define CS248_CONSOLE_H

#include <ostream>

#define ANSI_RESET "\x1b[0m"
#define ANSI_R "\x1b[31m"
#define ANSI_G "\x1b[32m"
#define ANSI_B "\x1b[34m"
#define ANSI_C "\x1b[36m"
#define ANSI_M "\x1b[35m"
#define ANSI_Y "\x1b[33m"

#define out_msg(s) std::cout << ANSI_B << "[CS248] " << ANSI_RESET << s << std::endl << std::flush
#define out_wrn(s) std::cout << ANSI_Y << "[CS248] " << ANSI_RESET << s << std::endl << std::flush
#define out_err(s) std::cout << ANSI_R << "[CS248] " << ANSI_RESET << s << std::endl << std::flush

#endif // CS248_CONSOLE_H
