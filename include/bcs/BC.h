#pragma once

#include "FluxBC.h"

class BC;

template<>
InputParameters validParams<BC>();

/**
 *
 */
class BC : public FluxBC
{
public:
  BC(const InputParameters & parameters);

protected:
  virtual RealGradient computeQpFluxResidual();
  virtual RealGradient computeQpFluxJacobian();

  Real _k;
};

