[Mesh]
  type = GeneratedMesh
  dim = 2

  nx = 8
  xmin = 0
  xmax = 20

  ny = 4
  ymin = 0
  ymax = 10
[]

[Variables]
  [./T]
    [./InitialCondition]
      type = ConstantIC
      value = 5.0
    [../]
  [../]
[]

[Kernels]
  [./spacetime]
    type = SpaceTimeHeatConduction
    variable = T
    k = 1.0          # (W/m/K)
    heat_cap = 1.0   # (J/kg/K)
    density = 1.0    # (kg/m^3)
    source_rad = 0.4 # source radius
    source = 1.7     # source strength (W/m^3)
    source_t = '0  2  8 20'
    source_x = '-5 0 10 15'
    source_y = '0 0 0 0' # unused for 1d spatial problem (i.e. 2d tot)
  [../]
[]

[BCs]
  [./spatial] # x=0, x=L
    type = DirichletBC
    variable = T
    boundary = 'top bottom'
    value = 5
  [../]
  [./time_initial] # t=0
    type = FunctionDirichletBC
    function = bc_func
    variable = T
    boundary = left
  [../]
[]

[Functions]
  [./bc_func]
    type = ParsedFunction
    value = sqrt(25-(y-5)^2)+5
    #vars = 'alpha'
    #vals = '16'
  [../]
[]

[Adaptivity]
  marker = errorfrac
  steps = 6

  [./Indicators]
    [./error]
      type = GradientJumpIndicator
      variable = T
    [../]
  [../]

  [./Markers]
    [./errorfrac]
      type = ErrorFractionMarker
      refine = 0.65
      coarsen = 0.0
      indicator = error
    [../]
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

#[Preconditioning]
#  active = 'FDP'
#  [./FDP]
#    type = FDP
#    full = true
#  [../]
#[]

[Outputs]
  exodus = true
[]
