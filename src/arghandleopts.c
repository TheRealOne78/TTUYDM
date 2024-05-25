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

#include "arghandleopts.h"
#include "version-help.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief Handle CLI arguments with getopt
 *
 * Handle the command line arguments using getopt.
 * This should run first after main() gets called because this just handles
 * version and help printing when the user requests that.
 *
 * @param argc Points to argc (argument count)
 *
 * @param argv Directly has argv (argument values).
 *
 * @return None.
 */
void argHandleOpts(int* restrict argc, char* argv[]) {

    static struct option long_options [] = {
    { "help"   , no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'v' },
    { NULL     , 0          , NULL, 0   }};

    /* And check for arguments */
    while(1) {
        int c = getopt_long(*argc, argv, "hv", long_options, NULL);
        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch(c) {
            /* help */
            case 'h':
                printHelp();
                exit(EXIT_SUCCESS);
                break;

                /* version */
            case 'v':
                printVersion();
                exit(EXIT_SUCCESS);
                break;

            default:
                abort();
        }
    }

}
