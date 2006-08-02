/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/CheckSum.cc
 *
*/

#include "zypp/base/Logger.h"
#include "zypp/base/String.h"

#include "zypp/CheckSum.h"
#include "zypp/Digest.h"

using std::endl;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////

  const std::string & CheckSum::md5Type()
  { static std::string _type( "md5" ); return _type; }

  const std::string & CheckSum::shaType()
  { static std::string _type( "sha" ); return _type; }

  const std::string & CheckSum::sha1Type()
  { static std::string _type( "sha1" ); return _type; }

  const std::string & CheckSum::sha256Type()
  { static std::string _type( "sha256" ); return _type; }


  CheckSum::CheckSum()
  {}

  CheckSum::CheckSum( const std::string & type, const std::string & checksum )
  : _type( str::toLower( type ) )
  , _checksum( checksum )
  {
    switch ( checksum.size() )
      {
      case 64:
        if ( _type == sha256Type() )
          return;
        if ( _type.empty() || _type == shaType() )
          {
            _type = sha256Type();
            return;
          }
        // else: dubious
        break;

      case 40:
        if ( _type == sha1Type() )
          return;
        if ( _type.empty() || _type == shaType() )
          {
            _type = sha1Type();
            return;
          }
        // else: dubious
        break;

      case 32:
        if (  _type == md5Type() )
          return;
        if ( _type.empty() )
          {
            _type = md5Type();
            return;
          }
        // else: dubious
        break;

      case 0:
        return; // empty checksum is ok
        break;

      default:
        if ( _type.empty() )
          {
            WAR << "Can't determine type of " << checksum.size() << " byte checksum '" << _checksum << "'" << endl;
            return;
          }
        // else: dubious
        break;
      }

    // dubious
    WAR << "Dubious type '" << _type << "' for " << checksum.size() << " byte checksum '" << _checksum << "'" << endl;
  }

  CheckSum::CheckSum( const std::string & type_r, std::istream & input_r )
  {
    if ( input_r.good() && ! type_r.empty() )
      {
        _type = str::toLower( type_r );
        _checksum = Digest::digest( _type, input_r );
        if ( ! input_r.eof() || _checksum.empty() )
          {
            _type = _checksum = std::string();
          }
      }
  }

  std::ostream & operator<<( std::ostream & str, const CheckSum & obj )
  {
    if ( obj.checksum().empty() )
      {
        return str << std::string("NoCheckSum");
      }

    return str << ( obj.type().empty() ? std::string("UNKNOWN") : obj.type() ) << '-' << obj.checksum();
  }


  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
