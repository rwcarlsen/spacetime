
#include "BC.h"

template<>
InputParameters validParams<BC>()
{
  InputParameters params = validParams<FluxBC>();

  return params;
}

BC::BC(const InputParameters & parameters) :
    FluxBC(parameters),
    _k(getMaterialProperty<Real>("thermal_conductivity"))
{
}

BC::~BC()
{
}

RealGradient
BC::computeQpFluxResidual()
{
  return -_k[_qp] * _grad_u[_qp];
}

RealGradient
BC::computeQpFluxJacobian()
{
  return -_k[_qp] * _grad_phi[_j][_qp];
}

