/*
  Copyright (C) 2014,2015,2016 The ESPResSo project
  
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
#include "config.hpp"
#include "electrokinetics_tcl.hpp"
#include "electrokinetics.hpp"
#include "lb.hpp"
#include "lb-boundaries.hpp"
#include "lb-boundaries_tcl.hpp"
#include "initialize.hpp"
#include "electrokinetics_pdb_parse.hpp"

#ifdef ELECTROKINETICS
extern int ek_initialized;
#endif

int tclcommand_electrokinetics(ClientData data, Tcl_Interp *interp, int argc, char **argv) {
#ifndef ELECTROKINETICS
  Tcl_AppendResult(interp, "Feature ELECTROKINETICS required", NULL);
  return TCL_ERROR;
#else

  argc--;
  argv++;

  int err = TCL_OK;
  int species;
  double floatarg;
  double vectarg[3];
  int coord[3];
  char int_buffer[TCL_INTEGER_SPACE];
  char double_buffer[TCL_DOUBLE_SPACE];

#ifdef EK_REACTION
  int reactant,
      product0,
      product1;
  double ct_rate,
         rho_reactant_reservoir, 
         rho_product0_reservoir, 
         rho_product1_reservoir, 
         fraction0,
         fraction1,
         mass_reactant,
         mass_product0,
         mass_product1;
#endif

  if(argc < 2) 
  {
    Tcl_AppendResult(interp, "Usage of \"electrokinetics\":\n\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics [agrid #float] [lb_density #float] [viscosity #float] [friction #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                [bulk_viscosity #float] [gamma_even #float] [gamma_odd #float] [T #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                [bjerrum_length #float] [stencil <linkcentered|nonlinear|nodecentered>]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                [advection <on|off>] [fluid-coupling <friction|estatics>]\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics print <density|velocity|potential|boundary|pressure|lbforce|reaction_tags> vtk #string\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics print net_charge\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics node #int #int #int print <velocity>\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics reaction [reactant_index #int]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [product0_index #int]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [product1_index #int]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [reactant_resrv_density #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [product0_resrv_density #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [product1_resrv_density #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [reaction_rate #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [mass_reactant #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [mass_product0 #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [mass_product1 #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [reaction_fraction_pr_0 #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                         [reaction_fraction_pr_1 #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics reaction region #int [box]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [wall ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [sphere ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [cylinder ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [rhomboid ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [pore ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [stomatocyte ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                     [hollow_cone ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics boundary charge_density #float [wall ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [sphere ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [cylinder ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [rhomboid ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [pore ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [stomatocyte ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [hollow_cone ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                                               [spherocylinder ... (c.f. constraint command)]\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics #int [density #float] [D #float] [valency #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                     [ext_force #float #float #float]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                     [print density vtk #string]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                     [print flux vtk #string]\n", (char *)NULL);
    Tcl_AppendResult(interp, "                     [neutralize_system]\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics #int node #int #int #int set density\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics #int node #int #int #int print <density|flux>\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics pdb-parse #string #string #double\n", (char *)NULL);
    Tcl_AppendResult(interp, "electrokinetics checkpoint <save|load> #string\n", (char *)NULL);
    return TCL_ERROR;
  }
  else if(ARG0_IS_S("checkpoint"))
  {
    argc--;
    argv++;

    if(argc != 2 || (!ARG0_IS_S("save") && !ARG0_IS_S("load")))
    {
      Tcl_AppendResult(interp, "Wrong usage of electrokinetics checkpoint <save|load> #filename\n", (char *) NULL);
      return TCL_ERROR;
    }

    if(ARG0_IS_S("save"))
    {
      argc--;
      argv++;

      if(ek_save_checkpoint(argv[0]) != 0)
      {
        Tcl_AppendResult(interp, "Error saving EK checkpoint\n", (char *) NULL);
        return TCL_ERROR;
      }
    }
    else if(ARG0_IS_S("load"))
    {
      argc--;
      argv++;

      if(ek_load_checkpoint(argv[0]) != 0)
      {
        Tcl_AppendResult(interp, "Error loading EK checkpoint\n", (char *) NULL);
        return TCL_ERROR;
      }
    }

    return TCL_OK;
  }
  else if(ARG0_IS_S("pdb-parse"))
  {
#ifndef EK_BOUNDARIES
    Tcl_AppendResult(interp, "Feature EK_BOUNDARIES required", (char *) NULL);
    return (TCL_ERROR);
#else
    argc--;
    argv++;

    if ((argc != 3) || !ARG_IS_D(2, floatarg))
    {
      Tcl_AppendResult(interp, "You need to specify two filenames.\n", (char *) NULL);
      Tcl_AppendResult(interp, "electrokinetics pdb-parse #string1 #string2 #double\n", (char *)NULL);
      Tcl_AppendResult(interp, "#string1 is the pdb-filename, #string2 is the itp-filename #double is the length unit used in you simulation.\n", (char *)NULL);
    }
    if (!ek_initialized)
    {
      Tcl_AppendResult(interp, "Please initialize EK before you attempt parsing.", (char *) NULL);
      return (TCL_ERROR);
    }
    if(pdb_parse(argv[0], argv[1], floatarg) != 0)
    {
      Tcl_AppendResult(interp, "Could not parse pdb- or itp-file. Please, check your format and filenames.", (char *) NULL);
      return (TCL_ERROR);
    }
    lb_init_boundaries();
#endif
  }
  else if(ARG0_IS_S("boundary")) 
  {
#ifndef EK_BOUNDARIES
    Tcl_AppendResult(interp, "Feature EK_BOUNDARIES required", (char *) NULL);
    return (TCL_ERROR);
#else
    argc--;
    argv++;
    
    if((!ARG0_IS_S("charge_density") && !ARG0_IS_S("net_charge")) || !ARG1_IS_D(floatarg)) 
    {
      Tcl_AppendResult(interp, "You need to specify the boundary charge using\n", (char *) NULL);
      Tcl_AppendResult(interp, "electrokinetics boundary <charge_density|net_charge> #float ...\n", (char *)NULL);
      return (TCL_ERROR);
    }

    bool net_charge_specified;

    if(ARG0_IS_S("charge_density"))
      net_charge_specified = 0;
    else
      net_charge_specified = 1;
    
    argc -= 2;
    argv += 2;
    
    if(floatarg != 0.0) 
    {
      species = -1;
      
      for(unsigned int i = 0; i < ek_parameters.number_of_species; i++)
        if(ek_parameters.valency[i] != 0.0) 
        {
          species = i;
          break;
        }
      
      if(species == -1) 
      {
        Tcl_AppendResult(interp, "You need to define at least one charged species in order to use charged walls\n", (char *) NULL);
        return (TCL_ERROR);
      }
    }
    
    int c_num;
    LB_Boundary *lbboundary_tmp;
    
    if(ARG0_IS_S("wall")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_wall(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("sphere")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_sphere(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("cylinder")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_cylinder(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("rhomboid")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_rhomboid(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("pore")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_pore(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("stomatocyte")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_stomatocyte(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("hollow_cone")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_hollow_cone(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("spherocylinder")) 
    {
      lbboundary_tmp = generate_lbboundary();
      err = tclcommand_lbboundary_spherocylinder(lbboundary_tmp, interp, argc - 1, argv + 1);
      lbboundary_tmp->charge_density = floatarg;
      lbboundary_tmp->net_charge = 0.0;
    }
    else if(ARG0_IS_S("delete")) 
    {
      if(argc < 3) 
      {
        /* delete all */
        Tcl_AppendResult(interp, "Can only delete individual electrokinetics boundaries", (char *) NULL);
        return (TCL_ERROR);
      }
      else 
      {
        if(Tcl_GetInt(interp, argv[2], &(c_num)) == TCL_ERROR)
          return (TCL_ERROR);
          
        if(c_num < 0 || c_num >= n_lb_boundaries) 
        {
	        Tcl_AppendResult(interp, "Can not delete non existing electrokinetics boundary", (char *) NULL);
	        return (TCL_ERROR);
        }

        Tcl_AppendResult(interp, "electrokinetics boundary delete not implemented", (char *) NULL);
        return (TCL_ERROR);
      }
    }
    else 
    {
      Tcl_AppendResult(interp, "possible electrokinetics boundary charge_density #float parameters:", (char *) NULL); 
      Tcl_AppendResult(interp, "wall, sphere, cylinder, rhomboid, pore, stomatocyte, hollow_cone, spherocylinder, delete {c} to delete a boundary", (char *) NULL);
      return (TCL_ERROR);
    }
        
    on_lbboundary_change();

    if(net_charge_specified && floatarg != 0.0)
    {
      lbboundary_tmp->charge_density *= floatarg / lbboundary_tmp->net_charge;
      on_lbboundary_change();
    }
