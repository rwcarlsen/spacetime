#pragma once

#include "Kernel.h"

class SpaceTimeHeatConduction;

template<>
InputParameters validParams<SpaceTimeHeatConduction>();

class SpaceTimeHeatConduction : public Kernel
{
public:
  SpaceTimeHeatConduction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

private:
  Real source();

  Real _k;
  Real _heat_cap;
  Real _density;
  Real _source_rad;
  Real _source;
  std::vector<Real> _source_t;
  std::vector<Real> _source_x;
  std::vector<Real> _source_y;
};

