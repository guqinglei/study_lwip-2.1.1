/**
 * @file
 * TCP protocol definitions
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef LWIP_HDR_PROT_TCP_H
#define LWIP_HDR_PROT_TCP_H

#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Length of the TCP header, excluding options. */
#define TCP_HLEN 20

/* Fields are (of course) in network byte order.
 * Some fields are converted to host byte order in tcp_input().
 */
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif

/* 定义标准 tcp 协议头（不包含选项字段）数据结构 */
PACK_STRUCT_BEGIN
struct tcp_hdr {
  PACK_STRUCT_FIELD(u16_t src);
  PACK_STRUCT_FIELD(u16_t dest);
  PACK_STRUCT_FIELD(u32_t seqno);
  PACK_STRUCT_FIELD(u32_t ackno);
  PACK_STRUCT_FIELD(u16_t _hdrlen_rsvd_flags);
  PACK_STRUCT_FIELD(u16_t wnd);
  PACK_STRUCT_FIELD(u16_t chksum);
  PACK_STRUCT_FIELD(u16_t urgp);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/* TCP header flags bits */
/* 定义 tcp 协议头中包含的几种协议控制位 */
#define TCP_FIN 0x01U
#define TCP_SYN 0x02U
#define TCP_RST 0x04U
#define TCP_PSH 0x08U
#define TCP_ACK 0x10U
#define TCP_URG 0x20U
#define TCP_ECE 0x40U
#define TCP_CWR 0x80U

/* Valid TCP header flags */
/* 定义 tcp 协议头中包含的几种协议控制位掩码值 */
#define TCP_FLAGS 0x3fU

/* 定义 tcp 协议头中“选项”字段可以包含的最多数据字节数 */
#define TCP_MAX_OPTION_BYTES 40

/* 获取 tcp 协议头中的协议头长度字段值，单位是 4 个 8 位字节 */
#define TCPH_HDRLEN(phdr) ((u16_t)(lwip_ntohs((phdr)->_hdrlen_rsvd_flags) >> 12))

/* 获取 tcp 协议头中的协议头长度字段值，单位是 8 位字节 */
#define TCPH_HDRLEN_BYTES(phdr) ((u8_t)(TCPH_HDRLEN(phdr) << 2))

/* 获取 tcp 协议头中的协议控制位字段值 */
#define TCPH_FLAGS(phdr)  ((u8_t)((lwip_ntohs((phdr)->_hdrlen_rsvd_flags) & TCP_FLAGS)))

/* 设置 tcp 协议头中的协议头长度字段值（包含常规协议头和选项数据），单位是 4 个 8 位字节 */
#define TCPH_HDRLEN_SET(phdr, len) (phdr)->_hdrlen_rsvd_flags = lwip_htons(((len) << 12) | TCPH_FLAGS(phdr))

/* 设置 tcp 协议头中的协议控制位字段值（清空原来的，设置成新的）*/
#define TCPH_FLAGS_SET(phdr, flags) (phdr)->_hdrlen_rsvd_flags = (((phdr)->_hdrlen_rsvd_flags & PP_HTONS(~TCP_FLAGS)) | lwip_htons(flags))

/* 设置 tcp 协议头中的协议头长度字段值（单位是 4 个 8 位字节）和协议控制位字段值（清空原来的，设置成新的）*/
#define TCPH_HDRLEN_FLAGS_SET(phdr, len, flags) (phdr)->_hdrlen_rsvd_flags = (u16_t)(lwip_htons((u16_t)((len) << 12) | (flags)))

/* 设置 tcp 协议头中的协议控制位中的某个标志位（直接或上指定的控制位，不影响其他控制位的值）*/
#define TCPH_SET_FLAG(phdr, flags ) (phdr)->_hdrlen_rsvd_flags = ((phdr)->_hdrlen_rsvd_flags | lwip_htons(flags))

/* 清除 tcp 协议头中的协议控制位中的某个控制位（只清除我们指定的控制位，不影响其他控制位的值）*/
#define TCPH_UNSET_FLAG(phdr, flags) (phdr)->_hdrlen_rsvd_flags = ((phdr)->_hdrlen_rsvd_flags & ~lwip_htons(flags))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_TCP_H */
