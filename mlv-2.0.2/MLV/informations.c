/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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

#include "MLV_information.h"
#include "config.h"

const char* MLV_get_package_name( ){
	return PACKAGE_NAME;
}

const char* MLV_get_version( ){
	return VERSION;
}

const char* MLV_get_revision_of_revision_control_software( ){
	return MLV_RCS_REVISION;
}

const char* MLV_get_repository( ){
	return MLV_REPOSITORY;
}

const char* MLV_get_bug_report_address( ){
	return PACKAGE_BUGREPORT;
}

const char* MLV_get_web_distribution( ){
	return PACKAGE_URL;
}

const char* MLV_get_licence( ){
	return "GPL V3";
}
