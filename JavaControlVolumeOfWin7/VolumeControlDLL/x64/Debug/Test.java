import com.guwei.volume.*;
import java.lang.Integer;
public class Test{
	public static void main(String[] args)
	{
		VolumeControl vc = null;
		try{
			vc = VolumeControl.getInstance();
			int val = vc.getMasterVolume();
			boolean mute = vc.getMute();
			System.out.println("current volume is"+val+". Is Muted?:"+mute);
		}catch (OperationFailedException e)
		{
			System.out.println("can not read volume info: Exception:"+e);
			return ;
		}
		if (args.length>1)
		{
			String s1=args[0];
			String s2=args[1];
			if (s1.equals("setmute"))
			{
				if (s2.equals("on"))
				{
					try{
						vc.setMute(true);
						System.out.println("Operation succeed!!!");
					}catch (OperationFailedException e)
					{
						System.out.println("operation failed: Exception:"+e);
						return ;
					}
				}
				else if (s2.equals("off")) 
				{
					try{
						vc.setMute(false);
						System.out.println("Operation succeed!!!");
					}catch (OperationFailedException e)
					{
						System.out.println("operation failed: Exception:"+e);
						return ;
					}
				}
			}else if (s1.equals("setvolume"))
			{
				int value = -1;
				try {
					value = Integer.parseInt(s2);
				}catch(NumberFormatException e)
				{										
					System.out.println("operation failed: Exception:"+e);
					return ;
				}
				if (value>=0 && value<=100)
				{
					try{
						vc.setMasterVolume(value);
						System.out.println("Operation succeed!!!");
					}catch (OperationFailedException e)
					{
						System.out.println("operation failed: Exception:"+e);
						return ;
					}
				}
			}
		}
	}
}