#endif /* EK_BOUNDARIES */
  }
  else if(ARG0_IS_I(species)) 
  {
    argc--;
    argv++;
    
    if(species < 0 || species > MAX_NUMBER_OF_SPECIES) 
    {
      sprintf(int_buffer, "%d", MAX_NUMBER_OF_SPECIES);
      Tcl_AppendResult(interp, "electrokinetics #int requires a number between 0 and", int_buffer, "denoting the species\n", (char *)NULL);
      return TCL_ERROR;
    }
    
    while(argc > 0) 
    {
      if(ARG0_IS_S("D")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int D requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg < 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int D can not be negative\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_D(species, floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics #int D\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("density")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int density requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg < 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int density must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_density(species, floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics #int density\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("ext_force")) 
      {
        if(argc < 4 || !ARG_IS_D(1, vectarg[0]) || !ARG_IS_D(2, vectarg[1]) || !ARG_IS_D(3, vectarg[2])) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int ext_force requires three floating point numbers as arguments\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(ek_set_ext_force(species, vectarg[0], vectarg[1], vectarg[2]) == 0) 
        {
          argc -= 4;
          argv += 4;
        }
        else 
        {
          Tcl_AppendResult(interp, "Unknown error setting electrokinetics #int ext_force\n", (char *)NULL);
          return TCL_ERROR;
        }
      }
      else if(ARG0_IS_S("valency")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics #int valency requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_valency(species, floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics #int valency\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("node")) 
      {
        argc--;
        argv++;
        
        if( (argc != 5 && argc != 6) ||
            !ARG_IS_I(0, coord[0]) || !ARG_IS_I(1, coord[1]) || !ARG_IS_I(2, coord[2]) ||
            (ARG_IS_S(3, "print") && (!ARG_IS_S(4, "density") && !ARG_IS_S(4, "flux"))) ||
            (ARG_IS_S(3, "set") && (!ARG_IS_S(4, "density")))
          ) 
        {
          Tcl_AppendResult(interp, "Wrong usage of electrokinetics #int node #int #int #int <set density #int|print <density|flux>>\n", (char *)NULL);
          return TCL_ERROR;
        }
        
        argc -= 3;
        argv += 3;
        
        if(ARG0_IS_S("set"))
        {
          argc--;
          argv++;

          if(ARG0_IS_S("density")) 
          {
            argc--;
            argv++;

            if(!ARG0_IS_D(floatarg))
            {
              Tcl_AppendResult(interp, "Wrong usage of electrokinetics #int node #int #int #int set density #float\n", (char *)NULL);
              return TCL_ERROR;
            }
            
            argc--;
            argv++;

            if(ek_node_set_density(species, coord[0], coord[1], coord[2], floatarg) != 0) 
            {
              Tcl_AppendResult(interp, "Unknown error in electrokinetics #int node #int #int #int set density\n", (char *)NULL);
              return TCL_ERROR;
            }
            else
              return TCL_OK;
          }
          else
          {
              Tcl_AppendResult(interp, "Wrong usage of electrokinetics #int node #int #int #int <set|print> density\n", (char *)NULL);
              return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("print"))
        {
          argc--;
          argv++;

          if(ARG0_IS_S("density")) 
          {
            if(ek_node_print_density(species, coord[0], coord[1], coord[2], &floatarg) == 0) 
            {
              argc --;
              argv ++;
              
              Tcl_PrintDouble(interp, floatarg, double_buffer);
              Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);

              if((err = gather_runtime_errors(interp, err)) != TCL_OK)
                return TCL_ERROR;
              else
                return TCL_OK;
            }
            else 
            {
              Tcl_AppendResult(interp, "Unknown error in electrokinetics #int node #int #int #int print density\n", (char *)NULL);
              return TCL_ERROR;
            }
          }
          else if(ARG0_IS_S("flux")) 
          {
            if(ek_node_print_flux(species, coord[0], coord[1], coord[2], vectarg) == 0) 
            {
              argc --;
              argv ++;
              
              Tcl_PrintDouble(interp, vectarg[0], double_buffer);
              Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);
              Tcl_PrintDouble(interp, vectarg[1], double_buffer);
              Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);
              Tcl_PrintDouble(interp, vectarg[2], double_buffer);
              Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);

              if((err = gather_runtime_errors(interp, err)) != TCL_OK)
                return TCL_ERROR;
              else
                return TCL_OK;
            }
            else 
            {
              Tcl_AppendResult(interp, "Unknown error in electrokinetics #int node #int #int #int print flux\n", (char *)NULL);
              return TCL_ERROR;
            }
          } 
          else
          {
              Tcl_AppendResult(interp, "Wrong usage of electrokinetics #int node #int #int #int <set|print> density\n", (char *)NULL);
              return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("print")) 
      {
        argc--;
        argv++;
        
        if(argc != 3 || !ARG1_IS_S("vtk") || ( !ARG0_IS_S("density") && !ARG0_IS_S("flux") ) ) 
        {
          Tcl_AppendResult(interp, "Wrong usage of electrokinetics #int print <density|flux> vtk #string\n", (char *)NULL);
          return TCL_ERROR;
        }
        
        if(ARG0_IS_S("density")) 
        {
          if(ek_print_vtk_density(species, argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics #int print density vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("flux")) 
        {
          if(ek_print_vtk_flux(species, argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics #int print flux vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("neutralize_system"))
      {
        err = ek_neutralize_system(species);

        if(err == 0) 
        {
          argc --;
          argv ++;
        }
        else if(err == 1)
        {
          Tcl_AppendResult(interp, "Species used for neutralization must exist in electrokinetics #int neutralize_system\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(err == 2)
        {
          Tcl_AppendResult(interp, "Species used for neutralization must be charged in electrokinetics #int neutralize_system\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(err == 3)
        {
          Tcl_AppendResult(interp, "Neutralization with specified species would result in negative density in electrokinetics #int neutralize_system\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          Tcl_AppendResult(interp, "Unknown error in electrokinetics #int neutralize_system\n", (char *)NULL);
          return TCL_ERROR;
        }
      }
      else 
      {
    	  Tcl_AppendResult(interp, "unknown feature \"", argv[0],"\" of electrokinetics #int\n", (char *)NULL);
    	  return TCL_ERROR ;
      }
    }
  }
  else 
  {
    Tcl_ResetResult(interp);
    
    while(argc > 0) 
    {
      if(ARG0_IS_S("print")) 
      {
        argc--;
        argv++;
       
        if(argc == 1 && ARG0_IS_S("net_charge"))
        {
          argc--;
          argv++;

          float net_charge = ek_calculate_net_charge();
          Tcl_PrintDouble(interp, net_charge, double_buffer);
          Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);
          return TCL_OK;
        }

        if (
             argc != 3 || !ARG1_IS_S("vtk") || 
             ( !ARG0_IS_S("velocity") && !ARG0_IS_S("density") &&
               !ARG0_IS_S("boundary") && !ARG0_IS_S("potential") &&
               !ARG0_IS_S("pressure") && !ARG0_IS_S("lbforce") &&
               !ARG0_IS_S("lbforce_buf") && !ARG0_IS_S("reaction_tags") &&
	       !ARG0_IS_S("particle_potential")
             )
           ) 
        {
          Tcl_AppendResult(interp, "Wrong usage of electrokinetics print <net_charge | <velocity|density|potential|pressure|reaction_tags> vtk #string>\n", (char *)NULL);
          return TCL_ERROR;
        }
        
        if(ARG0_IS_S("velocity")) 
        {
          if(ek_lb_print_vtk_velocity(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print velocity vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("density")) 
        {
          if(ek_lb_print_vtk_density(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print density vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("boundary")) 
        {
#ifndef EK_BOUNDARIES
          Tcl_AppendResult(interp, "Feature EK_BOUNDARIES required", (char *) NULL);
          return (TCL_ERROR);
#else
          if(lb_lbfluid_print_vtk_boundary(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print boundary vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
#endif /* EK_BOUNDARIES */
        }
        else if(ARG0_IS_S("particle_potential")) 
        {
#ifndef EK_ELECTROSTATIC_COUPLING
          Tcl_AppendResult(interp, "Feature EK_ELECTROSTATIC_COUPLING required", (char *) NULL);
          return (TCL_ERROR);
#else
          if(ek_print_vtk_particle_potential(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
#endif
	}
        else if(ARG0_IS_S("potential")) 
        {
          if(ek_print_vtk_potential(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print lbforce vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("pressure")) 
        {
#ifndef EK_REACTION
          Tcl_AppendResult(interp, "Feature EK_REACTION required", (char *) NULL);
          return (TCL_ERROR);
#else
          if( ek_parameters.number_of_species < 3 ||
              ( ek_parameters.reaction_species[0] == -1 ||
                ek_parameters.reaction_species[1] == -1 ||
                ek_parameters.reaction_species[2] == -1 )
            )
          {
            Tcl_AppendResult(interp, "The reaction must be set up to use this command\n", (char *) NULL);
            return (TCL_ERROR);
          }

          if(ek_print_vtk_pressure(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print pressure vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
#endif /* EK_PRESSURE */
        }
        else if(ARG0_IS_S("reaction_tags")) 
        {
#ifndef EK_REACTION
          Tcl_AppendResult(interp, "Feature EK_REACTION required", (char *) NULL);
          return (TCL_ERROR);
#else
          if( ek_parameters.number_of_species < 3 ||
              ( ek_parameters.reaction_species[0] == -1 ||
                ek_parameters.reaction_species[1] == -1 ||
                ek_parameters.reaction_species[2] == -1 )
            )
          {
            Tcl_AppendResult(interp, "The reaction must be set up to use this command\n", (char *) NULL);
            return (TCL_ERROR);
          }

          if(ek_print_vtk_reaction_tags(argv[2]) == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print reaction_tags vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
#endif /* EK_PRESSURE */
        }
        else if(ARG0_IS_S("lbforce")) 
        {
          int ret = ek_print_vtk_lbforce(argv[2]);
          if(ret == 0) 
          {
            argc -= 3;
            argv += 3;

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else if (ret == 1)
          {
            Tcl_AppendResult(interp, "Feature EK_DEBUG required\n", (char *)NULL);
            return TCL_ERROR;
          }
          else
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics print lbforce vtk #string\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else 
        {
            Tcl_AppendResult(interp, "Unknown feature \"", argv[0], "\" in electrokinetics print\n", (char *)NULL);
            return TCL_ERROR;
        }
      }
      else if(ARG0_IS_S("node")) 
      {
        argc--;
        argv++;
        
        if ( 
             argc != 5 || !ARG_IS_I(0, coord[0]) ||
             !ARG_IS_I(1, coord[1]) || !ARG_IS_I(2, coord[2]) ||
             !ARG_IS_S(3, "print") || !ARG_IS_S(4, "velocity")
           ) 
        {
          Tcl_AppendResult(interp, "Wrong usage of electrokinetics node print <velocity|flux>\n", (char *)NULL);
          return TCL_ERROR;
        }
        
        argc -= 4;
        argv += 4;
        
        if(ARG0_IS_S("velocity")) 
        {
          if(ek_node_print_velocity(coord[0], coord[1], coord[2], vectarg) == 0) 
          {
            argc --;
            argv ++;
            
            Tcl_PrintDouble(interp, vectarg[0], double_buffer);
            Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);
            Tcl_PrintDouble(interp, vectarg[1], double_buffer);
            Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);
            Tcl_PrintDouble(interp, vectarg[2], double_buffer);
            Tcl_AppendResult(interp, double_buffer, " ", (char *) NULL);

            if((err = gather_runtime_errors(interp, err)) != TCL_OK)
              return TCL_ERROR;
            else
              return TCL_OK;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error in electrokinetics node print velocity\n", (char *)NULL);
            return TCL_ERROR;
          }
        } 
      }
      else if(ARG0_IS_S("T")) 
      {
        argc--;
        argv++;
        
        if(argc < 1 || !ARG0_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics T requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics T must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_T(floatarg) == 0) 
          {
            argc --;
            argv ++;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics T\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("bjerrum_length")) 
      {
        argc--;
        argv++;
      
        if(!ARG0_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics bjerrum_length requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics bjerrum_length must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_bjerrumlength(floatarg) == 0) 
          {
            argc--;
            argv++;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics bjerrum_length\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
#ifdef EK_ELECTROSTATIC_COUPLING
      else if(ARG0_IS_S("electrostatics_coupling"))
        {
          argc--;
          argv++;
          ek_set_electrostatics_coupling(true);
        }
#endif
      else if(ARG0_IS_S("agrid")) 
      {
        argc--;
        argv++;
      
        if(!ARG0_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics agrid requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics agrid must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_agrid(floatarg) == 0) 
          {
            argc--;
            argv++;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics agrid\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("lb_force")) 
      {
        argc--;
        argv++;
        
#ifndef EXTERNAL_FORCES
        Tcl_AppendResult(interp, "External Forces not compiled in!", (char *)NULL);
        return TCL_ERROR;
#endif

        if(argc < 3 || !ARG_IS_D(0,vectarg[0]) || !ARG_IS_D(1,vectarg[1]) || !ARG_IS_D(2,vectarg[2])) 
        {
          Tcl_AppendResult(interp, "electrokinetics lb_force requires three floating point numbers as arguments\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_lb_force(vectarg) == 0) 
          {
            argc-=3;
            argv+=3;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics lb_force\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("lb_density")) 
      {
        argc--;
        argv++;
      
        if(!ARG0_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics lb_density requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics lb_density must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_lb_density(floatarg) == 0) 
          {
            argc--;
            argv++;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics lb_density\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("viscosity")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics viscosity requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        } 
        else if (floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics viscosity must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_viscosity(floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics viscosity\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("friction")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics friction requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics friction must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if (ek_set_friction(floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics friction\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("bulk_viscosity")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics bulk_viscosity requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(floatarg <= 0) 
        {
          Tcl_AppendResult(interp, "electrokinetics bulk_viscosity must be positive\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_bulk_viscosity(floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics bulk_viscosity\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("gamma_odd")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics gamma_odd requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(fabs(floatarg) >= 1) 
        {
          Tcl_AppendResult(interp, "electrokinetics gamma_odd must be smaller than 1\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_gamma_odd(floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics gamma_odd\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("gamma_even")) 
      {
        if(argc < 2 || !ARG1_IS_D(floatarg)) 
        {
          Tcl_AppendResult(interp, "electrokinetics gamma_even requires one floating point number as argument\n", (char *)NULL);
          return TCL_ERROR;
        }
        else if(fabs(floatarg) >= 1) 
        {
          Tcl_AppendResult(interp, "electrokinetics gamma_even must be smaller than 1\n", (char *)NULL);
          return TCL_ERROR;
        }
        else 
        {
          if(ek_set_gamma_even(floatarg) == 0) 
          {
            argc -= 2;
            argv += 2;
          }
          else 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics gamma_even\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
      }
      else if(ARG0_IS_S("reaction")) 
      {
#ifndef EK_REACTION
        Tcl_AppendResult(interp, "EK_REACTION needs to be compiled in to use electrokinetics reaction\n", (char *)NULL);
        return TCL_ERROR;
#else
        argc--;
        argv++;

        if( ARG0_IS_S("region") )
        {
#ifndef EK_BOUNDARIES
          Tcl_AppendResult(interp, "Feature EK_BOUNDARIES required", (char *) NULL);
          return (TCL_ERROR);
#else
          if(ek_parameters.number_of_species < 3) 
          {
            Tcl_AppendResult(interp, "to invoke the reaction command 3 species must first be set\n", (char *) NULL);
            return (TCL_ERROR);
          }

          if ( ek_parameters.reaction_species[0] == -1 ||
               ek_parameters.reaction_species[1] == -1 ||
               ek_parameters.reaction_species[2] == -1 )
          {
            Tcl_AppendResult(interp, "You need to set up the reaction first,\n", (char *) NULL);
            Tcl_AppendResult(interp, "before you can tag the reactive regions", (char *) NULL);
            return (TCL_ERROR);
          }

          argc--;
          argv++;

          int reaction_type;
          LB_Boundary lbboundary_tmp;

          if( !ARG0_IS_I(reaction_type) ) 
          {
            Tcl_AppendResult(interp, "\nYou need to specify the reaction type you want to use\n", (char *) NULL);
            Tcl_AppendResult(interp, "\nelectrokinetics reaction region #int ...\n", (char *)NULL);
            return (TCL_ERROR);
          }         

          if ( reaction_type != 0 &&
               reaction_type != 1 &&
               reaction_type != 2 )
          {
            Tcl_AppendResult(interp, "Not a valid choice for the type, choose from:\n", (char *) NULL);
            Tcl_AppendResult(interp, "(0) no reaction, (1) reaction, (2) reservoir\n", (char *) NULL);
            return (TCL_ERROR);
          }

          argc--;
          argv++;

          if(ARG0_IS_S("box")) 
          {
            err = tclcommand_lbboundary_box(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }          
          else if(ARG0_IS_S("wall")) 
          {
            err = tclcommand_lbboundary_wall(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("sphere")) 
          {
            err = tclcommand_lbboundary_sphere(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("cylinder")) 
          {
            err = tclcommand_lbboundary_cylinder(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("rhomboid")) 
          {
            err = tclcommand_lbboundary_rhomboid(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("pore")) 
          {
            err = tclcommand_lbboundary_pore(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("stomatocyte")) 
          {
            err = tclcommand_lbboundary_stomatocyte(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("hollow_cone")) 
          {
            err = tclcommand_lbboundary_hollow_cone(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else if(ARG0_IS_S("spherocylinder")) 
          {
            err = tclcommand_lbboundary_spherocylinder(&lbboundary_tmp, interp, argc - 1, argv + 1);
          }
          else 
          {
            Tcl_AppendResult(interp, "possible electrokinetics reaction region #int parameters:\n", (char *) NULL);
            Tcl_AppendResult(interp, "box, wall, sphere, cylinder, rhomboid, pore, stomatocyte, hollow_cone, spherocylinder", (char *) NULL);
            return (TCL_ERROR);
          }

          ek_tag_reaction_nodes( &lbboundary_tmp, char(reaction_type) ); 

          return TCL_OK;
#endif
        }
        else
        { 
          if(ek_parameters.number_of_species < 3) 
          {
            Tcl_AppendResult(interp, "to invoke the reaction command 3 species must first be set\n", (char *) NULL);
            return (TCL_ERROR);
          }

          if( argc < 22 )
          {
            Tcl_AppendResult(interp, "electrokinetics reaction requires 15 arguments:\n", (char *) NULL);
            Tcl_AppendResult(interp, "11 quantifiers, 3 ints, and 8 floats\n", (char *)NULL);
            return TCL_ERROR;
          }
          else
          {

            int counter = 0;

            while(argc > 0 && counter < 13 ) 
            {
              counter++;

              if ( ARG_IS_S_EXACT(0,"reactant_index") ) 
              {

                if ( !ARG_IS_I(1, reactant) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics reactant_index requires one int as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( (reactant < 0 || reactant > MAX_NUMBER_OF_SPECIES) ) 
                {
                  sprintf(int_buffer, "%d", MAX_NUMBER_OF_SPECIES);
                  Tcl_AppendResult(interp, "electrokinetics reactant_index #int requires a number between 0 and", int_buffer, "denoting the species\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if( ARG_IS_S_EXACT(0,"product0_index") )
              {

                if ( !ARG_IS_I(1, product0) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics product0_index requires one int as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( (product0 < 0 || product0 > MAX_NUMBER_OF_SPECIES) ) 
                {
                  sprintf(int_buffer, "%d", MAX_NUMBER_OF_SPECIES);
                  Tcl_AppendResult(interp, "electrokinetics product0_index #int requires a number between 0 and", int_buffer, "denoting the species\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if ( ARG_IS_S_EXACT(0,"product1_index") ) 
              {

                if ( !ARG_IS_I(1, product1) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics product1_index requires one int as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( (product1 < 0 || product1 > MAX_NUMBER_OF_SPECIES) ) 
                {
                  sprintf(int_buffer, "%d", MAX_NUMBER_OF_SPECIES);
                  Tcl_AppendResult(interp, "electrokinetics product1_index #int requires a number between 0 and", int_buffer, "denoting the species\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if ( ARG_IS_S_EXACT(0,"reactant_resrv_density") ) 
              {

                if ( !ARG_IS_D(1, rho_reactant_reservoir) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics reactant_resrv_density requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( rho_reactant_reservoir < 0 ) 
                {
                  Tcl_AppendResult(interp, "the reactant reservoir density has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"product0_resrv_density")) 
              {

                if ( !ARG_IS_D(1, rho_product0_reservoir) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics product0_resrv_density requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( rho_product0_reservoir < 0 ) 
                {
                  Tcl_AppendResult(interp, "the product0 reservoir density has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if ( ARG_IS_S_EXACT(0,"product1_resrv_density") ) 
              {

                if (!ARG_IS_D(1, rho_product1_reservoir)) 
                {
                  Tcl_AppendResult(interp, "electrokinetics product1_resrv_density requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( rho_product1_reservoir < 0 ) 
                {
                  Tcl_AppendResult(interp, "the product1 reservoir density has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if ( ARG_IS_S_EXACT(0,"reaction_rate") ) 
              {

                if ( !ARG_IS_D(1, ct_rate) ) 
                {
                  Tcl_AppendResult(interp, "electrokinetics reaction_rate requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( ct_rate < 0 ) 
                {
                  Tcl_AppendResult(interp, "catalytic reaction rate has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"mass_reactant")) 
              {

                if ( !ARG_IS_D(1, mass_reactant) )
                {
                  Tcl_AppendResult(interp, "electrokinetics mass_reactant requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( mass_reactant <= 0 ) 
                {
                  Tcl_AppendResult(interp, "the mass has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"mass_product0")) 
              {

                if ( !ARG_IS_D(1, mass_product0) )
                {
                  Tcl_AppendResult(interp, "electrokinetics mass_product0 requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( mass_product0 <= 0 ) 
                {
                  Tcl_AppendResult(interp, "the mass has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"mass_product1")) 
              {

                if ( !ARG_IS_D(1, mass_product1) )
                {
                  Tcl_AppendResult(interp, "electrokinetics mass_product1 requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( mass_product1 <= 0 ) 
                {
                  Tcl_AppendResult(interp, "the mass has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"reaction_fraction_pr_0")) 
              {

                if ( !ARG_IS_D(1, fraction0) )
                {
                  Tcl_AppendResult(interp, "electrokinetics reaction_fraction_pr_0 requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( fraction0 < 0 ) 
                {
                  Tcl_AppendResult(interp, "the fraction has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }

              else if (ARG_IS_S_EXACT(0,"reaction_fraction_pr_1")) 
              {

                if ( !ARG_IS_D(1, fraction1) )
                {
                  Tcl_AppendResult(interp, "electrokinetics reaction_fraction_pr_1 requires one floating point number as argument\n", (char *)NULL);
                  return TCL_ERROR;
                }

                if ( fraction1 < 0 ) 
                {
                  Tcl_AppendResult(interp, "the fraction has to be greater than zero\n", (char *)NULL);
                  return TCL_ERROR;
                }

                argc -= 2;
                argv += 2;
              }
            }

            if ( counter == 13 )
            {
              Tcl_AppendResult(interp, "unknown option given, please check for spelling errors\n", (char *)NULL);
              return TCL_ERROR;
            }

            if ( (reactant == product0) ||
                 (product0 == product1) ||
                 (product1 == reactant) ) 
            {
              Tcl_AppendResult(interp, "the reactant and product species need to be distinct\n", (char *)NULL);
              return TCL_ERROR;
            }     

            if ( fabs( fraction0*mass_product0 + fraction1*mass_product1 - mass_reactant ) > 1.0e-06  ) 
            {
              Tcl_AppendResult(interp, "the reaction does not conserve mass:\n", (char *)NULL);
              Tcl_AppendResult(interp, "please choose different masses or fractions\n", (char *)NULL);
              return TCL_ERROR;
            }       

            if ( ek_set_reaction( reactant, product0, product1, 
                                  rho_reactant_reservoir, rho_product0_reservoir, rho_product1_reservoir, 
                                  ct_rate, fraction0, fraction1, 
                                  mass_reactant, mass_product0, mass_product1 ) != 0 ) 
            {
              Tcl_AppendResult(interp, "species are not set before invoking electrokinetics reaction\n", (char *)NULL);
              return TCL_ERROR;
            }  
          }
        }     
#endif 
      }
      else if(ARG0_IS_S("stencil")) {
        argc--;
        argv++;

        if(argc < 1 || (!ARG0_IS_S("linkcentered") && !ARG0_IS_S("nonlinear") && !ARG0_IS_S("nodecentered")) ) 
        {
          Tcl_AppendResult(interp, "wrong usage of electrokinetics stencil <linkcentered|nonlinear|nodecentered>\n", (char *)NULL);
          return TCL_ERROR;
        }

        if(ARG0_IS_S("nonlinear")) {
          if(ek_set_stencil(1) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics stencil\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("nodecentered")) {
          if(ek_set_stencil(2) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics stencil\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else {
          if(ek_set_stencil(0) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics stencil\n", (char *)NULL);
            return TCL_ERROR;
          }
        }

        argc--;
        argv++;
      }
      else if(ARG0_IS_S("advection")) {
        argc--;
        argv++;

        if(argc < 1)
        {
          Tcl_AppendResult(interp, "wrong usage of electrokinetics advection <on|off>\n", (char *)NULL);
          return TCL_ERROR;
        }

        if(ARG0_IS_S("on")) {
          if(ek_set_advection(true) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics advection\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("off")) {
          if(ek_set_advection(false) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics advection\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else
        {
          Tcl_AppendResult(interp, "wrong usage of electrokinetics advection <on|off>\n", (char *)NULL);
          return TCL_ERROR;
        }

        argc--;
        argv++;
      }
      else if(ARG0_IS_S("fluid-coupling")) {
        argc--;
        argv++;

        if(argc < 1)
        {
          Tcl_AppendResult(interp, "wrong usage of electrokinetics fluid-coupling <friction|estatics>\n", (char *)NULL);
          return TCL_ERROR;
        }

        if(ARG0_IS_S("friction")) {
          if(ek_set_fluidcoupling(true) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics fluid-coupling\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else if(ARG0_IS_S("estatics")) {
          if(ek_set_fluidcoupling(false) != 0) 
          {
            Tcl_AppendResult(interp, "Unknown error setting electrokinetics fluid-coupling\n", (char *)NULL);
            return TCL_ERROR;
          }
        }
        else
        {
          Tcl_AppendResult(interp, "wrong usage of electrokinetics fluid-coupling <friction|estatics>\n", (char *)NULL);
          return TCL_ERROR;
        }

        argc--;
        argv++;
      }
      else 
      {
    	  Tcl_AppendResult(interp, "unknown feature \"", argv[0],"\" of electrokinetics\n", (char *)NULL);
    	  return TCL_ERROR ;
      }
    }
  }

  if((err = gather_runtime_errors(interp, err)) != TCL_OK)
    return TCL_ERROR;

  err = ek_init();

  switch(err) 
  {
    case 0:
      return TCL_OK;
      
    case 2:
      Tcl_AppendResult(interp, "electrokinetics agrid not compatible with box size\n", (char *)NULL);
      
    default:
      sprintf(int_buffer, "%d", err);
      Tcl_AppendResult(interp, "Error ", int_buffer, " during initialization of electrokinetics", (char *)NULL);
      break;
  }
  
  return TCL_ERROR;
  
#endif /* defined ELECTROKINETICS */
}
