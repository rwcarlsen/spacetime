
#include "BC.h"

template<>
InputParameters validParams<BC>()
{
  InputParameters params = validParams<FluxBC>();
  params.addParam<Real>("k", 1.0, "thermal conductivity (W/m/K)");
  return params;
}

BC::BC(const InputParameters & pars)
  : FluxBC(pars),
    _k(pars.get<Real>("k"))
{ }

RealGradient
BC::computeQpFluxResidual()
{
  // int(k*w*gradu dSurface)
  auto grad_u = RealGradient(_grad_u[_qp]);
  grad_u(0) = 0;
  return -_k * grad_u;
}

RealGradient
BC::computeQpFluxJacobian() { return 0; }

