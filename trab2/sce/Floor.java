import java.util.LinkedList; // Estrutura de dados sem tamanho pré-definido que possa facilmente ser utilizada em FIFO

public class Floor
{
  private int floorNumber; // numero do andar
  private LinkedList<Request> requests; // fila de requisicoes no andar

  public int getFloor () {
    return floorNumber;
  }

  public LinkedList<Request> getQueue () {
    return requests;
  }

  public int getQueueSize () {
    return requests.size();
  }

  public Request personIntoElevator () {
    return requests.poll();
  }

  public Floor (int floorNumber) {
    if (floorNumber < 0)
      throw new NegativeQuantityException("Quantidade de andares negativa");

    this.floorNumber = floorNumber;
  }
}
