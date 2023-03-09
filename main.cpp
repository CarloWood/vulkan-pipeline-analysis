#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "utils/RandomNumber.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  utils::RandomNumber rn;
  Pipeline pipeline;

#if 0
  int count = 0;
  do
  {
    ++count;
//    if (count > 8638025 - 100)
//      Dout(dc::notice, pipeline);
  }
  while (pipeline.next());
#endif

  for (;;)
  {
    pipeline.randomize(rn);
    Dout(dc::notice, pipeline);
  }

  //Dout(dc::notice, "count = " << count);
}
