import java.util.Scanner;

public class Aes {

    //to hex
    public static String Hex(int b) {
        return String.format("%02x", b);
    }


    public static void main(String[] args) throws Exception{
        Scanner scanner = new Scanner(System.in);
        String[][] a = new String[4][4];
        //input
        System.out.println("明文：");
        for(int j=0;j<a.length;j++){
            for(int i=0;i<a.length;i++){
                a[i][j] = scanner.next();
            }
        }
        String[][] b = new String[4][4];
        System.out.println("密钥：");
        for(int j=0;j<b.length;j++){
            for(int i=0;i<b.length;i++){
                b[i][j] = scanner.next();
            }
        }
        //output
        System.out.println("输入明文状态矩阵：");
        for(int i=0;i<a.length;i++){
            for(int j=0;j<a.length;j++){
                System.out.print(a[i][j]+" ");
            }
            System.out.println();
        }
        //String转化成16进制
        int[][] ivvv1 = new int[4][4];
        //int z = 0;
        for(int i=0;i<a.length;i++){
            for(int j=0;j<a.length;j++){
                Integer integer = Integer.parseInt(a[j][i],16);
                //System.out.println(integer);
                ivvv1[j][i] =integer;
            }
        }

        System.out.println("输入128比特初始密钥矩阵：");
        for(int i=0;i<b.length;i++){
            for(int j=0;j<b.length;j++){
                System.out.print(b[i][j]+" ");
            }
            System.out.println();
        }
        //String转化成10进制
        int[][] ivvv2 = new int[4][4];
        for(int i=0;i<b.length;i++){
            for(int j=0;j<b.length;j++){
                Integer integer = Integer.parseInt(b[j][i],16);
                //System.out.println(integer);
                ivvv2[j][i] =integer;
            }
        }

        //轮密钥加密函数调用
        Integer[][] ints = add_50(ivvv1,ivvv2);

        String[][] ivv4 = new String[4][4];
        for(int i = 0;i<4;i++){
            for(int j=0;j<4;j++){
                String string = Hex(ints[i][j]);
                //System.out.println(string);
                ivv4[j][i] = string.toUpperCase();
            }
        }

        System.out.println("轮密钥加运算输出：");
        for(int i =0;i<4;i++){
            for(int j = 0;j<4;j++){
                System.out.print(ivv4[i][j]+" ");
            }
            System.out.println();
        }

        //字节替代调用
        String[][] string = add1_50(ints);

        //行移位函数调用
        String[][] strings = add2_50(string);

        //列混合函数调用
        add3_50(strings);

    }


    //轮密钥加密函数
    private static Integer[][] add_50(int[][] p1, int[][] p2) {
        Integer[][] p3 = new Integer[4][4];
        for(int i=0;i<4;i++){
            for(int j = 0;j<4;j++){
                Integer integer =(p1[i][j])^(p2[i][j]);
                p3[j][i] = integer;
            }
        }
        return p3;
    }

