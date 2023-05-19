#pragma once

#define ERR(TYPE, MSG)                                                         \
  std::cout << TYPE << ": " << MSG << " in file: " << __FILE__                 \
            << " at line: " << __LINE__ << std::endl;                          \
  exit(0);

#define ASSERT(X, MSG) if (!X)                                                 \
  {                                                                            \
    ERR("Assertion Error", MSG);                                               \
  }
