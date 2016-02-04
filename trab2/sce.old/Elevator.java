import exceptions.ZeroOrNegativeException;
import java.util.LinkedList;
import java.util.NoSuchElement;

public class Elevator
{
  private int C; // capacidade do elevador
  private int currentFloor;
  private Building building;
  private LinkedList<Request> pendingRequests;

  public int getCapacity () {
    return C;
  }

  public Elevator (int currentFloor, int elevatorCapacity, Building b) {
    this.currentFloor = currentFloor;

    if (C <= 0)
      throw new ZeroOrNegativeException("Capacidade de carga do elevador nula ou negativa");

    C = elevatorCapacity;
    building = b;
  }

  public synchronized void peopleIn () {
    Floor f;

    try {
      f = building.getFloor(currentFloor);

      // Fazer pessoas entrarem no elevador ate que esteja cheio ou nao haja mais pessoas na fila
      int i = C;
      for (Request r : f.getQueue()) {
        pendingRequests.add(r);
        f.getQueue().remove(r);

        if (--i == 0) return;
      }
    } catch (NoSuchElementException e) {
      // Se nao ha ninguem para entrar no elevador, ninguem entra
    }
  }

  // TODO: implementar metodo para levar elevador de um andar a outro
  public void goToNextFloor () {
    if (pendingRequests.size() == 0) {
      // TODO: logica de quando todoas as pessoas sairam do elevador e é necessário pegar mais
    }

    currentFloor = pendingRequests.element().getDestination();
  }

  public void peopleOut () {
    for (int i = 0; i < pendingRequests.size(); i++) {
      if (pendingRequests.get(i).getDestination() == currentFloor) {
        pendingRequests.remove(i);
      }
    }
  }

}