    //字节替代函数
    private static String[][] add1_50(Integer[][] p1){
        String string = "63,7c,77,7b,f2,6b,6f,c5,30,01,67,2b,fe,d7,ab,76,ca,82,c9,7d,fa,59,47,f0,ad,d4,a2,af,9c,a4,72,c0,b7,fd,93,26,36,3f,f7,cc,34,a5,e5,f1,71,d8,31,15,04,c7,23,c3,18,96,05,9a,07,12,80,e2,eb,27,b2,75,09,83,2c,1a,1b,6e,5a,a0,52,3b,d6,b3,29,e3,2f,84,53,d1,00,ed,20,fc,b1,5b,6a,cb,be,39,4a,4c,58,cf,d0,ef,aa,fb,43,4d,33,85,45,f9,02,7f,50,3c,9f,a8,51,a3,40,8f,92,9d,38,f5,bc,b6,da,21,10,ff,f3,d2,cd,0c,13,ec,5f,97,44,17,c4,a7,7e,3d,64,5d,19,73,60,81,4f,dc,22,2a,90,88,46,ee,b8,14,de,5e,0b,db,e0,32,3a,0a,49,06,24,5c,c2,d3,ac,62,91,95,e4,79,e7,c8,37,6d,8d,d5,4e,a9,6c,56,f4,ea,65,7a,ae,08,ba,78,25,2e,1c,a6,b4,c6,e8,dd,74,1f,4b,bd,8b,8a,70,3e,b5,66,48,03,f6,0e,61,35,57,b9,86,c1,1d,9e,e1,f8,98,11,69,d9,8e,94,9b,1e,87,e9,ce,55,28,df,8c,a1,89,0d,bf,e6,42,68,41,99,2d,0f,b0,54,bb,16";
        String[] strings = string.split(",");
        String[][] strings1 = new String[4][4];
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                int a = p1[i][j];
                String strings2 = strings[a];
                strings1[j][i] = strings2.toUpperCase();
            }
        }
        System.out.println("字节替代输出：");
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                System.out.print(strings1[i][j]+" ");
            }
            System.out.println();
        }
        return strings1;
    }

    //行移位输出
    private static String[][] add2_50(String[][] p1){
        String s,s1,s2;
        String[][] strings = new String[4][4];
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //第一行
                strings[0][0] = p1[0][0];
                strings[0][1] = p1[0][1];
                strings[0][2] = p1[0][2];
                strings[0][3] = p1[0][3];
                //第二行
                s = p1[1][0];
                strings[1][0] = p1[1][1];
                strings[1][1] = p1[1][2];
                strings[1][2] = p1[1][3];
                strings[1][3] = s;
                //第三行
                s = p1[2][0];
                s1 = p1[2][1];
                strings[2][0] = p1[2][2];
                strings[2][1] = p1[2][3];
                strings[2][2] = s;
                strings[2][3] = s1;
                //第四行
                s = p1[3][0];
                s1 = p1[3][1];
                s2 = p1[3][2];
                strings[3][0] = p1[3][3];
                strings[3][1] = s;
                strings[3][2] = s1;
                strings[3][3] = s2; } }
        System.out.println("行移位输出：");
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                System.out.print(strings[i][j]+" ");
            }
            System.out.println();
        }
        return strings;
    }

    //列混合函数
    //固定矩阵输入
    private static void add3_50(String[][] p1){
        String[] s0 = "02,01,01,03,03,02,01,01,01,03,02,01,01,01,03,02".split(",");
        String[][] s1 = new String[4][4];
        int z = 0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                s1[j][i] = s0[z];
                z++;
            }
        }
        //String固定矩阵转10进制
        Integer[][] integers = new Integer[4][4];
        for(int i =0;i<4;i++){
            for(int j=0;j<4;j++){
                Integer integer = Integer.parseInt(s1[j][i],16);
                integers[j][i] = integer;
            }
        }
        //String输入矩阵转10进制
        Integer[][] integers1 = new Integer[4][4];
        for(int i =0;i<4;i++){
            for(int j=0;j<4;j++){
                Integer integer = Integer.parseInt(p1[j][i],16);
                integers1[j][i] = integer;
            }
        }
        Integer[][] integers2 = new Integer[4][4];
        Integer[][] integers3 = new Integer[4][4];
        Integer[][] integers4 = new Integer[4][4];
        Integer[][] integers5 = new Integer[4][4];
        int l = 0;
        int p = 0;
        for(int i =0;i<4;i++){
            for(int j =0;j<4;j++){
                for(int k =0;k<4;k++){
                    if(integers[i][p]==3){
                        integers4[i][p] = 2;
                        integers5[i][p] = 1;
                        integers2[l][p] = (integers4[i][p]*integers1[p][j])^(integers5[i][p]*integers1[p][j]);
                    }
                    else {
                        integers2[l][p] = integers[i][p] * integers1[p][j];
                    }
                    if(integers2[l][p]>255){
                        integers2[l][p] = (integers2[l][p]-256)^(27);//0x1B
                    }
                    //integers3[i][j] = integers2[l][p]^integers2[l+1][p+1]^integers2[l+2][p+2]^integers2[l+3][p+3];
                    l++;
                    p++;
                }
                l = 0;
                p = 0;
                integers3[i][j] = integers2[l][p]^integers2[l+1][p+1]^integers2[l+2][p+2]^integers2[l+3][p+3];
            }
        }

        //列混合输出
        System.out.println("列混合输出：");
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                System.out.print(Hex(integers3[i][j]).toUpperCase()+" ");
            }
            System.out.println();
        }
    }

}
