#include "stdio.h"
#define MAX_NODE 1000
typedef struct sRouteNode
{
	int pcoTei;       //���ڵ� 
	int leftTei;     // ���� 
	int rightTei;   //���ֵ� 
	int layer ;    //�㼶
	
}sRouteNode,*psRouteNode;

sRouteNode RouteNode[MAX_NODE] = {0};

void add_node(int tei,int pcoTei)
{
	//�����ڵ㸳ֵ 
	RouteNode[tei-1].pcoTei = pcoTei; 
	//�㼶��1   
	RouteNode[tei-1].layer  = RouteNode[pcoTei-1].layer + 1;
	printf("tei:%d   pcotei:%d  \n",tei,pcoTei);
	//������ڵ�û�����ӣ���tei�������� 
	if(RouteNode[pcoTei-1].leftTei == 0)       
	{
		RouteNode[pcoTei-1].leftTei = tei;
	}
	//���ڵ�������
	else
	{
		//���游�ڵ������ 
		int temp_tei = RouteNode[pcoTei-1].leftTei;
		printf(" -->����_tei:%d  \n ",temp_tei);
		//�ҵ������ֵܽڵ㲢���� 
		temp_tei = find_last_brothernode(temp_tei);
		printf("-->�����ֵܣ� %d\n",temp_tei);
		//tei���������ֵ� 
		if(temp_tei > 0)
		{
		    //��tei���������ֵ���
			RouteNode[temp_tei-1].rightTei = tei;
		}
	}
}

void del_node(int tei,int delTei)
{
	int last_leftTei;
	sRouteNode routeNode;
	if(tei <=0)
	{
		return ;
	}
	//��ʱ�����ҵ�������ֵ 
	last_leftTei = find_last_left(tei);
	//����һ���ṹ�� ����Ҫɾ����tei����ڵ�������Ϣ 
	routeNode = RouteNode[last_leftTei-1];
	//ɾ����ڵ�������Ϣ
	memset(&RouteNode[last_leftTei-1],0,sizeof(routeNode));
	printf(" ɾ��tei :%d\n",last_leftTei);

	int temp_deltei = 0;
    //���tei���������ֵ�
	if(routeNode.rightTei >0)
	{
	    //����Ľڵ�Ϊɾ���Ľڵ�
	    if(last_leftTei == delTei)
    	{
    	    //�ҵ����ֵ�
    		int temp_left_brother = find_node_leftbrother(last_leftTei);
    		if(temp_left_brother <= 0)
    		{
                RouteNode[routeNode.pcoTei-1].leftTei = routeNode.rightTei;
    		}
    		else
    		{
        	    //���ֵܵ����ֵܸ�Ϊɾ���Ľڵ�����ֵ�
        		RouteNode[temp_left_brother-1].rightTei =routeNode.rightTei;
 		    }
    	}
    	else
    	{
    	    //ȡ��ɾ���ڵ�ĸ��ڵ�
    		int pcotei = routeNode.pcoTei;
    		//pcotei֮ǰ�����ӵ����ֵ�Ϊ��ʱpcotei������
    		RouteNode[pcotei-1].leftTei = routeNode.rightTei;
    		//ɾ�����ֵܵ���Ϣ
    		temp_deltei = routeNode.rightTei;
		}
	}   
	else //û�����ֵ�
	{
        if(last_leftTei == delTei)//�����ֵ�
    	{
    	    //�ҵ����ֵ�
    		int temp_left_brother = find_node_leftbrother(last_leftTei);
    		if(temp_left_brother <= 0)
    		{
    			//û�����ֵ�Ҳû�����ֵ� �����Ը�������û�� 
                RouteNode[routeNode.pcoTei-1].leftTei = 0;
    		}
    		else
    		{
        	    //���ֵܵ����ֵܸ�Ϊɾ���Ľڵ�����ֵ�
        		RouteNode[temp_left_brother-1].rightTei = 0;     		    
			}
    	}
    	else
        {
		    //ɾ��tei֮ǰ������
			RouteNode[routeNode.pcoTei-1].leftTei = 0;
			temp_deltei = routeNode.pcoTei;   //����һ��ɾ��
    	}
	}
	//���Ҫɾ���Ľڵ�û��ɾ����͵ݹ�ɾ�������еĽڵ�
	if(last_leftTei != delTei)
	{
		del_node(temp_deltei,delTei);
	}
}

