/*
  Copyright (C) 2010,2011,2012,2013,2014 The ESPResSo project
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

#include "utils.hpp"
#include "parser.hpp"
#include "cg_dna_tcl.hpp"

#ifdef CG_DNA

void cg_dna_basepair_usage(Tcl_Interp *interp) { 
  puts("usage: cg_dna_basepair { r0 alpha E0 kd sigma1 sigma2 psi01 psi02 E0sb r0sb alphasb f2 f3 }");
}

void cg_dna_stacking_usage(Tcl_Interp *interp) { 
  puts("usage: cg_dna_stacking { rm epsilon a0 a1 a2 a3 a4 a5 a6 a7 b1 b2 b3 b4 b5 b6 b7 }");
}

int tclcommand_inter_parse_cg_dna_basepair(Tcl_Interp *interp, int bond_type, int argc, char **argv) {   
  DoubleList params;
  
  init_doublelist(&params);

  argc--;
  argv++;

  if(!ARG0_IS_DOUBLELIST(params)) {
    cg_dna_basepair_usage(interp);
    return ES_ERROR;
  }

  if(params.n != 13) {
    puts("Wrong number of parameters");
    cg_dna_basepair_usage(interp);
    return ES_ERROR;
  }

  cg_dna_basepair_set_params(bond_type, &params);

  return ES_OK; 
}

int tclcommand_inter_parse_cg_dna_stacking(Tcl_Interp *interp, int bond_type, int argc, char **argv) {
  DoubleList params;
  
  init_doublelist(&params);

  argc--;
  argv++;

  if(!ARG0_IS_DOUBLELIST(params)) {
    cg_dna_basepair_usage(interp);
    return ES_ERROR;
  }

  if(params.n != 17) {
    puts("Wrong number of parameters");
    cg_dna_stacking_usage(interp);
    return ES_ERROR;
  }

  cg_dna_stacking_set_params(bond_type, &params);

  return ES_OK; 
}

#endif