/*
 * gps.h
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#ifndef GPS_GPS_H_
#define GPS_GPS_H_

#include "bsp.h"

void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);

#endif /* GPS_GPS_H_ */
