#include <stdio.h>
#include <string.h>

typedef struct SHA1Context
{
    unsigned Message_Digest[5];

    unsigned Length_Low;
    unsigned Length_High;

    unsigned char Message_Block[64];
    int Message_Block_Index; 

    int Computed;
    int Corrupted;
} SHA1Context;

#define SHA1CircularShift(bits,word) ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))))

void SHA1Reset_52(SHA1Context *context)
{
    context->Length_Low             = 0;
    context->Length_High            = 0;
    context->Message_Block_Index    = 0;

    context->Message_Digest[0]      = 0x67452301;
    context->Message_Digest[1]      = 0xEFCDAB89;
    context->Message_Digest[2]      = 0x98BADCFE;
    context->Message_Digest[3]      = 0x10325476;
    context->Message_Digest[4]      = 0xC3D2E1F0;

    context->Computed   = 0;
    context->Corrupted  = 0;
}

void SHA1ProcessMessageBlock_52(SHA1Context *context)
{
    const unsigned K[] =    
    {
        0x5A827999,
        0x6ED9EBA1,
        0x8F1BBCDC,
        0xCA62C1D6
    };
    int         t;
    unsigned    temp;
    unsigned    W[80];
    unsigned    A, B, C, D, E;


    for(t = 0; t < 16; t++)
    {
        W[t] = ((unsigned) context->Message_Block[t * 4]) << 24;
        W[t] |= ((unsigned) context->Message_Block[t * 4 + 1]) << 16;
        W[t] |= ((unsigned) context->Message_Block[t * 4 + 2]) << 8;
        W[t] |= ((unsigned) context->Message_Block[t * 4 + 3]);
    }

    for(t = 16; t < 80; t++)
    {
       W[t] = SHA1CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
    }

    A = context->Message_Digest[0];
    B = context->Message_Digest[1];
    C = context->Message_Digest[2];
    D = context->Message_Digest[3];
    E = context->Message_Digest[4];

	printf("W[0] = %08lx\n",W[0]);
    printf("W[1] = %08lx\n",W[1]);
    printf("W[14] = %08lx\n",W[14]);
    printf("W[15] = %08lx\n",W[15]);
    printf("W[16] = %08lx\n",W[16]);
    printf("W[79] = %08lx\n",W[79]);

    for(t = 0; t < 20; t++)
    {
        temp =  SHA1CircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 20; t < 40; t++)
    {
        temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 40; t < 60; t++)
    {
        temp = SHA1CircularShift(5,A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 60; t < 80; t++)
    {
        temp = SHA1CircularShift(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }

    context->Message_Digest[0] = (context->Message_Digest[0] + A) & 0xFFFFFFFF;
    context->Message_Digest[1] = (context->Message_Digest[1] + B) & 0xFFFFFFFF;
    context->Message_Digest[2] = (context->Message_Digest[2] + C) & 0xFFFFFFFF;
    context->Message_Digest[3] = (context->Message_Digest[3] + D) & 0xFFFFFFFF;
    context->Message_Digest[4] = (context->Message_Digest[4] + E) & 0xFFFFFFFF;
    context->Message_Block_Index = 0;
}

void SHA1PadMessage_52(SHA1Context *context)
{
    if (context->Message_Block_Index > 55)
    {
        context->Message_Block[context->Message_Block_Index++] = 0x80;
        while(context->Message_Block_Index < 64)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }

        SHA1ProcessMessageBlock_52(context);

        while(context->Message_Block_Index < 56)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }
    }
    else
    {
        context->Message_Block[context->Message_Block_Index++] = 0x80;
        while(context->Message_Block_Index < 56)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }
    }

    context->Message_Block[56] = (context->Length_High >> 24) & 0xFF;
    context->Message_Block[57] = (context->Length_High >> 16) & 0xFF;
    context->Message_Block[58] = (context->Length_High >> 8) & 0xFF;
    context->Message_Block[59] = (context->Length_High) & 0xFF;
    context->Message_Block[60] = (context->Length_Low >> 24) & 0xFF;
    context->Message_Block[61] = (context->Length_Low >> 16) & 0xFF;
    context->Message_Block[62] = (context->Length_Low >> 8) & 0xFF;
    context->Message_Block[63] = (context->Length_Low) & 0xFF;

    SHA1ProcessMessageBlock_52(context);
}

int SHA1Result_52(SHA1Context *context)
{

    if (context->Corrupted)
    {
        return 0;
    }

    if (!context->Computed)
    {
        SHA1PadMessage_52(context);
        context->Computed = 1;
    }

    return 1;
}

void SHA1Input_52(SHA1Context *context, const unsigned char *message_array, unsigned length)
{
    if (!length)
    {
        return;
    }

    if (context->Computed || context->Corrupted)
    {
        context->Corrupted = 1;
        return;
    }

    while(length-- && !context->Corrupted)
    {
        context->Message_Block[context->Message_Block_Index++] = (*message_array & 0xFF);
        context->Length_Low += 8;
        context->Length_Low &= 0xFFFFFFFF;
        if (context->Length_Low == 0)
        {
            context->Length_High++;
            context->Length_High &= 0xFFFFFFFF;
            if (context->Length_High == 0)
            {
                context->Corrupted = 1;
            }
        }

        if (context->Message_Block_Index == 64)
        {
            SHA1ProcessMessageBlock_52(context);
        }

        message_array++;
    }
}


int main()
{
    SHA1Context sha;
    int i;
	unsigned char input[64];

    printf("输入待hash的消息M：\n");
	scanf("%s", input);
	printf("显示待hash的消息M:%s",input);
	printf("\n");

    SHA1Reset_52(&sha);
    SHA1Input_52(&sha, (const unsigned char *) input, strlen(input));

    if (!SHA1Result_52(&sha))
    {
        fprintf(stderr, "ERROR-- could not compute message digest\n");
    }
    else
    {
		printf("\n\n\nThe resulting 160-bit message digest is：\n\n");
        for(i = 0; i < 5 ; i++)
        {
            printf("%x ", sha.Message_Digest[i]);
        }
        printf("\n\n");
    }

	return 0;
}
