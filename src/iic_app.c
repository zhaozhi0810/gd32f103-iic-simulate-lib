
//#include "includes.h"
#include "i2c.h"     //i2c.h��������includes.h�У���Ϊ�����������ļ������ӿڡ�ֻ��iic_appʹ��


/*	
	������IIC��Ӧ�ò㣬ʵ����������
		��Ҫ���õײ��hard_iiC.c�е�ʵ�֣�����ʹ��ģ��ķ�ʽʵ��
		
	1. ����λ�ö�����  IicApp_read_bytes
	2. ����λ��д����  IicApp_write_bytes
	
*/

//���ǵ��ж���ӿڿ��ܻ���ó�ʼ��������ȫ�ַ�ֹ��γ�ʼ��
//static uint8_t iic_inited = 0;    //��0λ�͵�1λ ����Ϊ1��ʾ�Ѿ���ʼ���ˣ�0��ʾδ��ʼ��

void IicApp_Init(dz_sim_iic_iostruct_t* iic_io)
{
//	iic_init(I2Cx);	
//	if(iic_inited & (1<< index))  //�Ѿ���ʼ���˾�ֱ�ӷ��ذ�
//		return;
	
	IIC_Init(iic_io);
	
//	iic_inited |= (1<< index);    //��ʾ�Ѿ���ʼ����
}

/*
	��ǰλ�ö�����ֽڡ����һ�ζ�ȡ256���ֽڣ�������
	����    0 ��ʾ�ɹ�����0��ʾʧ��
	!!!!!�������ṩ�ӿ�
*/
uint8_t IicApp_Read_Byte_Cur(dz_sim_iic_iostruct_t* iic_io,uint8_t dev_addr,uint8_t *dat,uint8_t len)
{
	uint8_t i;
	
	IIC_Start(iic_io);
			
	//2.�����豸��ַ
	IIC_Send_Byte(iic_io,dev_addr | 1);	    //��������ַ
	if(IIC_Wait_Ack(iic_io)!= 0) 
	//if(iic_put_devaddr(I2Cx,dev_addr | 1) != 0)   //���λ��1����ʾ������
	{
		//printf("i2c  read_byte_cur send dev addr error!\r\n");
	//	DBG_PRINTF("ERROR:IIC_Wait_Ack(index)!= 0 index = %d\r\n",index);
		return 2;
	}
	
	for(i=0;i<len;i++)
	{					
		//3.���һ���ֽڵ�����
		//dat[i] = iic_get_byte_data(I2Cx);
	
		//4.ֻ�����һ�����ݷ��ͷ�Ӧ��
		if(i == len -1)
		{
			dat[i]=IIC_Read_Byte(iic_io,0);
		}
		else
		{
			dat[i]=IIC_Read_Byte(iic_io,1);
		}
			
	}		
	//.����stopʱ��
	IIC_Stop(iic_io);//����һ��ֹͣ����
	
	return 0;
}

/*
	IicAppд������ݣ����д��256���ֽڣ�����
	������
		word_addr �ռ��ַ������Ҫ���ֽ�datд��24c02����һ���洢��Ԫ��ȥ
		dat       ʵ�����ݵ��׵�ַ��
		len       ʵ����Ҫд�����ݵĸ���
	����ֵ��
		0  ��     �ɹ�
		��0��     ʧ��
*/
uint8_t IicApp_Write_Bytes(dz_sim_iic_iostruct_t* iic_io,uint8_t dev_addr,uint8_t word_addr,const uint8_t *dat,uint8_t len)
{
	uint8_t i;

	IIC_Start(iic_io);
	
	//2.�����豸��ַ
	IIC_Send_Byte(iic_io,dev_addr & 0xfe);	    //��������ַ
	if(IIC_Wait_Ack(iic_io)!= 0) 
	{
		//printf("i2c  read_byte_cur send dev addr error!\r\n");
	//	DBG_PRINTF("ERROR: send dev_addr IIC_Wait_Ack(index)!= 0 dev_addr = 0x%x index = %d\r\n",dev_addr,index);
		IIC_Stop(iic_io);
		return 2;
	}

	//3.���Ϳռ��ַ
	IIC_Send_Byte(iic_io,word_addr);     //�����ֽ�							    
	if(IIC_Wait_Ack(iic_io))  //���û��Ӧ��ֱ���˳�
	{
		//printf("send word addr error!\r\n");
	//	DBG_PRINTF("ERROR: send word_addr IIC_Wait_Ack(index)!= 0 index = %d\r\n",index);
		IIC_Stop(iic_io); //iic_stop(I2Cx);     //����ֹͣ�źţ����߾Ϳ�����
		return 3;
	}
	
	//len����0��ʱ������Ϊ���������һ����Ч����
	if(len == 0)
	{
		return 255;   //���Ǹ��������
	}
	
	for(i=0;i<len;i++)
	{		
		//4.��������
		IIC_Send_Byte(iic_io,dat[i]);     //�����ֽ�							    
		if(IIC_Wait_Ack(iic_io)!= 0)  //���û��Ӧ��ֱ���˳�
		//if(iic_put_byte_data(I2Cx,dat[i]))  //���û��Ӧ��ֱ���˳�
		{
			//printf("send data error!\r\n");
	//		DBG_PRINTF("ERROR: send data IIC_Wait_Ack(index)!= 0 i=%d index = %d\r\n",i,index);
			IIC_Stop(iic_io); //iic_stop(I2Cx);     //����ֹͣ�źţ����߾Ϳ�����
			return 4;
		}
	}
	
	//5.�������������ߵ�ռ��
	IIC_Stop(iic_io); //iic_stop(I2Cx);
	
	return 0;
}





/*
	���������
	���� �� word_addr ָ����Ҫ��ȡ��λ��
			dat ��ʾ�洢���ݻ�����׵�ַ
			len ��ʾ��Ҫ��ȡ���ݵĸ���
	����ֵ�� 0 ��ʾ�ɹ�
			��0 ��ʾʧ��
*/
uint8_t IicApp_Read_Bytes(dz_sim_iic_iostruct_t* iic_io,uint8_t dev_addr,uint8_t word_addr,uint8_t *dat,uint8_t len)
{
	uint8_t ret;
	
	ret = IicApp_Write_Bytes(iic_io,dev_addr,word_addr,(void*)0,0);
	
	if(ret == 255)	//��������Ĵ���
	{
	//	printf("IicApp_Read_Byte_Curret == 255 \r\n");
		return IicApp_Read_Byte_Cur(iic_io,dev_addr,dat,len);
	}
	else
		;
	//	DBG_PRINTF("ERROR: IicApp_Write_Bytes ret = %d index = %d\r\n",ret,index);
	return ret;   //���ⷵ��
}
