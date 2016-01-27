package exceptions;

public class NullFloorException extends IllegalArgumentException
{
    public NullFloorException (String message) {
      super(message);
    }
}
