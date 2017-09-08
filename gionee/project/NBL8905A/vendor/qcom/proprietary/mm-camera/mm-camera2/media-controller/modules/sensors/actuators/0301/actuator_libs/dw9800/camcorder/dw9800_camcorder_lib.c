/*============================================================================

  Copyright (c) 2013-2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

#include "af_tuning.h"
#include "actuator.h"

static actuator_ctrl_t dw9800_camcorder_lib_ptr = {
#include "dw9800_camcorder_lib.h"
};

void *dw9800_camcorder_open_lib(void)
{
  return &dw9800_camcorder_lib_ptr;
}
