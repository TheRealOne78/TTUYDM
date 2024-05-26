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

#ifndef __VERSION_HELP_H__
#define __VERSION_HELP_H__

#ifdef __cplusplus
extern "C" {
#endif

    /// Print help list
    void printHelp(void);

    /// Print version, git hash and copyright info
    void printVersion(void);

#ifdef __cplusplus
}
#endif // extern "C" closing bracket

#endif // __VERSION_HELP_H__
