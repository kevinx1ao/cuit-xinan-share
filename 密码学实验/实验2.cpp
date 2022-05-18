#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
bool gcd_52(int p,int q);
void rand_52(int q,int p);
int extend_52(int e,int t);
int MessageProcess_52(long int num,int array[],int n);
int RLfun_52(long int a,long int n,int key[],int klen);
bool is_sushu_52(int s);

//判断两个数是不是互素。
bool gcd_52(int p,int q){
	int temp1,temp2;   //q=temp2*p+temp1;
	if(q<p){
		temp1=p;
		p=q;
		q=temp1;
	}
	temp1=q%p,temp2=q/p;
	while(temp1!=0){
	    q=p;p=temp1;
		temp1=q%p;temp2=q/p;
		}
		if(temp1==0&&temp2==q){
			return 1;
	    }
	    else{
	    	return 0;
		}
}

//生成随机素数
void rand_52(int *q,int *p,int *e){
	int n,t,i,j=0,j1,e1[100],yinzi[100];
    while(1)
    {
        srand((unsigned)time(NULL));
        *p = rand()%100+2;
        if(is_sushu_52(*p))
        {
            printf(" 自动生成的的第一个大素数 p的值为：%d  \n",*p);
            break;
        }
    }
    while(1)
    {
        srand((unsigned)time(NULL));
        *q = rand()%100+2;
        if(is_sushu_52(*q))
        {
            printf(" 自动生成的的第二个大素数q的值为：%d  \n",*q);
            break;
        }
    }
    n=*p*(*q);
    t=(*p-1)*(*q-1);
	//自动随机生成e
    for(i = 2; i <= t; i++)   //求出Φ(n)的所有因子
    {
        if(t%i==0)
        {
            yinzi[j]=i;
            j++;
        }
        j1=j;
    }
    srand(time(NULL));
    for(i = 0; i<j1+1; i++)   //生成大于因子个数的候选值（随机选取整数e（1<e<Φ(n)）作为公钥）
    {
        e1[i] = rand()%(t-2)+2;
        for(j=0; j<i; j++)
        {
            if(e1[j]==e1[i])
            {
                i--;
                break;
            }
        }
    }
    for(i=0; i<j1+1; i++)
    {
        for(j=j1; j>i; j--)
        {
            int x;
            if(e1[i]>e1[j])
            {
                x = e1[i];
                e1[i] = e1[j];
                e1[j] = x;
            }
        }
    }
    for(i = 0; i<j1+1; i++)   //要求满足e与Φ(n)的最大公约数为1，即两者互素
    {
        for(j = 0; j<j1; j++)
        {
            if(e1[i]==yinzi[j])
            {
                e1[i]=0;
                break;
            }
        }
        if(e1[i]!=0)
        {
            *e = e1[i];
            printf(" 自动生成的e的值为：%d  \n",*e);
            break;
        }
    }
}

//求e关于模(p-1)(q-1)的逆元d：即私钥 
int extend_52(int e,int t){
	int d;
	for(d=0;d<t;d++){
		if(e*d%t==1)
	        return d;
	}
}

//分组，转为数组存储n的二进制表达形式 
int MessageProcess_52(long int num,int array[],int n)
{
	long int temp=num;
	int i;
	for(i=0;temp>0;i++)
	{
		array[i]=temp%n;
		temp=temp/n;	
	}
	return i;
}

//模重复 
int RLfun_52(long int a,long int n,int key[],int klen){
	long int s=1;
	for(int i=0;i<klen;i++){
	if(key[i]==1){
		s=(s*a)%n;
	}
	a=(a*a)%n;
	printf("i=%d, %d\n",i,s);
	}
	return s;
}

//判断输入的p和q是不是素数 
bool is_sushu_52(int s){
	for(int i=2;i<s;i++){
		if(s%i==0) return false;
	}
	return true;
}

//平方乘 
long int LRFun_52(long int a,long int n,int key[],int klen)
{
	int s=1;
	for(int i=klen-1;i>=0;i--)
	{
		s=(s*s)%n;
		if(key[klen-i-1]!=0)
		{
			s=(s*a)%n;
		}
		printf("i=%d, %d\n",i,s);
	}
	return s;
 }

//将指数转为二进制数组 
int Tobin_52(int e,int key[]){
	int temp=e;
	int num=0;
	do{
		e = e / 2;
		num++;
	} while (e != 0);
	for (int i = 0; i < num; i++)
	{
		key[i] = temp % 2;
		temp = temp / 2;
	}
	return num;
}



int main(){
	int q,p,e,d,n,t,f,c,a;
	long int m;
	int len,len1,fen_len;
	int key[100],key1[100],fen[100];
	printf("请选择是否手动输入e p q:\n");
	printf("1)手动输入\t\t2)随机生成\n"); 
	scanf("%d",&a);
	do{
		if(a==2){
		rand_52(&q,&p,&e);
		}else if(a==1){
			do{
			printf("请顺序输入公钥，两素数：e  p  q:");
			scanf("%d%d%d",&e,&p,&q);
			if(is_sushu_52(p)==0){
				printf("p不是素数，请重新输入！\n");
			}
			if(is_sushu_52(q)==0){
				printf("q不是素数，请重新输入！\n");
			}
			if(gcd_52(p,q)==0){
				printf("p,q不互素，请重新输入！\n");
			}
			}while(!is_sushu_52(p)&&!is_sushu_52(q)&&!gcd_52(p,q));

		}
		else{
			printf("输入错误，请重新输入:");
			scanf("%d",&a);
		}
	}while(a!=1&&a!=2);
	n=q*p;
	printf("输出模数n：");
	printf("%d\n",n);
	t=(q-1)*(p-1);
	printf("输出模数n的欧拉函数：");
	printf("%d\n",t);
	d=extend_52(e,t);
	printf("输出模n的私钥d：%d\n",d);
	printf("请输入要加密的明文m：");
	scanf("%d",&m);
	len=Tobin_52(e,key);
	fen_len=MessageProcess_52(m,fen,n);
	printf("RSA加密模幕运算底数 指数 模数 :");
	printf("%d %d %d\n",m,e,n);
	for(int i=0;i<fen_len;i++){
		printf("RSA第%d组 底数 指数 模数 :",i);
		printf("%d %d %d\n",fen[i],e,n);
		printf("平方乘\n");
		c=LRFun_52(fen[i],n,key,len);
		printf("加密后的密文为：%d\n",c);
		printf("RSA解密模幕运算底数 指数 模数 :");
		printf("%d %d %d\n",c,d,n);
		printf("模重复平方\n");
		len1=Tobin_52(d,key1);
		f=RLfun_52(c,n,key1,len1); 
		printf("解密后的明文为：%d\n",f);
	}
	return 0;
}
