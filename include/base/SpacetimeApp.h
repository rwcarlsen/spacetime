#ifndef STORKAPP_H
#define STORKAPP_H

#include "MooseApp.h"

class SpacetimeApp;

template<>
InputParameters validParams<SpacetimeApp>();

class SpacetimeApp : public MooseApp
{
public:
  SpacetimeApp(InputParameters parameters);
  virtual ~SpacetimeApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* STORKAPP_H */
