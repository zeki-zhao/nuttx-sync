/****************************************************************************
 * boards/arm/stm32/mystm32f429igt6/src/stm32_myinit.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/boardctl.h>
#include <sched.h>
#include <stdio.h>

/****************************************************************************
 * External Functions
 ****************************************************************************/

extern int mylvgl_main(int argc, FAR char *argv[]);
extern int nsh_main(int argc, FAR char *argv[]);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int myinit_main(int argc, FAR char *argv[])
{
    /* Start LVGL application as a background task */

    task_create("mylvgl",
                CONFIG_EXAMPLES_MY_LVGL_PRIORITY,
                CONFIG_EXAMPLES_MY_LVGL_STACKSIZE,
                mylvgl_main,
                NULL);

    /* Start NSH (handles login, then shell) */

    nsh_main(argc, argv);

    return 0;
}
