#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "utils/RandomNumber.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  Pipeline pipeline;

  Debug(dc::debug.off());
#if 0
  uint64_t count = 0;
  do
  {
    ++count;
//    if (count == 305567)
//      Debug(dc::debug.on());
    Dout(dc::notice, count << " : " << pipeline);
//    if (count == 305568)
//      break;
  }
  while (pipeline.next());

  Dout(dc::notice, "count = " << count);
#else
  utils::RandomNumber rn;

  for (;;)
  {
    pipeline.randomize(rn);
    Dout(dc::notice, pipeline);
  }
#endif
}
