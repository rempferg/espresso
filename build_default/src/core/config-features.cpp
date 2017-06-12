/* 
WARNING: This file was autogenerated by

   /Users/bindgens2/Documents/espresso_dev/espresso/src/core/gen_featureconfig.py 
   on 
   Wed Jun  7 12:39:03 2017

   Do not modify it or your changes will be overwritten!
   Modify features.def instead.
*/

/* config.hpp includes config-features.hpp and myconfig.hpp */
#include "config.hpp"

/* Handle requirements */
// MODES requires FFTW
#if defined(MODES) && !(defined(FFTW))
#error Feature MODES requires FFTW
#endif

// LEES_EDWARDS requires not ELECTROSTATICS and not LB and not PARTIAL_PERIODIC
#if defined(LEES_EDWARDS) && !( ! defined(ELECTROSTATICS)  &&   ! defined(LB)  &&   ! defined(PARTIAL_PERIODIC))
#error Feature LEES_EDWARDS requires not ELECTROSTATICS and not LB and not PARTIAL_PERIODIC
#endif

// MULTI_TIMESTEP requires not GAUSSRANDOMCUT and not GAUSSRANDOM
#if defined(MULTI_TIMESTEP) && !( ! defined(GAUSSRANDOMCUT)  &&   ! defined(GAUSSRANDOM))
#error Feature MULTI_TIMESTEP requires not GAUSSRANDOMCUT and not GAUSSRANDOM
#endif

// BOND_CONSTRAINT requires not ROTATION
#if defined(BOND_CONSTRAINT) && !( ! defined(ROTATION))
#error Feature BOND_CONSTRAINT requires not ROTATION
#endif

// MMM1D_GPU requires CUDA and PARTIAL_PERIODIC and ELECTROSTATICS
#if defined(MMM1D_GPU) && !(defined(CUDA)  &&  defined(PARTIAL_PERIODIC)  &&  defined(ELECTROSTATICS))
#error Feature MMM1D_GPU requires CUDA and PARTIAL_PERIODIC and ELECTROSTATICS
#endif

// EWALD_GPU requires CUDA and ELECTROSTATICS
#if defined(EWALD_GPU) && !(defined(CUDA)  &&  defined(ELECTROSTATICS))
#error Feature EWALD_GPU requires CUDA and ELECTROSTATICS
#endif

// _P3M_GPU_FLOAT requires CUDA and ELECTROSTATICS
#if defined(_P3M_GPU_FLOAT) && !(defined(CUDA)  &&  defined(ELECTROSTATICS))
#error Feature _P3M_GPU_FLOAT requires CUDA and ELECTROSTATICS
#endif

// _P3M_GPU_DOUBLE requires CUDA and ELECTROSTATICS
#if defined(_P3M_GPU_DOUBLE) && !(defined(CUDA)  &&  defined(ELECTROSTATICS))
#error Feature _P3M_GPU_DOUBLE requires CUDA and ELECTROSTATICS
#endif

// DIPOLAR_DIRECT_SUM requires CUDA
#if defined(DIPOLAR_DIRECT_SUM) && !(defined(CUDA))
#error Feature DIPOLAR_DIRECT_SUM requires CUDA
#endif

// VIRTUAL_SITES_COM requires not VIRTUAL_SITES_RELATIVE
#if defined(VIRTUAL_SITES_COM) && !( ! defined(VIRTUAL_SITES_RELATIVE))
#error Feature VIRTUAL_SITES_COM requires not VIRTUAL_SITES_RELATIVE
#endif

// VIRTUAL_SITES_RELATIVE requires not VIRTUAL_SITES_COM
#if defined(VIRTUAL_SITES_RELATIVE) && !( ! defined(VIRTUAL_SITES_COM))
#error Feature VIRTUAL_SITES_RELATIVE requires not VIRTUAL_SITES_COM
#endif

// DPD_MASS_RED requires not DPD_MASS_LIN
#if defined(DPD_MASS_RED) && !( ! defined(DPD_MASS_LIN))
#error Feature DPD_MASS_RED requires not DPD_MASS_LIN
#endif

// DPD_MASS_LIN requires not DPD_MASS_RED
#if defined(DPD_MASS_LIN) && !( ! defined(DPD_MASS_RED))
#error Feature DPD_MASS_LIN requires not DPD_MASS_RED
#endif

// LB_GPU requires CUDA
#if defined(LB_GPU) && !(defined(CUDA))
#error Feature LB_GPU requires CUDA
#endif

// ELECTROKINETICS requires CUDA
#if defined(ELECTROKINETICS) && !(defined(CUDA))
#error Feature ELECTROKINETICS requires CUDA
#endif

