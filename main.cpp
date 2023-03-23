#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "utils/RandomNumber.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  Pipeline pipeline;

  //Debug(dc::debug.off());
  uint64_t count = 0;
#if 0
  do
  {
    ++count;
//    if (count == 305567)
//      Debug(dc::debug.on());
    Dout(dc::notice, count << " : " << pipeline);
    ASSERT(pipeline.is_sane());
//    if (count == 305568)
//      break;
  }
  while (pipeline.next());

  Dout(dc::notice, "count = " << count);
#else
  utils::RandomNumber rn(0x4);

  for (;;)
  {
    ++count;
    try
    {
      pipeline.randomize(rn);
    }
    catch (std::exception const&)
    {
      Dout(dc::notice, "FAILURE for: " << pipeline);
      return 1;
    }
    Dout(dc::notice, count << " : " << pipeline);
    ASSERT(pipeline.is_sane());
  }
#endif
}
