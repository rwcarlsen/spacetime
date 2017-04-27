#include "SpacetimeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

#include "SpaceTimeHeatConduction.h"
#include "BC.h"

template<>
InputParameters validParams<SpacetimeApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

SpacetimeApp::SpacetimeApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  SpacetimeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  SpacetimeApp::associateSyntax(_syntax, _action_factory);
}

SpacetimeApp::~SpacetimeApp()
{
}

// External entry point for dynamic application loading
extern "C" void SpacetimeApp__registerApps() { SpacetimeApp::registerApps(); }
void
SpacetimeApp::registerApps()
{
  registerApp(SpacetimeApp);
}

// External entry point for dynamic object registration
extern "C" void SpacetimeApp__registerObjects(Factory & factory) { SpacetimeApp::registerObjects(factory); }
void
SpacetimeApp::registerObjects(Factory & factory)
{
  registerObject(SpaceTimeHeatConduction);
  registerObject(BC);
}

// External entry point for dynamic syntax association
extern "C" void SpacetimeApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SpacetimeApp::associateSyntax(syntax, action_factory); }
void
SpacetimeApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
