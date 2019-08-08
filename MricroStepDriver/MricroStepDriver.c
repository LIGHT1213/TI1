#include "MricroStepDriver.h"
u8 rcr_remainder;   //�ظ�������������
u8 is_rcr_finish=1; //�ظ��������Ƿ��������
long rcr_integer;	//�ظ�������������
long target_pos=0;  //�з��ŷ���
long current_pos=0; //�з��ŷ���
DIR_Type motor_dir=CW;//˳ʱ��
void Locate_Rle(long num,u32 frequency,DIR_Type dir) //��Զ�λ����
{
	if(num<=0) //��ֵС����0 ��ֱ�ӷ���
	{
		printf("\r\nThe num should be greater than zero!!\r\n");
		return;
	}
	if(TIM2->CR1&0x01)//��һ�����廹δ�������  ֱ�ӷ���
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//����Ƶ�ʲ��ڷ�Χ�� ֱ�ӷ���
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir=dir;//�õ�����	
	DRIVER_DIR=motor_dir;//���÷���
	
	if(motor_dir==CW)//˳ʱ��
		target_pos=current_pos+num;//Ŀ��λ��
	else if(motor_dir==CCW)//��ʱ��
		target_pos=current_pos-num;//Ŀ��λ��
	
	rcr_integer=num/(RCR_VAL+1);//�ظ�������������
	rcr_remainder=num%(RCR_VAL+1);//�ظ�������������
	is_rcr_finish=0;//�ظ�������δ�������
	TIM8_Startup(frequency);// ����TIM2
}
/********************************************
//���Զ�λ���� 
//num   -2147483648��2147483647
//frequency: 20Hz~100KHz
*********************************************/
void Locate_Abs(long num,u32 frequency)//���Զ�λ����
{
	if(TIM2->CR1&0x01)//��һ�����廹δ������� ֱ�ӷ���
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//����Ƶ�ʲ��ڷ�Χ�� ֱ�ӷ���
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	target_pos=num;//����Ŀ��λ��
	if(target_pos!=current_pos)//Ŀ��͵�ǰλ�ò�ͬ
	{
		if(target_pos>current_pos)
			motor_dir=CW;//˳ʱ��
		else
			motor_dir=CCW;//��ʱ��
		DRIVER_DIR=motor_dir;//���÷���
		
		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//�ظ�������������
		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//�ظ�������������
		is_rcr_finish=0;//�ظ�������δ�������
		TIM8_Startup(frequency);//����TIM2
	}
}
void TIM8_Startup(u32 frequency)   //������ʱ��8
{
	u16 temp_arr=1000000/frequency-1; 
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,temp_arr);
}
