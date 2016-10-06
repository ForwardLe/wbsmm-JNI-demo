package com.guwei.volume;
/**
 * 该类设计为单例模式
 * 提供控制win7系统音量的方法
 * @author guwei
 *
 */
public class VolumeControl {
	    static
	    {
	    	//System.out.println(System.getProperty("java.library.path"));
	        System.loadLibrary("VolumeControlDLL");			
	    }
		private static VolumeControl uniqueInstance = null;  
    
		private VolumeControl()  throws OperationFailedException
		{				
			init();		
		}			
		/**
		 * 单例模式
		 * @return 唯一的VolumeControl 有可能为null
		 */
		public static VolumeControl getInstance() {  
			if (uniqueInstance == null) {  
				try {
					uniqueInstance = new VolumeControl();  
				}catch (OperationFailedException e)
				{
					e.printStackTrace();
					return null;
				}
			}  
			return uniqueInstance;  
		}  			
		/**
		 * cpp本地一些初始化
		 * @return 
		 */
		private native void init()  throws OperationFailedException;
		/**
		 * 设置音量大小0~100
		 * @param num
		 * @return 操作是否成功
		 */
	    public native void setMasterVolume(int num) throws OperationFailedException;
	    /**
	     * 
	     * @return 当前音量大小1-100
	     */
		public native int getMasterVolume() throws OperationFailedException;
		/**
		 * 设置是否静音 true-是 false-否
		 * @param bMute
		 * @return
		 */
		public native void setMute(boolean bMute) throws OperationFailedException;
		/**
		 * 得到当前静音状态  true-是 false-否
		 * @return
		 */
		public native boolean getMute() throws OperationFailedException;
		/**
		 * cpp本地释放指针等操作
		 * @return
		 */
		private native void finished();
		@Override
		public void finalize()
		{
			finished();
		}
}