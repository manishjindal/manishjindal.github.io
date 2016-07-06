import java.math.*;
import java.util.Scanner;
class Bishops {

public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    
    while (sc.hasNextBigInteger()) 
    {
            
        BigInteger bi1, bi2, bi3,bi4,bi5,bi6;
    
        bi2=new BigInteger("2");
        bi1 = sc.nextBigInteger();
        int res;
        res=bi1.compareTo(bi2);
    
        if(res==0 || res==1){   
            bi3 = bi1.subtract(bi2);
        bi4=bi1.add(bi3);
    
        System.out.println(bi4);
        }
        else
        System.out.println(bi1);

    //t--;
    }
    }
}