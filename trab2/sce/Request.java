public class Request
{
  private int id; //identificador unico da requisicao
  private int destinationFloor;

  public int getId () {
    return id;
  }

  public int getDestination () {
    return destinationFloor;
  }

  public Request (int id, int destination) {
    destinationFloor = destination;
    this.id = id;
  }
}
