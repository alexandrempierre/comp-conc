public class Request
{
  private int id; //identificador unico da requisicao
  private Floor destinationFloor;

  public int getId () {
    return id;
  }

  public Floor getDestino () {
    return destinationFloor;
  }

  public Requisicao (int id, Floor destination) {
    destinationFloor = destination;
    this.id = id;
  }
}
