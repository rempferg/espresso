#include "lb_oop.hpp"

using namespace LB;

LBFluid::LBFluid()
{
}

void LBFluid::integrate()
{
  calc_modes();
  relax(mode[0], mode[1:3]);
  thermalize();
  apply force();
  calc_n_from_m_push();
}

float LBFluid::equilibrium_mode(float rho, float* u, int i);
 
void LBFluid::calc_modes();
void LBFluid::relax(float rho, float* u)
{
  for(int i = 0; i < 19; i++)
    mode[i] = equilibrium_mode(rho, u, i) + gamma * mode[i];
}
void LBFluid::thermalize();
void LBFluid::apply_force();
void LBFluid::calc_populations_push();
