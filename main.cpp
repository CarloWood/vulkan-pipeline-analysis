#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  Pipeline stuff;

  do
  {
    Dout(dc::notice, stuff);
  }
  while (stuff.next());
}
