package com.guwei.volume;
public class OperationFailedException extends Exception
{
	public OperationFailedException()
	{}
	public OperationFailedException(String message)
	{
		super(message);
	}
}