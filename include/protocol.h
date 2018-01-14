/**
 * @Author: fjk
 * @Date:   2018-01-13T20:10:21+08:00
 * @Email:  sunnyfjk@gmail.com
 * @Filename: protocol.h
 * @Last modified by:   fjk
 * @Last modified time: 2018-01-14T12:48:07+08:00
 */
#ifndef __INCLUDE_PROTOCOL_H__
#define __INCLUDE_PROTOCOL_H__
#pragma pack(push,1)
struct MessageHead {
        uint32_t id;
        uint16_t flag;
        uint16_t datalen;
        uint8_t md5[16];
        uint8_t data[0];
};
struct MessageData_t {
        struct MessageHead head;
        uint8_t data[1024];
};
#pragma pack(pop)
struct MessageList_t
{
        int MessageNum;
        int id;
        struct list_head ListNode;
        struct list_head MessageRoot;
        struct sockaddr_in addr;
};
struct Message_t {
        struct list_head MessageNode;
        struct MessageData_t data;
};
struct MessageStr_t {
        struct sockaddr_in addr;
        uint8_t *str;
        uint32_t len;
};
struct MessageList_t *CreateSendMessage(struct sockaddr_in *addr,uint8_t *buf,uint32_t len);
void FreeSendMessage(struct MessageList_t * msgl);
struct MessageStr_t *GetMessageString(struct MessageList_t *msgl);
void FreeMessageString(struct MessageStr_t * msg);
#endif
