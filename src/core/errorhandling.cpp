/*
  Copyright (C) 2010,2012,2013,2014,2015,2016 The ESPResSo project
  Copyright (C) 2002,2003,2004,2005,2006,2007,2008,2009,2010 
  Max-Planck-Institute for Polymer Research, Theory Group
  
  This file is part of ESPResSo.
  
  ESPResSo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ESPResSo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/
/** \file errorhandling.cpp
    Implementation of \ref errorhandling.hpp.
*/
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <memory>

#include "utils.hpp"
#include "errorhandling.hpp"

#include "MpiCallbacks.hpp"
#include "RuntimeErrorCollector.hpp"

using namespace std;
using Communication::mpiCallbacks;

namespace ErrorHandling {

/* Forward declarations */

void mpi_gather_runtime_errors_slave(int node, int parm);

/* Definitions */

static void sigint_handler(int sig) {
  /* without this exit handler the nodes might exit asynchronously
   * without calling MPI_Finalize, which may cause MPI to hang
   * (e.g. this handler makes CTRL-c work properly with poe)
   *
   * NOTE: mpirun installs its own handler for SIGINT/SIGTERM
   *       and takes care of proper cleanup and exit */


  static int numcalls = 0;
  if (numcalls++ > 0) exit(sig); // catch sig only once

  /* we use runtime_error to indicate that sig was called;
   * upon next call of mpi_gather_runtime_errors all nodes 
   * will clean up and exit. */
  runtimeErrorMsg() << "caught signal " << sig;
}

void register_sigint_handler() {
  signal(SIGINT, sigint_handler);
}

/** RuntimeErrorCollector instance.
 *  This is a weak pointer so we don't
 *  leak on repeated calls of @f init_error_handling.
 */
unique_ptr<RuntimeErrorCollector> runtimeErrorCollector;

/** Initialize the error collection system. */
void init_error_handling() {
  mpiCallbacks().add(mpi_gather_runtime_errors_slave);
  
  runtimeErrorCollector = unique_ptr<RuntimeErrorCollector>(new RuntimeErrorCollector(mpiCallbacks().comm()));
}

void _runtimeWarning(const std::string &msg, 
                     const char* function, const char* file, const int line) {
  runtimeErrorCollector->warning(msg, function, file, line);
}

void _runtimeWarning(const char* msg, 
                     const char* function, const char* file, const int line) {
  runtimeErrorCollector->warning(msg, function, file, line);
}

void _runtimeWarning(const std::ostringstream &msg, 
                     const char* function, const char* file, const int line) {
  runtimeErrorCollector->warning(msg, function, file, line);
}

void _runtimeError(const std::string &msg, 
                   const char* function, const char* file, const int line) {
  runtimeErrorCollector->error(msg, function, file, line);
}

void _runtimeError(const char* msg, 
                   const char* function, const char* file, const int line) {
  runtimeErrorCollector->error(msg, function, file, line);
}

void _runtimeError(const std::ostringstream &msg, 
                   const char* function, const char* file, const int line) {
  runtimeErrorCollector->error(msg, function, file, line);
}

RuntimeErrorStream _runtimeErrorStream(const std::string &file, const int line, const std::string &function) {
  return RuntimeErrorStream(*runtimeErrorCollector, file, line, function);
}

vector<RuntimeError>
mpi_gather_runtime_errors() {
  // Tell other processors to send their erros
  mpiCallbacks().call(mpi_gather_runtime_errors_slave, -1, 0);
  return runtimeErrorCollector->gather();
}

void mpi_gather_runtime_errors_slave(int node, int parm) {
  runtimeErrorCollector->gatherSlave();
}

} /* ErrorHandling */

void errexit() {
#ifdef FORCE_CORE
  core();
#endif
  mpiCallbacks().comm().abort(1);
  exit(1);
}

int check_runtime_errors() {
  using namespace ErrorHandling;
  return runtimeErrorCollector->count(RuntimeError::ErrorLevel::ERROR);
}
