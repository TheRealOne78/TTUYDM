/*
 * Copyright (C) 2024 TheRealOne78 <bajcsielias78@gmail.com>
 *
 * This file is part of the TTUYDM project
 *
 * TTUYDM is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * TTUYDM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with TTUYDM. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "version-help.h"
#include "info.h"
#include <stdio.h>

void printHelp(void) {
    printf("\n"
           "TTUYDM - TeleTYpewriter + Text-based User Interface Display Manager"            "\n"
                                                                                            "\n"
           "Usage: ttuydm [options]"                                                        "\n"
                                                                                            "\n"
           "Options:"                                                                       "\n"
           "-h, --help\t\t\t"              "Output this help list and exit"                 "\n"
           "-v, --version\t\t\t"           "Output version information and license and exit""\n"
           "\n");
}

void printVersion(void) {
    printf("TTUYDM version %s | git %s" /* version number */                                "\n"
           "Source URI: <%s>"                                                               "\n"
                                                                                            "\n"
           "Copyright (C) 2024 TheRealOne78"                                                "\n"
           "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.""\n"
           "This is free software: you are free to change and redistribute it."             "\n"
           "There is NO WARRANTY, to the extent permitted by law."                          "\n"
           "\n"
           , __VERSION_STR, GIT_HASH_SHORT, SRC_URI);
}
