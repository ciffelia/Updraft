#pragma once

extern "C" {
#include <Uefi.h>
}

struct PrintEfiStatus
{
  const RETURN_STATUS m_returnStatus;

  constexpr PrintEfiStatus(const RETURN_STATUS returnStatus)
    : m_returnStatus(returnStatus)
  { }
};
