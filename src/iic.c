
#include "i2c.h"


#define IIC_DELAY_CONT 2   //������ʱ����,GD32�ﵽ��108M����������Ϊ2����������Ĭ��72M��������Ϊ0




//static void Sda_In(iic_index_t index)
static void Sda_In(dz_sim_iic_iostruct_t * iic_io)
{
	gpio_init(iic_io->gpio_periph_sda, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ,iic_io->pin_sda);
//	if(index == IIC2_INDEX)
//		gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ,GPIO_PIN_11);
//	else if(index == IIC3_INDEX)
//		gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ,GPIO_PIN_9);
//	else 
//		gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ,GPIO_PIN_6);
	//	gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ,GPIO_PIN_7);
}

//static void Sda_Out(iic_index_t index)
static void Sda_Out(dz_sim_iic_iostruct_t * iic_io)
{
	gpio_init(iic_io->gpio_periph_sda, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,iic_io->pin_sda); 
//	if(index == IIC2_INDEX)
//		gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,GPIO_PIN_11); 
//	else if(index == IIC3_INDEX)
//		gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,GPIO_PIN_9);		
//	else 
//		gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,GPIO_PIN_6);
	//	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,GPIO_PIN_7);
}


//static void Iic_Sda_Set(iic_index_t index,uint8_t val)
static void Iic_Sda_Set(dz_sim_iic_iostruct_t * iic_io,uint8_t val)
{
	if(val)
		gpio_bit_set(iic_io->gpio_periph_sda, iic_io->pin_sda);
	else
		gpio_bit_reset(iic_io->gpio_periph_sda, iic_io->pin_sda);	
//	if(index == IIC2_INDEX)
//	{
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_11);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_11);		
//	}
//	else if(index == IIC3_INDEX)
//	{
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_9);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_9);		
//	}
//	else
//	{
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_6);
//		//	gpio_bit_set(GPIOB, GPIO_PIN_7);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_6);
//		//	gpio_bit_reset(GPIOB, GPIO_PIN_7);
//	}
}


//static void Iic_Scl_Set(iic_index_t index,uint8_t val)
static void Iic_Scl_Set(dz_sim_iic_iostruct_t * iic_io,uint8_t val)
{
	if(val)
		gpio_bit_set(iic_io->gpio_periph_scl, iic_io->pin_scl);
	else
		gpio_bit_reset(iic_io->gpio_periph_scl, iic_io->pin_scl);
	
	
//	if(index == IIC2_INDEX)
//	{
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_10);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_10);
//	}
//	else if(index == IIC3_INDEX)
//	{
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_8);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_8);
//	}
//	else
//	{		
//		if(val)
//			gpio_bit_set(GPIOB, GPIO_PIN_7);
//		//	gpio_bit_set(GPIOB, GPIO_PIN_6);
//		else
//			gpio_bit_reset(GPIOB, GPIO_PIN_7);
//		//	gpio_bit_reset(GPIOB, GPIO_PIN_6);
//	}
}


//static uint8_t Read_Sda(iic_index_t index)
static uint8_t Read_Sda(dz_sim_iic_iostruct_t * iic_io)
{
	return gpio_input_bit_get(iic_io->gpio_periph_sda, iic_io->pin_sda);
//	if(index == IIC2_INDEX) 
//		return gpio_input_bit_get(GPIOB,GPIO_PIN_11); 
//	else if(index == IIC3_INDEX) 
//		return gpio_input_bit_get(GPIOB,GPIO_PIN_9); 
//	else 
//		return gpio_input_bit_get(GPIOB,GPIO_PIN_6);
	//	return gpio_input_bit_get(GPIOB,GPIO_PIN_7);
}


//static void delay_i2c(uint32_t nCount)
//{
//	nCount=nCount*4;
//  for(; nCount != 0; nCount--);
//}


//void IIC_Init(iic_index_t index)
void IIC_Init(dz_sim_iic_iostruct_t * iic_io)
{					     
//	uint32_t pin;
	//1. ʱ��ʹ��
	rcu_periph_clock_enable(iic_io->periph_sda);
	rcu_periph_clock_enable(iic_io->periph_scl);

	
	//2. ����Ϊ����ģʽ	
//	if(index == IIC2_INDEX)
//		pin = BITS(10,11); 
//	else if(index == IIC3_INDEX)
//		pin = BITS(8,9); 
//	else
//		pin = BITS(6,7); 
//	
	gpio_init(iic_io->gpio_periph_sda, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, iic_io->pin_sda);
	gpio_init(iic_io->gpio_periph_scl, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, iic_io->pin_scl);


	Iic_Scl_Set(iic_io,1);
	Iic_Sda_Set(iic_io,1);
}