void modify_brotherlayer(int tei,int offset_layer)
{
	int temp_tei = tei;
	//�������ֵ�
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}	
		RouteNode[temp_tei-1].layer +=offset_layer;
		printf("temptei_layer:%d   %d  \n",temp_tei,RouteNode[temp_tei-1].layer);
		//û�����ֵ�ʱ���˳�����
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei����������ʱ�����������ֵ�
		temp_tei = RouteNode[temp_tei-1].rightTei;
	}
}

void modify_brother_child_layer(int temp_tei,int offset_layer)
{
	//printf("\nxyz:%d\n",temp_tei);
	//�������ֵܣ��������������ֵ

	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//�����������ֵ
		modify_layer(temp_tei,offset_layer);
		//��û�����ֵ�֮���˳�����
		
		//printf("sdfdf%d ",RouteNode[temp_tei-1].layer);
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei����������ʱ�����������ֵ�
		temp_tei = RouteNode[temp_tei-1].rightTei;
		printf("%d ", RouteNode[temp_tei-1].layer);	
	}
}

void modify_layer(int tei,int offset_layer)
{
	
    if(tei <= 0)
    {
        return;
    }
    //printf("\n%d  ",RouteNode[tei-1].leftTei);
    if(RouteNode[tei-1].leftTei > 0)
    {
        //temp_tei ��������
        int temp_tei = RouteNode[tei-1].leftTei;
        
        //��ӡ���ֵ�
        modify_brotherlayer(temp_tei,offset_layer);
        //printf("\n");
        //��ӡ���ֵܵĺ���
        modify_brother_child_layer(temp_tei,offset_layer);
    }
}


void modify_node(int srcTei,int dstTei)
{
	sRouteNode routeNode; 
	//1.��srcTei��Ϣ����
	routeNode = RouteNode[srcTei-1];            

	//2.1��srcTei�����ֵ� 
	int left_brother_tei = find_node_leftbrother(srcTei);
	if(left_brother_tei == 0)  //���û�����ֵ� 
	{
		//��srcTei�ĸ������Ӹ�ΪsrcTei�����ֵ�	 
		int pcoTei = RouteNode[srcTei-1].pcoTei;
		RouteNode[pcoTei-1].leftTei =routeNode.rightTei;
		
	}
	else
	{
		//�����ֵܵ����ֵܸ�ΪsrcTei�����ֵ� 
		RouteNode[left_brother_tei-1].rightTei	= RouteNode[srcTei-1].rightTei;
	 } 
	//3.��src�ڵ��޸ĵ�dst�ڵ�����
	if(RouteNode[dstTei-1].leftTei > 0)
	{
		//�ҵ�Ŀ��ڵ�������ֵ� 
		int temp_tei  =  find_last_brothernode(RouteNode[dstTei-1].leftTei);
		//���������ֵܵ����ֵ� 
		RouteNode[temp_tei].rightTei = srcTei;
	} 
	else
	{
		//��Դ�ҵ�Ŀ��ڵ����� 
		RouteNode[dstTei-1].leftTei = srcTei;
	} 
	 //4.��srcTei���ֵ���Ϣȥ��
	RouteNode[srcTei-1].rightTei = 0;
	int offset_layer =RouteNode[dstTei-1].layer-RouteNode[srcTei-1].layer+1;
	RouteNode[srcTei-1].layer +=offset_layer;
	modify_layer(srcTei,offset_layer);
}

