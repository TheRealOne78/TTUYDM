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

#include "signal-handlers.h"

/**
 * @brief Reset password buffer when program receiving ^C (SIGINT)
 *
 * Handle the INT signal on POSIX compliant operating systems by resetting the
 * password input buffer when the user presses ^C (CTRL+C).
 *
 * This makes more sense for a Diplay Manager, because it's supposed to be a
 * daemon, not command-line program.
 *
 * See <https://en.wikipedia.org/wiki/Signal_(IPC)> or signal(7) manual if you
 * don't know what a signal is.
 *
 * @param signum The Signal number. This should be SIGINT.
 * @return None.
 */
void handler_sigint(int signum) {

}
