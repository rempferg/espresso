
/* Generic features */
//#define PARTIAL_PERIODIC
//#define EXTERNAL_FORCES
//#define CONSTRAINTS
//#define MASS
//#define EXCLUSIONS
//#define COMFORCE
//#define COMFIXED
//#define MOLFORCES
//#define BOND_CONSTRAINT
//#define MODES
//#define BOND_VIRTUAL
//#define LANGEVIN_PER_PARTICLE
//#define COLLISION_DETECTION
//#define LEES_EDWARDS
//#define METADYNAMICS
//#define NEMD
//#define NPT
//#define GHMC
//#define CATALYTIC_REACTIONS
//#define MULTI_TIMESTEP
//#define ENGINE
//#define CONFIGTEMP
//#define PARTICLE_ANISOTROPY

/* Rotation */
//#define ROTATION
//#define ROTATIONAL_INERTIA
//#define ROTATION_PER_PARTICLE

/* Electrostatics */
//#define ELECTROSTATICS
//#define INTER_RF
//#define MMM1D_GPU
//#define EWALD_GPU
//#define _P3M_GPU_FLOAT
//#define _P3M_GPU_DOUBLE


/* Magnetostatics */
//#define DIPOLES

/* Virtual sites features */
//#define VIRTUAL_SITES_COM
//#define VIRTUAL_SITES_RELATIVE
//#define VIRTUAL_SITES_NO_VELOCITY
//#define VIRTUAL_SITES_THERMOSTAT
//#define THERMOSTAT_IGNORE_NON_VIRTUAL

/* DPD features */
//#define DPD
//#define TRANS_DPD
//#define DPD_MASS_RED
//#define DPD_MASS_LIN
//#define TUNABLE_SLIP

/* Alternative implementation of DPD */
//#define INTER_DPD

/* Lattice-Boltzmann features */
//#define LB
//#define LB_GPU
//#define LB_BOUNDARIES
//#define LB_BOUNDARIES_GPU
//#define LB_ELECTROHYDRODYNAMICS
//#define ELECTROKINETICS
//#define EK_BOUNDARIES
//#define EK_REACTION
//#define EK_ELECTROSTATIC_COUPLING
//#define EK_DEBUG
//#define EK_DOUBLE_PREC
//#define SHANCHEN

/* Stokesian-Dynamics features */
//#define BD
//#define SD
//#define SD_FF_ONLY
//#define SD_USE_FLOAT
//#define SD_NOT_PERIODIC

/* Interaction features */
//#define TABULATED
//#define LENNARD_JONES
//#define LJ_WARN_WHEN_CLOSE
//#define LENNARD_JONES_GENERIC
//#define LJCOS
//#define LJCOS2
//#define LJ_ANGLE
//#define LJGEN_SOFTCORE
//#define COS2
//#define GAY_BERNE
//#define SMOOTH_STEP
//#define HERTZIAN
//#define GAUSSIAN
//#define BMHTF_NACL
//#define MORSE
//#define BUCKINGHAM
//#define SOFT_SPHERE
//#define HAT
//#define UMBRELLA
//#define OVERLAPPED

/* Fluid-Structure Interactions (object in fluid) */
//#define OIF_LOCAL_FORCES
//#define OIF_GLOBAL_FORCES
//#define AFFINITY
//#define MEMBRANE_COLLISION

//#define BOND_ANGLE

//#define BOND_ANGLEDIST
//#define BOND_ANGLEDIST_HARMONIC

//#define BOND_ENDANGLEDIST
//#define BOND_ENDANGLEDIST_HARMONIC

//#define CG_DNA
//#define TWIST_STACK
//#define HYDROGEN_BOND
//#define COULOMB_DEBYE_HUECKEL

/* Immersed-Boundary Bayreuth version */
//#define IMMERSED_BOUNDARY
//#define SCAFACOS_DIPOLES

// Shape of the noise in ther (Langevin) thermostat
//#define FLATNOISE
//#define GAUSSRANDOM
//#define GAUSSRANDOMCUT


/* Strange features. Use only if you know what you are doing! */
/* activate the old dihedral form */
//#define OLD_DIHEDRAL
/* turn off nonbonded interactions within molecules */
//#define NO_INTRA_NB
/* add an int to the particle marking ghosts. Only visible on C level */
//#define GHOST_FLAG
/* ghost particles also have the bond information. */
//#define GHOSTS_HAVE_BONDS


/* Debugging */
//#define ADDITIONAL_CHECKS
//#define ASYNC_BARRIER

//#define ESIF_DEBUG
//#define COMM_DEBUG
//#define EVENT_DEBUG
//#define INTEG_DEBUG
//#define CELL_DEBUG
//#define GHOST_DEBUG
//#define LATTICE_DEBUG
//#define HALO_DEBUG
//#define GRID_DEBUG
//#define VERLET_DEBUG
//#define PARTICLE_DEBUG
//#define P3M_DEBUG
//#define FFT_DEBUG
//#define RANDOM_DEBUG
//#define FORCE_DEBUG
//#define THERMO_DEBUG
//#define LE_DEBUG
//#define LJ_DEBUG
//#define MORSE_DEBUG
//#define ESR_DEBUG
//#define ESK_DEBUG
//#define FENE_DEBUG
//#define GHOST_FORCE_DEBUG
//#define STAT_DEBUG
//#define POLY_DEBUG
//#define MOLFORCES_DEBUG
//#define PTENSOR_DEBUG
//#define MAGGS_DEBUG
//#define LB_DEBUG
//#define VIRTUAL_SITES_DEBUG
//#define SD_DEBUG
//#define CUDA_DEBUG
//#define H5MD_DEBUG

//#define MPI_CORE
//#define FORCE_CORE

/* Single particle debugging */
//#define ONEPART_DEBUG
// which particle id to debug
//#define ONEPART_DEBUG_ID 13