//����IIC��ʼ�ź�
//void IIC_Start(iic_index_t index)
void IIC_Start(dz_sim_iic_iostruct_t * iic_io)
{
//	Iic_Scl_Set(index,0);
	Iic_Sda_Set(iic_io,1);
	Sda_Out(iic_io);     //sda�����	  	  
	Iic_Scl_Set(iic_io,1);
	Delay1us(IIC_DELAY_CONT+2);
 	Iic_Sda_Set(iic_io,0);//START:when CLK is high,DATA change form high to low 
	Delay1us(IIC_DELAY_CONT+4);
	Iic_Scl_Set(iic_io,0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}


//����IICֹͣ�ź�
//void IIC_Stop(iic_index_t index)
void IIC_Stop(dz_sim_iic_iostruct_t * iic_io)
{
	Iic_Scl_Set(iic_io,0);
	Sda_Out(iic_io);//sda�����	
	Iic_Sda_Set(iic_io,0);//STOP:when CLK is high DATA change form low to high
 	Delay1us(IIC_DELAY_CONT+4);
	Iic_Scl_Set(iic_io,1); 
	Delay1us(IIC_DELAY_CONT+1);
	Iic_Sda_Set(iic_io,1);//����I2C���߽����ź�
	Delay1us(IIC_DELAY_CONT+4);	

//	printf("IIC_Stop index = %d\r\n",index);
	
	//����֮��sda��scl�����Ϊ�ߣ���
}



//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
//uint8_t IIC_Wait_Ack(iic_index_t index)
uint8_t IIC_Wait_Ack(dz_sim_iic_iostruct_t * iic_io)
{
	uint8_t ucErrTime=0;
	
	Iic_Scl_Set(iic_io,0);
	Delay1us(IIC_DELAY_CONT+1);	 
	Iic_Sda_Set(iic_io,1);
	Delay1us(IIC_DELAY_CONT+1);	
	
	Sda_In(iic_io);      //SDA����Ϊ���� 	
	Iic_Scl_Set(iic_io,1);
	
	Delay1us(IIC_DELAY_CONT+1);	 
	while(Read_Sda(iic_io))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop(iic_io);
		//	printf("ERROR: IIC_Wait_Ack\r\n");
			return 1;
		}
		Delay1us(20);   //��ʱһ��
	}
	Iic_Scl_Set(iic_io,0);//ʱ�����0
	Delay1us(IIC_DELAY_CONT+1);	
	return 0;  
} 



//����ACKӦ��
//void IIC_Ack(iic_index_t index)
void IIC_Ack(dz_sim_iic_iostruct_t * iic_io)
{
	Iic_Scl_Set(iic_io,0);
	Sda_Out(iic_io);
	Iic_Sda_Set(iic_io,0);
	Delay1us(IIC_DELAY_CONT+2);
	Iic_Scl_Set(iic_io,1);
	Delay1us(IIC_DELAY_CONT+4);
	Iic_Scl_Set(iic_io,0);
	Delay1us(IIC_DELAY_CONT+1);
}


//������ACKӦ��		    
//void IIC_NAck(iic_index_t index)
void IIC_NAck(dz_sim_iic_iostruct_t * iic_io)
{
	Iic_Scl_Set(iic_io,0);
	Sda_Out(iic_io);
	Iic_Sda_Set(iic_io,1);
	Delay1us(IIC_DELAY_CONT+2);
	Iic_Scl_Set(iic_io,1);
	Delay1us(IIC_DELAY_CONT+4);
	Iic_Scl_Set(iic_io,0);
	Delay1us(IIC_DELAY_CONT+1);
}


//IIC����һ���ֽ�		  
//void IIC_Send_Byte(iic_index_t index,uint8_t txd)
void IIC_Send_Byte(dz_sim_iic_iostruct_t * iic_io,uint8_t txd)
{                        
    uint8_t t;  
	Iic_Scl_Set(iic_io,0);//����ʱ�ӿ�ʼ���ݴ���
	Sda_Out(iic_io); 	    
    
    for(t=0;t<8;t++)
    {              
        Delay1us(IIC_DELAY_CONT+1);   //��TEA5767��������ʱ���Ǳ����
		Iic_Sda_Set(iic_io,txd & 0x80);//IIC_SDA(index)=((txd>>(7-t))& 1);
		txd<<=1; 	//�ȷ������λ��Ȼ�������ƶ�һλ  
		Delay1us(IIC_DELAY_CONT+2);   //��TEA5767��������ʱ���Ǳ����
		Iic_Scl_Set(iic_io ,1);
		Delay1us(IIC_DELAY_CONT+4); 
		Iic_Scl_Set(iic_io,0);	
		Delay1us(IIC_DELAY_CONT+1);
    }	 
} 	



//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��	
//uint8_t I2c_WriteByte(iic_index_t index,uint8_t txd)
uint8_t I2c_WriteByte(dz_sim_iic_iostruct_t * iic_io,uint8_t txd)
{
	IIC_Send_Byte(iic_io,txd);
	if(IIC_Wait_Ack(iic_io))  //���û��Ӧ��ֱ���˳�
	{
		//printf("send word addr error!\n");
	//	DBG_PRINTF("ERROR: send word_addr IIC_Wait_Ack(index)!= 0 index = %d txd = %#x\r\n",index,txd);
		IIC_Stop(iic_io); //iic_stop(I2Cx);     //����ֹͣ�źţ����߾Ϳ�����
		return 3;
	}
	return 0;  //0  no error
}




//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
//uint8_t IIC_Read_Byte(iic_index_t index,unsigned char ack)
uint8_t IIC_Read_Byte(dz_sim_iic_iostruct_t * iic_io,unsigned char ack)
{
	unsigned char i,receive=0;
	Iic_Scl_Set(iic_io,0); 
	Sda_In(iic_io);//SDA����Ϊ����
	Delay1us(IIC_DELAY_CONT+1);
	for(i=0;i<8;i++ )
	{
		Iic_Scl_Set(iic_io,0); 
		Delay1us(IIC_DELAY_CONT+3);
		Iic_Scl_Set(iic_io,1);
		receive<<=1;
		Delay1us(IIC_DELAY_CONT+2);
		if(Read_Sda(iic_io))
			receive++;   
		Delay1us(IIC_DELAY_CONT+2);
		Iic_Scl_Set(iic_io,0); 	
	}					 
	if (!ack)  //0 ����ҪӦ��һ�������һ���ֽ��ˡ�
		IIC_NAck(iic_io);//����nACK
	else   //����Ӧ��
		IIC_Ack(iic_io); //����ACK 

	
	return receive;
}
