#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  ShaderStageFlagBits flag;
  ShaderModule sm(flag);
  Declarations stuff(&sm);

  do
  {
    Dout(dc::notice, stuff);
  }
  while (stuff.next());
}
