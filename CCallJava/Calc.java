import java.math.*;
public class Calc{

	public static String add(String a,String b){
		BigDecimal na,nb;
		try{
			na = new BigDecimal(a);
			nb = new BigDecimal(b);
		}catch(Exception e){
			return null;
		}
		return na.add(nb).toString();
	} 
	public static void main(String args[]){
		if (args.length!=2){
			System.out.println("param error.");
			return ;
		}
		System.out.println(add(args[0],args[1]));
	}

}
