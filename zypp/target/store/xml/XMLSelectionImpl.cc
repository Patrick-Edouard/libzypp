/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/target/store/xml/XMLSelectionImpl.cc
 *
*/
#include "zypp/target/store/xml/XMLSelectionImpl.h"

using namespace std;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace storage
  { /////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    //
    //	METHOD NAME : XMLSelectionImpl::XMLSelectionImpl
    //	METHOD TYPE : Ctor
    //
    XMLSelectionImpl::XMLSelectionImpl() : _visible(true)
    {}

    ///////////////////////////////////////////////////////////////////
    //
    //	METHOD NAME : XMLSelectionImpl::~XMLSelectionImpl
    //	METHOD TYPE : Dtor
    //
    XMLSelectionImpl::~XMLSelectionImpl()
    {}

    Label XMLSelectionImpl::category() const
    { return _category.text(); }

    bool XMLSelectionImpl::visible() const
    { return _visible; }

    Label XMLSelectionImpl::order() const
    { return _order; }

    const std::set<std::string> XMLSelectionImpl::suggests() const
    { return _suggests; }

    const std::set<std::string> XMLSelectionImpl::recommends() const
    { return _recommends; }

    const std::set<std::string> XMLSelectionImpl::install_packages( const Locale & lang ) const
    { return _install_packages; }

    /////////////////////////////////////////////////////////////////
  } // namespace storage
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////