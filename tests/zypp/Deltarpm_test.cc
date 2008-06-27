#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "zypp/base/Logger.h"
#include "zypp/base/Exception.h"
#include "zypp/PathInfo.h"
#include "zypp/RepoManager.h"
#include "zypp/sat/Pool.h"
#include "zypp/repo/DeltaCandidates.h"
#include "zypp/repo/PackageDelta.h"
#include "KeyRingTestReceiver.h"

using boost::unit_test::test_case;

using namespace std;
using namespace zypp;
using namespace zypp::repo;
using namespace zypp::filesystem;

#define TEST_DIR TESTS_SRC_DIR "/zypp/data/Delta"

BOOST_AUTO_TEST_CASE(delta)
{
  KeyRingTestReceiver rec;
  rec.answerAcceptUnknownKey(true);
//  rec.answerImportKey(true);
  Pathname rootdir(TEST_DIR );
  RepoManagerOptions opts(rootdir);
  opts.repoRawCachePath = rootdir;
  opts.repoSolvCachePath = rootdir;
  opts.knownReposPath = rootdir;
  opts.knownServicesPath = rootdir;

  RepoManager rm(opts);

  RepoInfo updates;
  updates.setAlias("updates");
  updates.addBaseUrl(Url(string("dir:") + rootdir.absolutename().asString() ));

  try
  {
    rm.buildCache(updates);
    rm.loadFromCache(updates);
  }
  catch (const Exception & e)
  {
    BOOST_FAIL( string("Problem getting the data: ")+ e.msg()) ;
  }
  sat::Pool pool(sat::Pool::instance());

  repo::DeltaCandidates dc(list<Repository>(pool.reposBegin(),pool.reposEnd()), "libzypp");

  std::list<packagedelta::DeltaRpm> deltas = dc.deltaRpms(0);
  for_ (it,deltas.begin(),deltas.end())
  {
    BOOST_CHECK(it->name() == "libzypp");
    BOOST_CHECK(it->edition() == Edition("4.21.3-2"));
    BOOST_CHECK(it->arch() == "i386");
    BOOST_CHECK(it->baseversion().edition().match(Edition("4.21.3-1")) 
      ||it->baseversion().edition().match(Edition("4.21.2-3")));

    cout << it->name() << " - " << it->edition() << " - " <<  it->arch()
      << " base: " << it->baseversion().edition() << endl;

    cout << (it->edition() == "4.21.3-2") << endl;              // fine
    cout << (it->edition() == Edition("4.21.3-2")) << endl;     // fine
    cout << (it->edition().match(Edition("4.21.3-2"))) << endl; //! \todo FIXME says no 
    cout << (it->edition().match("4.21.3-2")) << endl;          //! \todo FIXME says no
  }

  //! \todo FIXME Edition("0:4.21.3-2") != Edition("4.21.3-2") (not even does Edition("0:4.21.3-2").match(Edition("4.21.3-2"))
  rm.cleanCache(updates);
}