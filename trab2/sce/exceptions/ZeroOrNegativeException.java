package exceptions;

public class ZeroOrNegativeException extends IllegalArgumentException
{
  public ZeroOrNegativeException (String message) {
    super(message);
  }
}
