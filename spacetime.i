[Mesh]
  type = GeneratedMesh
  dim = 2

  nx = 10
  xmin = 0
  xmax = 10

  ny = 10
  ymin = 0
  ymax = 10
[]

[Variables]
  [./T]
  [../]
[]

[Kernels]
  [./diff]
    type = SpaceTimeHeatConduction
    variable = T
    k = 1.0          # (W/m/K)
    heat_cap = 1.0   # (J/kg/K)
    source_rad = 1.0 # source radius
    source = 0.0     # source strength (W/m^3)
    source_t = '0 10'
    source_x = '0 10'
    source_y = '0 10' # unused for 1d spatial problem (i.e. 2d tot)
  [../]
[]

[BCs]
  #type = FunctionDirichletBC
  #function = x
  #[./bottom] # t=0
  #  type = DirichletBC
  #  variable = T
  #  boundary = bottom
  #  value = 0
  #[../]
  #[./top] # t=T
  #  type = BC
  #  k = 1.0
  #  variable = T
  #  boundary = bottom
  #[../]
  [./left] # x=0
    type = DirichletBC
    variable = T
    boundary = left
    value = 10
  [../]
  [./right] # x=L
    type = DirichletBC
    variable = T
    boundary = right
    value = 10
  [../]
  [./top] # x=L
    type = DirichletBC
    variable = T
    boundary = top
    value =5 
  [../]
  [./bottom] # x=L
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 5
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
