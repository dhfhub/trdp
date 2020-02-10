/******************************************************************************/
/**
 * @file            trdp_utils.h
 *
 * @brief           Common utilities for TRDP communication
 *
 * @details
 *
 * @note            Project: TCNOpen TRDP prototype stack
 *
 * @author          Bernd Loehr, NewTec GmbH
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright Bombardier Transportation Inc. or its subsidiaries and others, 2013-2019. All rights reserved.
 */
/*
* $Id: trdp_utils.h 1959 2019-08-09 12:40:11Z bloehr $
*
*      BL 2019-06-17: Ticket #264 Provide service oriented interface
*      BL 2019-06-17: Ticket #162 Independent handling of PD and MD to reduce jitter
*      BL 2019-06-17: Ticket #161 Increase performance
*      BL 2019-06-17: Ticket #191 Add provisions for TSN / Hard Real Time (open source)
*      V 2.0.0 --------- ^^^ -----------
*      V 1.4.2 --------- vvv -----------
*      BL 2019-03-21: Ticket #191 Preparations for TSN (External code)
*      BL 2018-06-20: Ticket #184: Building with VS 2015: WIN64 and Windows threads (SOCKET instead of INT32)
*      BL 2017-11-28: Ticket #180 Filtering rules for DestinationURI does not follow the standard
*      BL 2017-11-15: Ticket #1   Unjoin on unsubscribe/delListener (finally ;-)
*      BL 2017-05-08: Doxygen comment errors
*      BL 2016-07-06: Ticket #122 64Bit compatibility (+ compiler warnings)
*/


#ifndef TRDP_UTILS_H
#define TRDP_UTILS_H

/*******************************************************************************
 * INCLUDES
 */

#include <stdio.h>  /*lint !e451 missing guard in std-header */

#include "trdp_private.h"
#include "vos_utils.h"
#include "vos_sock.h"

/*******************************************************************************
 * DEFINES
 */

#define TRDP_INVALID_SOCKET_INDEX  -1

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

extern TRDP_LOG_T gDebugLevel;

void    printSocketUsage(
    TRDP_SOCKETS_T iface[]);

BOOL8   trdp_SockIsJoined (
    const TRDP_IP_ADDR_T    mcList[VOS_MAX_MULTICAST_CNT],
    TRDP_IP_ADDR_T          mcGroup);

BOOL8   trdp_SockAddJoin(
    TRDP_IP_ADDR_T mcList[VOS_MAX_MULTICAST_CNT],
    TRDP_IP_ADDR_T mcGroup);

BOOL8   trdp_SockDelJoin(
    TRDP_IP_ADDR_T mcList[VOS_MAX_MULTICAST_CNT],
    TRDP_IP_ADDR_T mcGroup);

TRDP_IP_ADDR_T  trdp_getOwnIP (void);

PD_ELE_T        *trdp_queueFindComId (
    PD_ELE_T    *pHead,
    UINT32      comId);

PD_ELE_T        *trdp_findSubAddr (
    PD_ELE_T            *pHead,
    TRDP_ADDRESSES_T    *pAddr,
    UINT32              comId);

PD_ELE_T        *trdp_queueFindSubAddr (
    PD_ELE_T            *pHead,
    TRDP_ADDRESSES_T    *pAddr);

PD_ELE_T        *trdp_queueFindExistingSub (
    PD_ELE_T            *pHead,
    TRDP_ADDRESSES_T    *pAddr);

PD_ELE_T        *trdp_queueFindPubAddr (
    PD_ELE_T            *pHead,
    TRDP_ADDRESSES_T    *addr);

void            trdp_queueDelElement (
    PD_ELE_T    * *pHead,
    PD_ELE_T    *pDelete);

void            trdp_queueAppLast (
    PD_ELE_T    * *pHead,
    PD_ELE_T    *pNew);

void            trdp_queueInsFirst (
    PD_ELE_T    * *pHead,
    PD_ELE_T    *pNew);

#if MD_SUPPORT
MD_ELE_T    *trdp_MDqueueFindAddr (
    MD_ELE_T            *pHead,
    TRDP_ADDRESSES_T    *addr);

void        trdp_MDqueueDelElement (
    MD_ELE_T    * *ppHead,
    MD_ELE_T    *pDelete);

void        trdp_MDqueueAppLast (
    MD_ELE_T    * *pHead,
    MD_ELE_T    *pNew);

void        trdp_MDqueueInsFirst (
    MD_ELE_T    * *ppHead,
    MD_ELE_T    *pNew);
#endif

INT32   trdp_getCurrentMaxSocketCnt (
    TRDP_SOCK_TYPE_T    type);

void trdp_setCurrentMaxSocketCnt (
    TRDP_SOCK_TYPE_T    type,
    INT32               currentMaxSocketCnt);

void trdp_initSockets (
    TRDP_SOCKETS_T  iface[],
    UINT8           noOfEntries);

void    trdp_initUncompletedTCP (
    TRDP_APP_SESSION_T appHandle);

void    trdp_resetSequenceCounter (
    PD_ELE_T        *pElement,
    TRDP_IP_ADDR_T  srcIP,
    TRDP_MSG_T      msgType);

TRDP_IP_ADDR_T  trdp_findMCjoins (
    TRDP_APP_SESSION_T  appHandle,
    TRDP_IP_ADDR_T      mcGroup);

TRDP_ERR_T      trdp_requestSocket(
    TRDP_SOCKETS_T iface[],
    UINT16 port,
    const TRDP_SEND_PARAM_T * params,
    TRDP_IP_ADDR_T srcIP,
    TRDP_IP_ADDR_T mcGroup,
    TRDP_SOCK_TYPE_T type,
    TRDP_OPTION_T options,
    BOOL8 rcvMostly,
    SOCKET useSocket,
    INT32                   * pIndex,
    TRDP_IP_ADDR_T cornerIp);

void trdp_releaseSocket(
    TRDP_SOCKETS_T iface[],
    INT32 lIndex,
    UINT32 connectTimeout,
    BOOL8 checkAll,
    TRDP_IP_ADDR_T mcGroupUsed);


UINT32  trdp_packetSizePD (
    UINT32 dataSize);

UINT32  trdp_packetSizePD2 (
    UINT32 dataSize);

UINT32  trdp_packetSizeMD (
    UINT32 dataSize);

UINT32  trdp_getSeqCnt (
    UINT32          comId,
    TRDP_MSG_T      msgType,
    TRDP_IP_ADDR_T  srcIpAddr);

int trdp_checkSequenceCounter (
    PD_ELE_T        *pElement,
    UINT32          sequenceCounter,
    TRDP_IP_ADDR_T  srcIP,
    TRDP_MSG_T      msgType);

BOOL8 trdp_isAddressed (
    const TRDP_URI_USER_T   listUri,
    const TRDP_URI_USER_T   destUri);


BOOL8 trdp_validTopoCounters (
    UINT32  etbTopoCnt,
    UINT32  opTrnTopoCnt,
    UINT32  etbTopoCntFilter,
    UINT32  opTrnTopoCntFilter);

BOOL8 trdp_isInIPrange (
    TRDP_IP_ADDR_T  receivedSrcIP,
    TRDP_IP_ADDR_T  listenedSourceIPlow,
    TRDP_IP_ADDR_T  listenedSourceIPhigh);

#endif