//Ѱ�����ֵ�ΪsrcTei��Tei 
int find_node_leftbrother(int srcTei)
{	
	
	if(srcTei <= 0)
	{
		return 0;
	}
	int tei=1;
	for(tei=1;tei<MAX_NODE;tei++)
	{
		if(	RouteNode[tei-1].rightTei == srcTei)
		{
			return tei; //�ҵ�Ŀ�� 
		} 
		 
	}

	return 0;
}


//�ҵ����һ������
int find_last_left(int tei)   
{
	if(tei <= 0)
	{
		return 0;
	}
    //�õݹ���������һ������
	if(RouteNode[tei-1].leftTei > 0)
	{
		return find_last_left(RouteNode[tei-1].leftTei);
	}	
	return tei;
}


//�ҵ������ֵ� 
int find_last_brothernode(int tei)  
{
	//���� 
	int temp_tei = tei;
	if(tei <=0 )
	{
		return 0;
    }
    //�������ֵ�
	while(1)
	{
	    //temp_teiΪ0����������
		if(temp_tei <= 0)
		{
			break;
		}
		//û�����ֵܵ�ʱ����˳�����
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei��������������ֵܣ�����������
		temp_tei = RouteNode[temp_tei-1].rightTei;		
	}
	return temp_tei;
}

void display_brother(int tei)
{
	int temp_tei = tei;	
	//�������ֵ�
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//��ӡ�����������ֵ�ֵ������
		printf("\ntei:%d  layer:%d   pco:%d   left:%d   right:%d\n",
			temp_tei,RouteNode[temp_tei-1].layer,RouteNode[temp_tei-1].pcoTei,
			RouteNode[temp_tei-1].leftTei,RouteNode[temp_tei-1].rightTei);
		//û�����ֵ�ʱ���˳�����
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei����������ʱ�����������ֵ�
		temp_tei = RouteNode[temp_tei-1].rightTei;		
	}
}

void display_brother_child(int temp_tei)
{
	//printf("\nxyz:%d\n",temp_tei);
	//�������ֵܣ��������������ֵ
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//�����������ֵ
		display(temp_tei);
		//��û�����ֵ�֮���˳�����
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei����������ʱ�����������ֵ�
		temp_tei = RouteNode[temp_tei-1].rightTei;
	}
}

void display(int tei)
{
	if(tei <= 0)
	{
		return;
	}
	//printf("\n%d  ",RouteNode[tei-1].leftTei);
	if(RouteNode[tei-1].leftTei > 0)
	{
	    //temp_tei ��������
		int temp_tei = RouteNode[tei-1].leftTei;
        //��ӡ���ֵ�
		display_brother(temp_tei);
		//printf("\n");
		//��ӡ���ֵܵĺ���
		display_brother_child(temp_tei);
	}
	

}



int main()
{
	
	RouteNode[0].pcoTei  = 0;
	RouteNode[0].leftTei = 0;
	RouteNode[0].layer   = 0;
	RouteNode[0].rightTei = 0;
	
	printf("�������\n"); 
	add_node(8,1);
//	display(1);
	add_node(6,1);
	add_node(7,1);
	
	add_node(11,8);
	add_node(9,8);
	add_node(10,8);
	
	add_node(20,9);
	add_node(5,6);
	
	add_node(30,7);
	add_node(50,7);
	add_node(70,30);
	
	add_node(60,50);
	printf("��ӡ1\n");
	display(1);
	printf("\n��ӡ7\n");
	display(7);
	printf("find :%d ",find_last_left(1));
	if(0)
	{
		printf("\nɾ��8\n");
		del_node(7,7);
		printf("ɾ�����ӡ\n");
		display(1); 
	}
	
	if(1)
	{	
		printf("\n��6�ڵ�ĵ�70����\n"); 
		modify_node(8,70);
		printf("�޸ĺ��ӡ\n");
	
		display(1);
		
		
	}
	
}