// EK_BOUNDARIES requires CUDA
#if defined(EK_BOUNDARIES) && !(defined(CUDA))
#error Feature EK_BOUNDARIES requires CUDA
#endif

// EK_REACTION requires CUDA
#if defined(EK_REACTION) && !(defined(CUDA))
#error Feature EK_REACTION requires CUDA
#endif

// EK_ELECTROSTATIC_COUPLING requires CUDA and FFTW
#if defined(EK_ELECTROSTATIC_COUPLING) && !(defined(CUDA)  &&  defined(FFTW))
#error Feature EK_ELECTROSTATIC_COUPLING requires CUDA and FFTW
#endif

// EK_DEBUG requires ELECTROKINETICS
#if defined(EK_DEBUG) && !(defined(ELECTROKINETICS))
#error Feature EK_DEBUG requires ELECTROKINETICS
#endif

// EK_DOUBLE_PREC requires ELECTROKINETICS
#if defined(EK_DOUBLE_PREC) && !(defined(ELECTROKINETICS))
#error Feature EK_DOUBLE_PREC requires ELECTROKINETICS
#endif

// SHANCHEN requires not ELECTROKINETICS
#if defined(SHANCHEN) && !( ! defined(ELECTROKINETICS))
#error Feature SHANCHEN requires not ELECTROKINETICS
#endif

// SD requires CUDA
#if defined(SD) && !(defined(CUDA))
#error Feature SD requires CUDA
#endif

// SD requires ARPACK
#if defined(SD) && !(defined(ARPACK))
#error Feature SD requires ARPACK
#endif

// SD_FF_ONLY requires SD
#if defined(SD_FF_ONLY) && !(defined(SD))
#error Feature SD_FF_ONLY requires SD
#endif

// SD_USE_FLOAT requires SD
#if defined(SD_USE_FLOAT) && !(defined(SD))
#error Feature SD_USE_FLOAT requires SD
#endif

// SD_NOT_PERIODIC requires SD
#if defined(SD_NOT_PERIODIC) && !(defined(SD))
#error Feature SD_NOT_PERIODIC requires SD
#endif

// BOND_ANGLE requires not BOND_ANGLE_OLD
#if defined(BOND_ANGLE) && !( ! defined(BOND_ANGLE_OLD))
#error Feature BOND_ANGLE requires not BOND_ANGLE_OLD
#endif

// COULOMB_DEBYE_HUECKEL requires ELECTROSTATICS
#if defined(COULOMB_DEBYE_HUECKEL) && !(defined(ELECTROSTATICS))
#error Feature COULOMB_DEBYE_HUECKEL requires ELECTROSTATICS
#endif

// IMMERSED_BOUNDARY requires not VIRTUAL_SITES_RELATIVE
#if defined(IMMERSED_BOUNDARY) && !( ! defined(VIRTUAL_SITES_RELATIVE))
#error Feature IMMERSED_BOUNDARY requires not VIRTUAL_SITES_RELATIVE
#endif

// IMMERSED_BOUNDARY requires not VIRTUAL_SITES_COM
#if defined(IMMERSED_BOUNDARY) && !( ! defined(VIRTUAL_SITES_COM))
#error Feature IMMERSED_BOUNDARY requires not VIRTUAL_SITES_COM
#endif

// IMMERSED_BOUNDARY requires not SHANCHEN
#if defined(IMMERSED_BOUNDARY) && !( ! defined(SHANCHEN))
#error Feature IMMERSED_BOUNDARY requires not SHANCHEN
#endif

// IMMERSED_BOUNDARY requires not ELECTROKINETICS
#if defined(IMMERSED_BOUNDARY) && !( ! defined(ELECTROKINETICS))
#error Feature IMMERSED_BOUNDARY requires not ELECTROKINETICS
#endif

// SCAFACOS_DIPOLES requires SCAFACOS and DIPOLES
#if defined(SCAFACOS_DIPOLES) && !(defined(SCAFACOS)  &&  defined(DIPOLES))
#error Feature SCAFACOS_DIPOLES requires SCAFACOS and DIPOLES
#endif

// FLATNOISE requires not GAUSSRANDOM and not GAUSSRANDOM_CUT
#if defined(FLATNOISE) && !( ! defined(GAUSSRANDOM)  &&   ! defined(GAUSSRANDOM_CUT))
#error Feature FLATNOISE requires not GAUSSRANDOM and not GAUSSRANDOM_CUT
#endif

