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

#ifndef __SIGNAL_HANDLERS_H__
#define __SIGNAL_HANDLERS_H__

#ifdef __cplusplus

extern "C" {
#endif

#include "stdbool.h"

    /**
     * Check if SIGINT was called.
     */
    bool IS_SIGINT_TRIGGERED;

    /**
     * @brief Reset password buffer when program receiving ^C (SIGINT)
     *
     * Handle the INT signal on POSIX compliant operating systems by resetting the
     * password input buffer when the user presses ^C (CTRL+C).
     *
     * This makes more sense for a Diplay Manager, because it's supposed to be a
     * daemon, not command-line program.
     *
     * @see https://en.wikipedia.org/wiki/Signal_(IPC)
     * @see https://www.man7.org/linux/man-pages/man7/signal.7.html
     * @see man signal(7)
     *
     * @param signum The Signal number. This should be SIGINT.
     * @return None.
     */
    void handler_sigint(int signum);

#ifdef __cplusplus
}
#endif // extern "C" closing bracket

#endif // __SIGNAL_HANDLERS_H__
