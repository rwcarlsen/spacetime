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
  virtual ~BC();

protected:
  virtual RealGradient computeQpFluxResidual();
  virtual RealGradient computeQpFluxJacobian();

  const MaterialProperty<Real> & _k;
};