// GAUSSRANDOM requires not FLATNOISE and not GAUSSRANDOM_CUT
#if defined(GAUSSRANDOM) && !( ! defined(FLATNOISE)  &&   ! defined(GAUSSRANDOM_CUT))
#error Feature GAUSSRANDOM requires not FLATNOISE and not GAUSSRANDOM_CUT
#endif

// GAUSSRANDOMCUT requires not GAUSSRANDOM and not FLATNOISE
#if defined(GAUSSRANDOMCUT) && !( ! defined(GAUSSRANDOM)  &&   ! defined(FLATNOISE))
#error Feature GAUSSRANDOMCUT requires not GAUSSRANDOM and not FLATNOISE
#endif


/* Feature list */
const char* FEATURES[] = {

#ifdef ENGINE
  "ENGINE",
#endif

#ifdef BD
  "BD",
#endif

#ifdef EVENT_DEBUG
  "EVENT_DEBUG",
#endif

#ifdef NO_INTRA_NB
  "NO_INTRA_NB",
#endif

#ifdef CG_DNA
  "CG_DNA",
#endif

#ifdef GAUSSRANDOMCUT
  "GAUSSRANDOMCUT",
#endif

#ifdef PTENSOR_DEBUG
  "PTENSOR_DEBUG",
#endif

#ifdef CONSTRAINTS
  "CONSTRAINTS",
#endif

#ifdef ONEPART_DEBUG
  "ONEPART_DEBUG",
#endif

#ifdef LB_GPU
  "LB_GPU",
#endif

#ifdef VIRTUAL_SITES
  "VIRTUAL_SITES",
#endif

#ifdef ROTATIONAL_INERTIA
  "ROTATIONAL_INERTIA",
#endif

#ifdef SD_FF_ONLY
  "SD_FF_ONLY",
#endif

#ifdef BOND_ENDANGLEDIST_HARMONIC
  "BOND_ENDANGLEDIST_HARMONIC",
#endif

#ifdef TK
  "TK",
#endif

#ifdef MEMBRANE_COLLISION
  "MEMBRANE_COLLISION",
#endif

#ifdef GAY_BERNE
  "GAY_BERNE",
#endif

#ifdef POLY_DEBUG
  "POLY_DEBUG",
#endif

#ifdef BOND_ENDANGLEDIST
  "BOND_ENDANGLEDIST",
#endif

#ifdef RANDOM_DEBUG
  "RANDOM_DEBUG",
#endif

#ifdef GAUSSIAN
  "GAUSSIAN",
#endif

#ifdef ESK_DEBUG
  "ESK_DEBUG",
#endif

#ifdef COMFIXED
  "COMFIXED",
#endif

#ifdef INTER_RF
  "INTER_RF",
#endif

#ifdef GRID_DEBUG
  "GRID_DEBUG",
#endif

#ifdef HAT
  "HAT",
#endif

#ifdef PARTICLE_DEBUG
  "PARTICLE_DEBUG",
#endif

#ifdef _P3M_GPU_FLOAT
  "_P3M_GPU_FLOAT",
#endif

#ifdef FORCE_DEBUG
  "FORCE_DEBUG",
#endif

#ifdef ELECTROSTATICS
  "ELECTROSTATICS",
#endif

#ifdef EK_DEBUG
  "EK_DEBUG",
#endif

#ifdef LB_ELECTROHYDRODYNAMICS
  "LB_ELECTROHYDRODYNAMICS",
#endif

#ifdef OIF_GLOBAL_FORCES
  "OIF_GLOBAL_FORCES",
#endif

#ifdef NPT
  "NPT",
#endif

#ifdef CUDA_DEBUG
  "CUDA_DEBUG",
#endif

#ifdef EK_DOUBLE_PREC
  "EK_DOUBLE_PREC",
#endif

#ifdef DPD_MASS
  "DPD_MASS",
#endif

#ifdef GHMC
  "GHMC",
#endif

#ifdef DPD_MASS_LIN
  "DPD_MASS_LIN",
#endif

#ifdef EWALD_GPU
  "EWALD_GPU",
#endif

#ifdef SCAFACOS_DIPOLES
  "SCAFACOS_DIPOLES",
#endif

#ifdef STAT_DEBUG
  "STAT_DEBUG",
#endif

#ifdef COMFORCE
  "COMFORCE",
#endif

#ifdef LB_BOUNDARIES
  "LB_BOUNDARIES",
#endif

#ifdef GHOST_FLAG
  "GHOST_FLAG",
#endif

#ifdef HERTZIAN
  "HERTZIAN",
#endif

#ifdef IMMERSED_BOUNDARY
  "IMMERSED_BOUNDARY",
#endif

#ifdef DPD_MASS_RED
  "DPD_MASS_RED",
#endif

#ifdef MULTI_TIMESTEP
  "MULTI_TIMESTEP",
#endif

#ifdef EK_ELECTROSTATIC_COUPLING
  "EK_ELECTROSTATIC_COUPLING",
#endif

#ifdef BOND_ANGLEDIST_HARMONIC
  "BOND_ANGLEDIST_HARMONIC",
#endif

#ifdef GAUSSRANDOM
  "GAUSSRANDOM",
#endif

#ifdef VERLET_DEBUG
  "VERLET_DEBUG",
#endif

#ifdef CATALYTIC_REACTIONS
  "CATALYTIC_REACTIONS",
#endif

#ifdef PARTIAL_PERIODIC
  "PARTIAL_PERIODIC",
#endif

#ifdef LENNARD_JONES
  "LENNARD_JONES",
#endif

#ifdef HALO_DEBUG
  "HALO_DEBUG",
#endif

#ifdef LJCOS2
  "LJCOS2",
#endif

#ifdef LJ_ANGLE
  "LJ_ANGLE",
#endif

#ifdef ESIF_DEBUG
  "ESIF_DEBUG",
#endif

#ifdef GHOST_FORCE_DEBUG
  "GHOST_FORCE_DEBUG",
#endif

#ifdef OVERLAPPED
  "OVERLAPPED",
#endif

#ifdef EK_BOUNDARIES
  "EK_BOUNDARIES",
#endif

#ifdef VIRTUAL_SITES_RELATIVE
  "VIRTUAL_SITES_RELATIVE",
#endif

#ifdef CELL_DEBUG
  "CELL_DEBUG",
#endif

#ifdef SCAFACOS
  "SCAFACOS",
#endif

#ifdef LATTICE
  "LATTICE",
#endif

#ifdef LATTICE_DEBUG
  "LATTICE_DEBUG",
#endif

#ifdef FFT_DEBUG
  "FFT_DEBUG",
#endif

#ifdef LB_BOUNDARIES_GPU
  "LB_BOUNDARIES_GPU",
#endif

#ifdef BMHTF_NACL
  "BMHTF_NACL",
#endif

#ifdef MOLFORCES_DEBUG
  "MOLFORCES_DEBUG",
#endif

#ifdef EK_REACTION
  "EK_REACTION",
#endif

#ifdef ADDITIONAL_CHECKS
  "ADDITIONAL_CHECKS",
#endif

#ifdef MODES
  "MODES",
#endif

#ifdef EXTERNAL_FORCES
  "EXTERNAL_FORCES",
#endif

#ifdef TABULATED
  "TABULATED",
#endif

#ifdef BUCKINGHAM
  "BUCKINGHAM",
#endif

#ifdef H5MD_DEBUG
  "H5MD_DEBUG",
#endif

#ifdef FENE_DEBUG
  "FENE_DEBUG",
#endif

#ifdef ROTATION
  "ROTATION",
#endif

#ifdef H5MD
  "H5MD",
#endif

#ifdef LANGEVIN_PER_PARTICLE
  "LANGEVIN_PER_PARTICLE",
#endif

#ifdef METADYNAMICS
  "METADYNAMICS",
#endif

#ifdef SOFT_SPHERE
  "SOFT_SPHERE",
#endif

#ifdef MMM1D_GPU
  "MMM1D_GPU",
#endif

#ifdef VIRTUAL_SITES_NO_VELOCITY
  "VIRTUAL_SITES_NO_VELOCITY",
#endif

#ifdef LJCOS
  "LJCOS",
#endif

#ifdef LENNARD_JONES_GENERIC
  "LENNARD_JONES_GENERIC",
#endif

#ifdef VIRTUAL_SITES_THERMOSTAT
  "VIRTUAL_SITES_THERMOSTAT",
#endif

#ifdef AFFINITY
  "AFFINITY",
#endif

#ifdef INTEG_DEBUG
  "INTEG_DEBUG",
#endif

#ifdef DIPOLAR_DIRECT_SUM
  "DIPOLAR_DIRECT_SUM",
#endif

#ifdef DP3M
  "DP3M",
#endif

#ifdef MORSE_DEBUG
  "MORSE_DEBUG",
#endif

#ifdef ROTATION_PER_PARTICLE
  "ROTATION_PER_PARTICLE",
#endif

#ifdef SMOOTH_STEP
  "SMOOTH_STEP",
#endif

#ifdef SD_NOT_PERIODIC
  "SD_NOT_PERIODIC",
#endif

#ifdef OLD_DIHEDRAL
  "OLD_DIHEDRAL",
#endif

#ifdef VIRTUAL_SITES_DEBUG
  "VIRTUAL_SITES_DEBUG",
#endif

#ifdef ESR_DEBUG
  "ESR_DEBUG",
#endif

#ifdef _P3M_GPU_DOUBLE
  "_P3M_GPU_DOUBLE",
#endif

#ifdef GHOSTS_HAVE_BONDS
  "GHOSTS_HAVE_BONDS",
#endif

#ifdef LB_DEBUG
  "LB_DEBUG",
#endif

#ifdef MOLFORCES
  "MOLFORCES",
#endif

#ifdef GHOST_DEBUG
  "GHOST_DEBUG",
#endif

#ifdef ELECTROKINETICS
  "ELECTROKINETICS",
#endif

#ifdef FFTW
  "FFTW",
#endif

#ifdef BOND_CONSTRAINT
  "BOND_CONSTRAINT",
#endif

#ifdef TUNABLE_SLIP
  "TUNABLE_SLIP",
#endif

#ifdef HYDROGEN_BOND
  "HYDROGEN_BOND",
#endif

#ifdef COS2
  "COS2",
#endif

#ifdef COULOMB_DEBYE_HUECKEL
  "COULOMB_DEBYE_HUECKEL",
#endif

#ifdef BOND_ANGLE
  "BOND_ANGLE",
#endif

#ifdef SD
  "SD",
#endif

#ifdef BOND_ANGLEDIST
  "BOND_ANGLEDIST",
#endif

#ifdef MAGGS_DEBUG
  "MAGGS_DEBUG",
#endif

#ifdef THERMOSTAT_IGNORE_NON_VIRTUAL
  "THERMOSTAT_IGNORE_NON_VIRTUAL",
#endif

#ifdef PARTICLE_ANISOTROPY
  "PARTICLE_ANISOTROPY",
#endif

#ifdef DPD
  "DPD",
#endif

#ifdef LJGEN_SOFTCORE
  "LJGEN_SOFTCORE",
#endif

#ifdef SD_USE_FLOAT
  "SD_USE_FLOAT",
#endif

#ifdef INTER_DPD
  "INTER_DPD",
#endif

#ifdef VIRTUAL_SITES_COM
  "VIRTUAL_SITES_COM",
#endif

#ifdef LJ_DEBUG
  "LJ_DEBUG",
#endif

#ifdef LB
  "LB",
#endif

#ifdef MPI_CORE
  "MPI_CORE",
#endif

#ifdef BOND_VIRTUAL
  "BOND_VIRTUAL",
#endif

#ifdef P3M
  "P3M",
#endif

#ifdef NEMD
  "NEMD",
#endif

#ifdef LJ_WARN_WHEN_CLOSE
  "LJ_WARN_WHEN_CLOSE",
#endif

#ifdef CUDA
  "CUDA",
#endif

#ifdef LEES_EDWARDS
  "LEES_EDWARDS",
#endif

#ifdef SD_DEBUG
  "SD_DEBUG",
#endif

#ifdef CONFIGTEMP
  "CONFIGTEMP",
#endif

#ifdef P3M_DEBUG
  "P3M_DEBUG",
#endif

#ifdef UMBRELLA
  "UMBRELLA",
#endif

#ifdef MORSE
  "MORSE",
#endif

#ifdef FORCE_CORE
  "FORCE_CORE",
#endif

#ifdef DIPOLES
  "DIPOLES",
#endif

#ifdef THERMO_DEBUG
  "THERMO_DEBUG",
#endif

#ifdef COMM_DEBUG
  "COMM_DEBUG",
#endif

#ifdef SHANCHEN
  "SHANCHEN",
#endif

#ifdef TRANS_DPD
  "TRANS_DPD",
#endif

#ifdef LE_DEBUG
  "LE_DEBUG",
#endif

#ifdef COLLISION_DETECTION
  "COLLISION_DETECTION",
#endif

#ifdef FLATNOISE
  "FLATNOISE",
#endif

#ifdef OIF_LOCAL_FORCES
  "OIF_LOCAL_FORCES",
#endif

#ifdef TWIST_STACK
  "TWIST_STACK",
#endif

#ifdef MASS
  "MASS",
#endif

#ifdef ASYNC_BARRIER
  "ASYNC_BARRIER",
#endif

#ifdef EXCLUSIONS
  "EXCLUSIONS",
#endif

};

const int NUM_FEATURES = sizeof(FEATURES)/sizeof(char*);
