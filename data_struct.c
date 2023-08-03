#include "stdio.h"
#define MAX_NODE 1000
typedef struct sRouteNode
{
	int pcoTei;       //父节点 
	int leftTei;     // 左子 
	int rightTei;   //右兄弟 
	int layer ;    //层级
	
}sRouteNode,*psRouteNode;

sRouteNode RouteNode[MAX_NODE] = {0};

void add_node(int tei,int pcoTei)
{
	//给父节点赋值 
	RouteNode[tei-1].pcoTei = pcoTei; 
	//层级加1   
	RouteNode[tei-1].layer  = RouteNode[pcoTei-1].layer + 1;
	printf("tei:%d   pcotei:%d  \n",tei,pcoTei);
	//如果父节点没有左子，那tei就做左子 
	if(RouteNode[pcoTei-1].leftTei == 0)       
	{
		RouteNode[pcoTei-1].leftTei = tei;
	}
	//父节点有左子
	else
	{
		//保存父节点的左子 
		int temp_tei = RouteNode[pcoTei-1].leftTei;
		printf(" -->左子_tei:%d  \n ",temp_tei);
		//找到最右兄弟节点并保存 
		temp_tei = find_last_brothernode(temp_tei);
		printf("-->最右兄弟： %d\n",temp_tei);
		//tei挂在最右兄弟 
		if(temp_tei > 0)
		{
		    //把tei挂在最右兄弟上
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
	//临时保存找到的最左值 
	last_leftTei = find_last_left(tei);
	//定义一个结构体 保存要删除的tei的左节点所有信息 
	routeNode = RouteNode[last_leftTei-1];
	//删除左节点所有信息
	memset(&RouteNode[last_leftTei-1],0,sizeof(routeNode));
	printf(" 删除tei :%d\n",last_leftTei);

	int temp_deltei = 0;
    //如果tei左子有右兄弟
	if(routeNode.rightTei >0)
	{
	    //最左的节点为删除的节点
	    if(last_leftTei == delTei)
    	{
    	    //找到左兄弟
    		int temp_left_brother = find_node_leftbrother(last_leftTei);
    		if(temp_left_brother <= 0)
    		{
                RouteNode[routeNode.pcoTei-1].leftTei = routeNode.rightTei;
    		}
    		else
    		{
        	    //左兄弟的右兄弟改为删除的节点的右兄弟
        		RouteNode[temp_left_brother-1].rightTei =routeNode.rightTei;
 		    }
    	}
    	else
    	{
    	    //取得删除节点的父节点
    		int pcotei = routeNode.pcoTei;
    		//pcotei之前的左子的右兄弟为此时pcotei的左子
    		RouteNode[pcotei-1].leftTei = routeNode.rightTei;
    		//删除右兄弟的信息
    		temp_deltei = routeNode.rightTei;
		}
	}   
	else //没有右兄弟
	{
        if(last_leftTei == delTei)//有左兄弟
    	{
    	    //找到左兄弟
    		int temp_left_brother = find_node_leftbrother(last_leftTei);
    		if(temp_left_brother <= 0)
    		{
    			//没有右兄弟也没有左兄弟 ，所以父的左子没有 
                RouteNode[routeNode.pcoTei-1].leftTei = 0;
    		}
    		else
    		{
        	    //左兄弟的右兄弟改为删除的节点的右兄弟
        		RouteNode[temp_left_brother-1].rightTei = 0;     		    
			}
    	}
    	else
        {
		    //删除tei之前的左子
			RouteNode[routeNode.pcoTei-1].leftTei = 0;
			temp_deltei = routeNode.pcoTei;   //往上一层删除
    	}
	}
	//如果要删除的节点没有删除完就递归删除掉所有的节点
	if(last_leftTei != delTei)
	{
		del_node(temp_deltei,delTei);
	}
}

void modify_brotherlayer(int tei,int offset_layer)
{
	int temp_tei = tei;
	//遍历右兄弟
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}	
		RouteNode[temp_tei-1].layer +=offset_layer;
		printf("temptei_layer:%d   %d  \n",temp_tei,RouteNode[temp_tei-1].layer);
		//没有右兄弟时候退出遍历
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei用来保存临时遍历过的右兄弟
		temp_tei = RouteNode[temp_tei-1].rightTei;
	}
}

void modify_brother_child_layer(int temp_tei,int offset_layer)
{
	//printf("\nxyz:%d\n",temp_tei);
	//遍历右兄弟，并打出遍历过的值

	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//打出遍历过的值
		modify_layer(temp_tei,offset_layer);
		//当没有右兄弟之后，退出遍历
		
		//printf("sdfdf%d ",RouteNode[temp_tei-1].layer);
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei用来保存临时遍历过的右兄弟
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
        //temp_tei 保存左子
        int temp_tei = RouteNode[tei-1].leftTei;
        
        //打印右兄弟
        modify_brotherlayer(temp_tei,offset_layer);
        //printf("\n");
        //打印右兄弟的孩子
        modify_brother_child_layer(temp_tei,offset_layer);
    }
}


