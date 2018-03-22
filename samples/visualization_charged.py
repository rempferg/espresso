import espressomd
from espressomd.visualization_opengl import openGLLive
from espressomd import electrostatics
import numpy as np

box = [40, 40, 40]
system = espressomd.System(box_l=box)
system.cell_system.set_domain_decomposition(use_verlet_lists=True)
visualizer = openGLLive(system, background_color=[
                        1, 1, 1], drag_enabled=True, drag_force=10)

# TIMESTEP
time_step_fs = 1.0
system.time_step = time_step_fs * 1.0e-2
system.cell_system.skin = 1.2

# TEMPERATURE
SI_temperature = 300.0
kb_kjmol = 0.0083145
temperature = SI_temperature * kb_kjmol

# COULOMB PREFACTOR (elementary charge)^2 / (4*pi*epsilon_0) in Angstrom * kJ/mol
epsilon_r = 4.0
coulomb_prefactor = 1.67101e5 * kb_kjmol / epsilon_r

# FORCE FIELDS
species = ["Cl", "Na", "Colloid", "Solvent"]
types = {"Cl":          0, "Na": 1, "Colloid": 2, "Solvent": 3}
charges = {"Cl": -1.0, "Na": 1.0, "Colloid": -3.0, "Solvent": 0.0}
lj_sigmas = {"Cl":       3.85, "Na": 2.52, "Colloid": 10.0, "Solvent": 1.5}
lj_epsilons = {"Cl":     192.45, "Na": 17.44,
               "Colloid": 100.0, "Solvent": 50.0}
lj_cuts = {"Cl":  2.0 * lj_sigmas["Cl"], "Na": 2.0 * lj_sigmas["Na"],
           "Colloid": 1.5 * lj_sigmas["Colloid"], "Solvent": 2.0 * lj_sigmas["Solvent"]}
masses = {"Cl":        35.453, "Na": 22.99, "Colloid": 300, "Solvent": 18.0}

n_ionpairs = 50
for i in range(n_ionpairs):
    for t in ["Na", "Cl"]:
        system.part.add(pos=box * np.random.random(3),
                        q=charges[t], type=types[t], mass=masses[t])

n_colloids = 30
t = "Colloid"
t_co = "Na"
for i in range(n_colloids):
    system.part.add(pos=box * np.random.random(3),
                    q=charges[t], type=types[t], mass=masses[t])
    for i in range(int(abs(charges[t]))):
        system.part.add(pos=box * np.random.random(3),
                        q=charges[t_co], type=types[t_co], mass=masses[t_co])

n_solvents = 800
t = "Solvent"
for i in range(n_solvents):
    system.part.add(pos=box * np.random.random(3),
                    q=charges[t], type=types[t], mass=masses[t])


def combination_rule_epsilon(rule, eps1, eps2):
    if rule == "Lorentz":
        return (eps1 * eps2)**0.5
    else:
        return ValueError("No combination rule defined")


def combination_rule_sigma(rule, sig1, sig2):
    if rule == "Berthelot":
        return (sig1 + sig2) * 0.5
    else:
        return ValueError("No combination rule defined")


# Lennard-Jones interactions parameters
for i in range(len(species)):
    for j in range(i, len(species)):
        s = [species[i], species[j]]
        lj_sig = combination_rule_sigma(
            "Berthelot", lj_sigmas[s[0]], lj_sigmas[s[1]])
        lj_cut = combination_rule_sigma(
            "Berthelot", lj_cuts[s[0]], lj_cuts[s[1]])
        lj_eps = combination_rule_epsilon(
            "Lorentz", lj_epsilons[s[0]], lj_epsilons[s[1]])

        system.non_bonded_inter[types[s[0]], types[s[1]]].lennard_jones.set_params(
            epsilon=lj_eps, sigma=lj_sig, cutoff=lj_cut, shift="auto")

energy = system.analysis.energy()
print("Before Minimization: E_total = {}".format(energy['total']))
system.minimize_energy.init(f_max=1000, gamma=30.0,
                            max_steps=1000, max_displacement=0.01)
system.minimize_energy.minimize()
energy = system.analysis.energy()
print("After Minimization: E_total = {}".format(energy['total']))

print("Tune p3m")
p3m = electrostatics.P3M(prefactor=coulomb_prefactor, accuracy=1e-1)
system.actors.add(p3m)

system.thermostat.set_langevin(kT=temperature, gamma=5.0)

visualizer.run(1)
