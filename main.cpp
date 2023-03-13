#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "utils/RandomNumber.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  Pipeline pipeline;

#if 1
  uint64_t count = 0;
  do
  {
    ++count;
//    if (count > 8638025 - 100)
    Dout(dc::notice, pipeline);
    if (count % (5509 * 5509) == 0)
      //Dout(dc::notice, "count = " << (count / (5509 * 5509)));
      std::cout << "count = " << (count / (5509 * 5509)) << std::endl;
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