void modify_node(int srcTei,int dstTei)
{
	sRouteNode routeNode; 
	//1.把srcTei信息保存
	routeNode = RouteNode[srcTei-1];            

	//2.1找srcTei的左兄弟 
	int left_brother_tei = find_node_leftbrother(srcTei);
	if(left_brother_tei == 0)  //如果没有左兄弟 
	{
		//把srcTei的父的左子改为srcTei的右兄弟	 
		int pcoTei = RouteNode[srcTei-1].pcoTei;
		RouteNode[pcoTei-1].leftTei =routeNode.rightTei;
		
	}
	else
	{
		//把左兄弟的右兄弟改为srcTei的右兄弟 
		RouteNode[left_brother_tei-1].rightTei	= RouteNode[srcTei-1].rightTei;
	 } 
	//3.把src节点修改到dst节点下面
	if(RouteNode[dstTei-1].leftTei > 0)
	{
		//找到目标节点的最右兄弟 
		int temp_tei  =  find_last_brothernode(RouteNode[dstTei-1].leftTei);
		//挂在最右兄弟的有兄弟 
		RouteNode[temp_tei].rightTei = srcTei;
	} 
	else
	{
		//把源挂到目标节点左子 
		RouteNode[dstTei-1].leftTei = srcTei;
	} 
	 //4.把srcTei有兄弟信息去掉
	RouteNode[srcTei-1].rightTei = 0;
	int offset_layer =RouteNode[dstTei-1].layer-RouteNode[srcTei-1].layer+1;
	RouteNode[srcTei-1].layer +=offset_layer;
	modify_layer(srcTei,offset_layer);
}

//寻找右兄弟为srcTei的Tei 
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
			return tei; //找到目标 
		} 
		 
	}

	return 0;
}


//找到最后一个左子
int find_last_left(int tei)   
{
	if(tei <= 0)
	{
		return 0;
	}
    //用递归遍历到最后一个左子
	if(RouteNode[tei-1].leftTei > 0)
	{
		return find_last_left(RouteNode[tei-1].leftTei);
	}	
	return tei;
}


//找到最右兄弟 
int find_last_brothernode(int tei)  
{
	//保存 
	int temp_tei = tei;
	if(tei <=0 )
	{
		return 0;
    }
    //遍历右兄弟
	while(1)
	{
	    //temp_tei为0，跳出遍历
		if(temp_tei <= 0)
		{
			break;
		}
		//没有右兄弟的时候就退出遍历
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei保存遍历过的右兄弟，将用来遍历
		temp_tei = RouteNode[temp_tei-1].rightTei;		
	}
	return temp_tei;
}

void display_brother(int tei)
{
	int temp_tei = tei;	
	//遍历右兄弟
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//打印遍历过的右兄弟值的属性
		printf("\ntei:%d  layer:%d   pco:%d   left:%d   right:%d\n",
			temp_tei,RouteNode[temp_tei-1].layer,RouteNode[temp_tei-1].pcoTei,
			RouteNode[temp_tei-1].leftTei,RouteNode[temp_tei-1].rightTei);
		//没有右兄弟时候退出遍历
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei用来保存临时遍历过的右兄弟
		temp_tei = RouteNode[temp_tei-1].rightTei;		
	}
}

void display_brother_child(int temp_tei)
{
	//printf("\nxyz:%d\n",temp_tei);
	//遍历右兄弟，并打出遍历过的值
	while(1)
	{
		if(temp_tei <= 0)
		{
			break;
		}
		//打出遍历过的值
		display(temp_tei);
		//当没有右兄弟之后，退出遍历
		if(RouteNode[temp_tei-1].rightTei == 0)
		{
			break;
		}		
		//temp_tei用来保存临时遍历过的右兄弟
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
	    //temp_tei 保存左子
		int temp_tei = RouteNode[tei-1].leftTei;
        //打印右兄弟
		display_brother(temp_tei);
		//printf("\n");
		//打印右兄弟的孩子
		display_brother_child(temp_tei);
	}
	

}



int main()
{
	
	RouteNode[0].pcoTei  = 0;
	RouteNode[0].leftTei = 0;
	RouteNode[0].layer   = 0;
	RouteNode[0].rightTei = 0;
	
	printf("多叉树：\n"); 
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
	printf("打印1\n");
	display(1);
	printf("\n打印7\n");
	display(7);
	printf("find :%d ",find_last_left(1));
	if(0)
	{
		printf("\n删除8\n");
		del_node(7,7);
		printf("删除后打印\n");
		display(1); 
	}
	
	if(1)
	{	
		printf("\n把6节点改到70下面\n"); 
		modify_node(8,70);
		printf("修改后打印\n");
	
		display(1);
		
		
	}
	
}


