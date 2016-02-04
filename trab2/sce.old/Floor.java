import java.util.LinkedList; // Estrutura de dados sem tamanho pre-definido que possa facilmente ser utilizada em FIFO
import java.util.NoSuchElementException;
import exceptions.UndergroundFloorException;

public class Floor
{
  private LinkedList<Request> requests; // fila de requisicoes no andar

  private void checkEmptyness (String message) {
    if (requests.size() == 0)
      throw new NoSuchElementException(message);
  }

  public LinkedList<Request> getQueue () {
    checkEmptyness("Ninguém aguardando para subir no elevador");

    return requests;
  }

  public int getQueueSize () {
    return requests.size();
  }

  public Request runQueue () {
    checkEmptyness("Ninguém aguardando para subir no elevador");

    return requests.remove();
  }

  public Floor () {

  }

  public Floor (LinkedList<Request> reqs) {
    requests = reqs;
  }

  public Floor (Request... reqs) {
    for (Request req : reqs) {
      requests.add(req);
    }
  }

}
