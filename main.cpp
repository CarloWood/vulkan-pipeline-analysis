#include "sys.h"
#include <iostream>
#include "Pipeline.h"
#include "debug.h"

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  Pipeline pipeline;

  int count = 0;
  do
  {
    ++count;
//    if (count > 8638025 - 100)
//      Dout(dc::notice, pipeline);
  }
  while (pipeline.next());

  Dout(dc::notice, "count = " << count);
}
