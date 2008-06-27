/*
	Copyright (C) 2004-2005 Cory Nelson

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.

	CVS Info :
		$Author: phrostbyte $
		$Date: 2005/06/16 20:46:40 $
		$Revision: 1.1 $
*/

#include <sqlite3.h>
#include "sqlite3x.hpp"

namespace sqlite3x
{

database_error::database_error(const char *msg) : zypp::Exception(msg)
{}
database_error::database_error(const std::string & msg) : zypp::Exception(msg)
{}
database_error::database_error(sqlite3_connection &con) : zypp::Exception(sqlite3_errmsg(con.db))
{}

}