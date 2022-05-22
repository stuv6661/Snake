/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MLV__PLATFORM_H__
#define __MLV__PLATFORM_H__

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __CYGWIN__ )
#   define OS_WINDOWS
#elif defined( __APPLE_CC__)
#   define OS_APPLE
#elif defined( __MLV_ANDROID__ )
#	define OS_ANDROID
#else
#   define OS_LINUX
#endif

#endif
