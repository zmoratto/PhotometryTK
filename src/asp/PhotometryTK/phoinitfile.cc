// __BEGIN_LICENSE__
// Copyright (C) 2010 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__

// What's this file supposed to do ?
//
// (Pho)tometry (Init)ialize Phofile
//
// It's used to create project file and to solve for the starting ET.

#include <vw/Image.h>
using namespace vw;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

using namespace std;

struct Options {

  // For spawning multiple jobs
  int job_id, num_jobs;
};

void handle_arguments( int argc, char *argv[], Options& opt ) {
  po::options_description general_options("");
  general_options.add_options()
    ("job_id,j", po::value<int>(&opt.job_id)->default_value(0), "")
    ("num_jobs,n", po::value<int>(&opt.num_jobs)->default_value(1), "")
    ("help,h", "Display this help message");

  po::variables_map vm;
  try {
    po::store( po::command_line_parser( argc, argv ).options(general_options).run(), vm );
    po::notify( vm );
  } catch (po::error &e) {
    vw_throw( ArgumentErr() << "Error parsing input:\n\t"
              << e.what() << general_options );
  }

  std::ostringstream usage;
  usage << "Usage: " << argv[0] << " [programmer hasn't filled this out]\n";

  if ( vm.count("help") )
    vw_throw( ArgumentErr() << usage.str() << general_options );
}

int main( int argc, char *argv[] ) {

  Options opt;
  try {
    handle_arguments( argc, argv, opt );
  } catch ( const ArgumentErr& e ) {
    vw_out() << e.what() << std::endl;
    return 1;
  } catch ( const Exception& e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
