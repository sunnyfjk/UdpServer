/**
 * @Author: fjk
 * @Date:   2018-01-13T20:10:26+08:00
 * @Email:  sunnyfjk@gmail.com
 * @Filename: protocol.c
 * @Last modified by:   fjk
 * @Last modified time: 2018-01-14T21:25:00+08:00
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <list.h>
#include <md5.h>
#include <protocol.h>

#ifndef PERR
#define PERR(fmt,arg ...) fprintf(stderr,"[%s:%d]"fmt,__FUNCTION__,__LINE__, ## arg)
#endif
enum {
        MSG_END,
        NSG_NODE,
};
struct MessageList_t *CreateSendMessage(struct sockaddr_in *addr,uint8_t *buf,uint32_t len)
{
        struct MessageList_t *msgl=NULL;
        struct Message_t *ms=NULL,*n=NULL;
        struct MD5_CTX md5 = {0};
        int i=0;
        if(addr==NULL || buf==NULL || len==0) {
                PERR("Parameter error\n");
                goto Parameter_error;
        }
        INIT_LIST_HEAD(&msgl->ListNode);
        INIT_LIST_HEAD(&msgl->MessageRoot);
        memcpy(&msgl->addr, addr, sizeof(*addr));
        msgl=calloc(1,sizeof(*msgl));
        if(msgl==NULL) {
                PERR("calloc msgl err\n");
                goto calloc_msgl_err;
        }
        while(len>0) {
                ms=NULL;
                memset(&md5,0, sizeof(md5));
                ms=calloc(1,sizeof(*ms));
                INIT_LIST_HEAD(&ms->MessageNode);
                ms->data.head.id=i;
                ms->data.head.flag=NSG_NODE;
                if(len>1024) {
                        ms->data.head.datalen=1024;
                        len-=1024;
                }else{
                        ms->data.head.datalen=len;
                        len=0;
                }
                MD5Init(&md5);
                MD5Update(&md5, buf[1024*i],ms->data.head.datalen );
                MD5Final(&md5, (ms->data.head.md5));
                memcpy(ms->data.data, &(buf[1024*i]), ms->data.head.datalen);
                list_add(&ms->MessageNode,&msgl->MessageRoot);
                i++;
        }
        return msgl;
calloc_ms_err:
        list_for_each_entry_safe_reverse(ms,n,&msgl->MessageRoot,MessageNode){
                list_del_init(&ms->MessageNode);
                free(ms);
        }
        free(msgl);
calloc_msgl_err:
Parameter_error:
        return NULL;

}
void FreeSendMessage(struct MessageList_t * msgl)
{
        struct Message_t *ms=NULL,*n=NULL;
        if(msgl==NULL)
                return;
        list_del_init(&msgl->ListNode);
        list_for_each_entry_safe_reverse(ms,n,&msgl->MessageRoot,MessageNode){
                list_del_init(&ms->MessageNode);
                free(ms);
        }
        free(msgl);
}
struct MessageStr_t *GetMessageString(struct MessageList_t *msgl)
{

}
void FreeMessageString(struct MessageStr_t * msg)
{

}
