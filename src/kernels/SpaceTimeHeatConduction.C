
#include "SpaceTimeHeatConduction.h"
#include "LinearInterpolation.h"

template<>
InputParameters validParams<SpaceTimeHeatConduction>()
{
  InputParameters pars = validParams<Kernel>();
  pars.addClassDescription("Heat conduction treating the 1st spatial dim as time.");
  pars.addParam<Real>("k", 1.0, "thermal conductivity (W/m/K)");
  pars.addParam<Real>("heat_cap", 1.0, "heat capacity (J/kg/K)");
  pars.addParam<Real>("density", 1.0, "material density (kg/m^3)");
  pars.addParam<Real>("source_rad", 1.0, "source radius (m)");
  pars.addParam<Real>("source", 1.0, "source strength (W/m^3)");
  pars.addRequiredParam<std::vector<Real>>("source_t", "source t positions (m)");
  pars.addRequiredParam<std::vector<Real>>("source_x", "source x positions (m)");
  pars.addRequiredParam<std::vector<Real>>("source_y", "source y positions (m)");
  return pars;
}

SpaceTimeHeatConduction::SpaceTimeHeatConduction(const InputParameters & pars)
  : Kernel(pars),
    _k(pars.get<Real>("k")),
    _heat_cap(pars.get<Real>("heat_cap")),
    _density(pars.get<Real>("density")),
    _source_rad(pars.get<Real>("source_rad")),
    _source(pars.get<Real>("source")),
    _source_t(pars.get<std::vector<Real>>("source_t")),
    _source_x(pars.get<std::vector<Real>>("source_x")),
    _source_y(pars.get<std::vector<Real>>("source_y"))
{
}

Real
SpaceTimeHeatConduction::computeQpResidual()
{
  // time dimension is x (i.e. first dimension)
  Real residual = 0;

  // spatial temperature diffusion term: int(k*gradw*gradu dV)
  // mask gradient to exclude time dimension
  auto grad_u = RealGradient(_grad_u[_qp]);
  grad_u(0) = 0;
  residual += _k * _grad_test[_i][_qp] * grad_u;

  // source term: int(w*S dV)
  // I'm not sure why, but this needs the negative multipier...
  residual += -1 * _test[_i][_qp] * source();

  //std::cout << "i=" << _i << ",j=" << _j << ", x=" << _q_point[_qp](1) << ", t=" << _q_point[_qp](0) << "\n";
  //std::cout << "    gradu_x=" << _grad_u[_qp](1) << ", gradu_t=" << _grad_u[_qp](0) << "\n";
  std::cout << "    xresidual=" << residual << ", tresidual=" << -1 * _density * _heat_cap * _test[_i][_qp] * _grad_u[_qp](0) << ", source=" << _test[_i][_qp] * source() << "\n";
  // temperature time derivative term: rho*c_v*int(w*gradu dV)
  // mask gradient to exclude spatial dimensions
  residual += -1 * _density * _heat_cap * _test[_i][_qp] * _grad_u[_qp](0);

  return residual;
}

Real
SpaceTimeHeatConduction::source() {
  Point p = _q_point[_qp];
  LinearInterpolation xlin(_source_t, _source_x);
  LinearInterpolation ylin(_source_t, _source_y);
  Real x = xlin.sample(p(0));
  Real y = ylin.sample(p(0));

  Real dist = std::sqrt((p(1) - x)*(p(1) - x) + (p(2) - y)*(p(2) - y));
  return _source * std::exp(-1*std::pow(0.5*_source_rad*dist, 2.0));
}

Real
SpaceTimeHeatConduction::computeQpJacobian() {
  return 0;
}

