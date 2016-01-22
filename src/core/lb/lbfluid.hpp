#ifndef LB_OOP_H
#define LB_OOP_H

#include <vector>


namespace LB
{

class LBFluid
{
friend class SCFluid;

public:
  LBFluid();
  void integrate();

private:
  float equilibrium_mode(float rho, float* u, int i);
  
  void calc_modes();
  void relax(float rho, float* u)
  {
    for(int i = 0; i < 19; i++)
      mode[i] = equilibrium_mode(rho, u, i) + gamma * mode[i];
  }
  void thermalize();
  void apply_force();
  void calc_populations_push();
  
  float* population;
  float* force;
  //other parameters and stuff
};

}


#endif // LB_OOP_H
