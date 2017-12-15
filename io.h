/*
 * \file io.h
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date 21 de jan de 2016
 * \version 1.0.0
 */

#ifndef IO_H_
#define IO_H_

#include <avr/io.h>
#include "tx006_IO.h"

void io_init();
uint16_t io_getOutputs();
uint16_t io_getInputs();

#endif /* IO_H_ */
