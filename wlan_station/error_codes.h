/*
 * error_codes.h
 *
 *  Created on: 25 αιπε 2015
 *      Author: roy
 */

#ifndef ERROR_CODES_H_
#define ERROR_CODES_H_

typedef enum{
    // Choosing -0x7D0 to avoid overlap w/ host-driver's error codes
    TCP_CLIENT_FAILED = -0x7D0,
    TCP_SERVER_FAILED = TCP_CLIENT_FAILED - 1,
    DEVICE_NOT_IN_STATION_MODE = TCP_SERVER_FAILED - 1,
    LAN_CONNECTION_FAILED = DEVICE_NOT_IN_STATION_MODE -1,
    INTERNET_CONNECTION_FAILED = LAN_CONNECTION_FAILED - 1,

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

#endif /* ERROR_CODES_H_ */
