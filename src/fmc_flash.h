

#ifndef __FMC_FLASH_H__
#define __FMC_FLASH_H__


#include <gd32f10x.h>

//��ͬ������32��Ӧ��ҳ��С��һ����ע���޸�
#define FMC_PAGE_SIZE           (((uint16_t)0x400U)*2)   //0x400��ʾ1K�ֽ�

/*
	��ȡflash���ݣ������ڲ�����4�ֽڶ������
*/
void read_4Btye(uint32_t read_addr, uint32_t *data, uint32_t len);

/*
	����Ƿ���Ҫ����ҳ
	addr:�����ҳ��ʼ��ַ

*/
int check_erase(int start_addr ,uint32_t datalen);


/*
	������Ҫʹ�õ�����,����������ǰ�벿��û��ʹ�õĲ���
*/
void erase_flash(uint32_t write_addr, int page_num);



/*
	д��flash���ⳤ�ȵ��������ݣ������ڲ�����4�ֽڶ������
*/

void write_flash(uint32_t write_addr, uint32_t *data, int len);

#endif
