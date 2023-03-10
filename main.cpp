#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "utils/RandomNumber.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  ShaderStageFlagBits f;
  ShaderModule sm(f);
  Declarations/*Pipeline*/ pipeline(&sm);

#if 0
  int count = 0;
  do
  {
    ++count;
//    if (count > 8638025 - 100)
      Dout(dc::notice, pipeline);
  }
  while (pipeline.next());

#else
  utils::RandomNumber rn;

  for (;;)
  {
    pipeline.randomize(rn);
    Dout(dc::notice, pipeline);
  }
#endif

  //Dout(dc::notice, "count = " << count);
}
